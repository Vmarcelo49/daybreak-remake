#!/usr/bin/env node
// Runs the web client in a headless Chromium until it prints RESULT, a failure or the timeout,
// and reports its console. The browser's own tool panes often have no WebGPU adapter, so this
// launches one that does. Needs `python3 -m daybreak_web serve` running.
//
//   usage: web_flow_check.mjs <url> <out.png> [timeout seconds] [--match=<regex>]
//
// Exit 0 only when the console printed "RESULT: ok" and every --match regex was seen.
import { spawn } from "node:child_process";
import { mkdtempSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { join } from "node:path";

const positional = process.argv.slice(2).filter((a) => !a.startsWith("--"));
const required = process.argv.slice(2).filter((a) => a.startsWith("--match="))
    .map((a) => new RegExp(a.slice("--match=".length)));
const [url, outPng, timeoutArg] = positional;
if (!url || !outPng) {
    console.error("usage: web_flow_check.mjs <url> <out.png> [timeout seconds] [--match=<regex>]");
    process.exit(2);
}
const timeoutMs = (Number(timeoutArg) || 600) * 1000;
const port = 9300 + (process.pid % 500);
const profile = mkdtempSync(join(tmpdir(), "web_flow_"));
const browser = spawn(process.env.CHROMIUM || "chromium", [
    "--headless=new", `--remote-debugging-port=${port}`, `--user-data-dir=${profile}`,
    "--enable-unsafe-webgpu", "--enable-features=Vulkan,WebGPU", "--use-angle=vulkan",
    "--ignore-gpu-blocklist", "--mute-audio", "--no-first-run", "--window-size=1280,800", "about:blank",
], { stdio: "ignore" });

async function target() {
    for (let i = 0; i < 100; ++i) {
        try {
            const list = await (await fetch(`http://127.0.0.1:${port}/json`)).json();
            const page = list.find((t) => t.type === "page");
            if (page) return page.webSocketDebuggerUrl;
        } catch { /* the browser is still starting */ }
        await new Promise((r) => setTimeout(r, 200));
    }
    throw new Error("chromium did not open its debugging port");
}

const ws = new WebSocket(await target());
await new Promise((r) => ws.addEventListener("open", r, { once: true }));
let nextId = 1;
const pending = new Map();
const started = Date.now();
const lines = [];
let done = null;
const finish = (reason) => { done = done || reason; };

function send(method, params = {}) {
    const id = nextId++;
    ws.send(JSON.stringify({ id, method, params }));
    return new Promise((resolve) => pending.set(id, resolve));
}

function onLine(text) {
    const stamp = ((Date.now() - started) / 1000).toFixed(1);
    lines.push(text);
    if (!/startup \d+\/|match \d+\//.test(text)) console.log(`[${stamp}s] ${text}`.slice(0, 220));
    if (/RESULT: ok/.test(text)) finish("ok");
    if (/RESULT: (?!ok)|Aborted\(|exception thrown|RuntimeError/.test(text)) finish("failure");
}

ws.addEventListener("message", (event) => {
    const msg = JSON.parse(event.data);
    if (msg.id && pending.has(msg.id)) {
        pending.get(msg.id)(msg.result || msg.error);
        pending.delete(msg.id);
    } else if (msg.method === "Runtime.consoleAPICalled") {
        onLine(msg.params.args.map((a) => a.value ?? a.description ?? "").join(" "));
    } else if (msg.method === "Runtime.exceptionThrown") {
        onLine("exception thrown: " + (msg.params.exceptionDetails.exception?.description ?? msg.params.exceptionDetails.text));
    }
});

await send("Runtime.enable");
await send("Page.enable");
await send("Page.navigate", { url });
while (!done && Date.now() - started < timeoutMs) await new Promise((r) => setTimeout(r, 500));
const timedOut = !done;

const shot = await send("Page.captureScreenshot", { format: "png" });
if (shot.data) writeFileSync(outPng, Buffer.from(shot.data, "base64"));
browser.kill();
rmSync(profile, { recursive: true, force: true, maxRetries: 3 });

const missing = required.filter((re) => !lines.some((l) => re.test(l)));
for (const re of missing) console.log(`missing: ${re}`);
console.log(`web_flow_check: ${timedOut ? "timeout" : done}, ${((Date.now() - started) / 1000).toFixed(1)} s`);
process.exit(done === "ok" && missing.length === 0 ? 0 : 1);
