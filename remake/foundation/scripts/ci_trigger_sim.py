#!/usr/bin/env python3
"""Replay the build-foundation trigger against real commits (port rule).

This models which jobs the workflow would run for a push. It reads `on.push.paths`
and each job's `if:` *out of the workflow file*, so the model cannot drift from the
YAML without failing loudly, and it is deliberately a model: GitHub's own `paths`
matching and expression evaluation are reimplemented here, not executed. It is a
port rule, not recovered behaviour, and it proves nothing about what GitHub will do.

What is modelled:
  * `on.push.paths` globs over the union of files changed by the range (`**` crosses
    `/`, `*` stops at it, `?` is one character).
  * The gate job: the path its step `grep -qx`es (read out of that step), tested
    against the push's changed files — which is what the step's own
    `git diff before..after` computes. Its shell is reimplemented, not executed.
  * The gate's fallback, in the same direction the step takes it: a push with no
    usable base commit (all-zero `before`, or a range git cannot resolve) runs the
    matrix, and so does `workflow_dispatch`.
  * `github.event_name` and `needs.<gate>.outputs.<output>` for the `||`, `&&`,
    `==`, `!=`, `!`, parentheses and `contains(...)` subset the workflow uses. Any
    other expression shape is an error, never a guess.
  * A job's `needs:` is assumed satisfied — the model has no notion of a job
    failing, so it cannot decide the `if:` of a job whose gate failed.
Not modelled, and only a real run can show it: GitHub skips the `paths` filter and
always runs the workflow when a push carries more than 1000 commits, when the diff
times out, or when the diff has more than 3000 files the filter does not match
(https://docs.github.com/en/actions/how-tos/write-workflows/choose-when-workflows-run/trigger-a-workflow).

Usage:
    remake/foundation/scripts/ci_trigger_sim.py b8c527f^..b8c527f   # a real push range
    remake/foundation/scripts/ci_trigger_sim.py a35e36d            # one commit
    remake/foundation/scripts/ci_trigger_sim.py --files remake/foundation/VERSION
    remake/foundation/scripts/ci_trigger_sim.py --no-base 92b6d70  # no base: gate falls back
    remake/foundation/scripts/ci_trigger_sim.py --dispatch

Needs PyYAML; the workflow is parsed, never regex-scraped.
"""
import argparse
import os
import re
import subprocess

import yaml

DEFAULT_WORKFLOW = ".github/workflows/build-foundation.yml"
GATE_GREP_RE = re.compile(r"grep\s+-qx\s+(\S+)")


class ModelError(SystemExit):
    """An input the model does not cover. Fail loudly rather than guess."""


def git(repo, *args):
    out = subprocess.run(("git", "-C", repo) + args, capture_output=True, text=True)
    if out.returncode != 0:
        raise ModelError(f"git {' '.join(args)}: {out.stderr.strip()}")
    return [line for line in out.stdout.splitlines() if line.strip()]


def parents_of(repo, rev):
    return git(repo, "rev-list", "--parents", "-n", "1", rev)[0].split()[1:]


def commit_files(repo, rev):
    """The files one commit changed; a merge compares against its first parent."""
    parents = parents_of(repo, rev)
    if not parents:
        return git(repo, "diff-tree", "--no-commit-id", "--name-only", "--no-renames", "--root", "-r", rev)
    return git(repo, "diff", "--name-only", "--no-renames", parents[0], rev)


def resolve_range(repo, spec):
    """(before, after, changed paths) for `A..B`, or for one commit's own diff."""
    if ".." in spec:
        before, after = (git(repo, "rev-parse", part)[0] for part in spec.split("..", 1))
        return before, after, git(repo, "diff", "--name-only", "--no-renames", before, after)
    after = git(repo, "rev-parse", spec)[0]
    parents = parents_of(repo, after)
    return (parents[0] if parents else "(root)"), after, commit_files(repo, after)


def glob_to_regex(pattern):
    if any(ch in pattern for ch in "+[]!"):
        raise ModelError(f"unmodelled paths syntax in {pattern!r}: only '*', '**' and '?' are modelled")
    out, i = [], 0
    while i < len(pattern):
        if pattern.startswith("**", i):
            out.append(".*")
            i += 2
        elif pattern[i] == "*":
            out.append("[^/]*")
            i += 1
        elif pattern[i] == "?":
            out.append("[^/]")
            i += 1
        else:
            out.append(re.escape(pattern[i]))
            i += 1
    return re.compile("^" + "".join(out) + "$")


TOKEN_RE = re.compile(
    r"""(?P<ws>\s+)
      | (?P<op>\|\||&&|==|!=|!)
      | (?P<paren>[()])
      | (?P<comma>,)
      | (?P<str>'[^']*'|"[^"]*")
      | (?P<ident>[A-Za-z_][A-Za-z0-9_.\-]*)""",
    re.VERBOSE,
)


def truthy(value):
    if value is None or value is False:
        return False
    if isinstance(value, str):
        return value != ""
    if isinstance(value, (int, float)):
        return value != 0
    return True


def equal(left, right):
    # GitHub compares strings case-insensitively.
    if isinstance(left, str) and isinstance(right, str):
        return left.casefold() == right.casefold()
    return left == right


def contains(search, item):
    if isinstance(search, list):
        return any(equal(element, item) for element in search)
    if search is None:
        return False
    return str(item).casefold() in str(search).casefold()


class ExprModel:
    """The `if:` subset above, evaluated against a hand-built context."""

    def __init__(self, expr, context):
        self.src = expr
        self.context = context
        self.tokens = self._tokenize(expr)
        self.pos = 0

    @staticmethod
    def _tokenize(src):
        tokens, i = [], 0
        while i < len(src):
            match = TOKEN_RE.match(src, i)
            if not match:
                raise ModelError(f"unmodelled token at {src[i:]!r} in {src!r}")
            i = match.end()
            for kind in ("op", "paren", "comma", "str", "ident"):
                if match.group(kind) is not None:
                    tokens.append((kind, match.group(kind)))
                    break
        return tokens

    def _eat(self, text):
        if self.pos < len(self.tokens) and self.tokens[self.pos][1] == text:
            self.pos += 1
            return True
        return False

    def eval(self):
        value = self._or()
        if self.pos != len(self.tokens):
            raise ModelError(f"trailing tokens in {self.src!r}")
        return truthy(value)

    def _or(self):
        value = self._and()
        while self._eat("||"):
            # The right side is parsed even when the left one decides the result:
            # GitHub would short-circuit, but an expression this model does not
            # cover must raise rather than be skipped as unevaluated.
            right = self._and()
            value = truthy(value) or truthy(right)
        return value

    def _and(self):
        value = self._cmp()
        while self._eat("&&"):
            right = self._cmp()
            value = truthy(value) and truthy(right)
        return value

    def _cmp(self):
        left = self._unary()
        if self._eat("=="):
            return equal(left, self._unary())
        if self._eat("!="):
            return not equal(left, self._unary())
        return left

    def _unary(self):
        if self._eat("!"):
            return not truthy(self._unary())
        if self._eat("("):
            value = self._or()
            if not self._eat(")"):
                raise ModelError(f"missing ')' in {self.src!r}")
            return value
        if self.pos >= len(self.tokens):
            raise ModelError(f"expression ends early in {self.src!r}")
        kind, text = self.tokens[self.pos]
        if kind == "str":
            self.pos += 1
            return text[1:-1]
        if kind != "ident":
            raise ModelError(f"unmodelled operand {text!r} in {self.src!r}")
        self.pos += 1
        if not self._eat("("):
            if text == "true":
                return True
            if text == "false":
                return False
            if text == "null":
                return None
            if text not in self.context:
                raise ModelError(f"{text!r} is not in the modelled context ({self.src!r})")
            return self.context[text]
        args = [self._or()]
        while self._eat(","):
            args.append(self._or())
        if not self._eat(")"):
            raise ModelError(f"missing ')' after {text}() in {self.src!r}")
        if text.casefold() != "contains" or len(args) != 2:
            raise ModelError(f"unmodelled function {text}() in {self.src!r}: only contains(search, item)")
        return contains(args[0], args[1])


def load_workflow(path):
    with open(path, encoding="utf-8") as handle:
        workflow = yaml.safe_load(handle)
    # PyYAML reads a bare `on:` key as boolean True, not the string "on".
    on = workflow.get("on", workflow.get(True))
    if not isinstance(on, dict):
        raise ModelError(f"{path}: `on:` is not a mapping; the model expects push/workflow_dispatch")
    push = on.get("push") or {}
    if not isinstance(push, dict):
        raise ModelError(f"{path}: `on.push` is not a mapping")
    return {
        "paths": push.get("paths") or [],
        "branches": push.get("branches"),
        "dispatch": "workflow_dispatch" in on,
        "jobs": workflow.get("jobs") or {},
    }


def one_line(text):
    return " ".join(str(text).split())


def find_gate(workflow):
    """(job, output, path) for the job that gates the matrix on a `grep -qx <path>`.

    That is the shape this model can replay; any other gate raises rather than
    guessing which job decides the expensive half.
    """
    for name, job in workflow["jobs"].items():
        for step in (job or {}).get("steps") or []:
            match = GATE_GREP_RE.search(step.get("run") or "")
            if not match:
                continue
            outputs = list(((job or {}).get("outputs") or {}).keys())
            if len(outputs) != 1:
                raise ModelError(f"gate job {name!r} publishes {outputs}; the model expects exactly one output")
            return name, outputs[0], match.group(1)
    raise ModelError("no gate job found: expected a job whose step publishes `grep -qx <path>` as an output")


def report(workflow, wf_path, origin, scenario=False, changed=None, tip_files=None, head_line=None,
           base_resolvable=True):
    """`changed` is None for a dispatch, otherwise the push's paths and its tip commit."""
    push = changed is not None
    print(f"workflow    {wf_path}  (read, not executed)")
    print("model       port rule: `paths`, the gate and `if:` replayed from that file;")
    print("            GitHub's own evaluation and run are not executed")
    print(f"event       {origin}")
    if push:
        print(f"head_commit {head_line}")
        print(f"changed ({len(changed)})")
        for path in changed:
            print(f"            {path}")
        matches = [p for p in changed if any(glob_to_regex(pat).match(p) for pat in workflow["paths"])]
        print(f"paths       {len(matches)}/{len(changed)} match {workflow['paths']}")
        if not matches:
            print("trigger     the workflow does not run: no changed path matches")
            print("jobs        (none)")
            return
    else:
        print("trigger     workflow_dispatch runs the workflow unconditionally")
    gate_job, gate_output, gate_path = find_gate(workflow)
    if not push:
        gate, why = "true", "workflow_dispatch"
    elif not base_resolvable:
        gate, why = "true", "no usable base commit: the gate falls back to running the matrix"
    elif gate_path in changed:
        gate, why = "true", f"{gate_path} changed in the push"
    else:
        gate, why = "false", f"no {gate_path} in the push"
    print(f"gate        {gate_job}.{gate_output}={gate}  ({why})")
    context = {
        "github.event_name": "push" if push else "workflow_dispatch",
        f"needs.{gate_job}.outputs.{gate_output}": gate,
    }
    print("jobs")
    for name, job in workflow["jobs"].items():
        expr = (job or {}).get("if")
        if expr is None:
            print(f"  {name:<8} RUN   no if:")
            continue
        value = ExprModel(one_line(expr), context).eval()
        print(f"  {name:<8} {'RUN ' if value else 'SKIP'}  if: {one_line(expr)} -> {str(value).lower()}")
    if push and gate_path in changed and gate_path not in tip_files:
        print(f"note        {gate_path} changed outside the tip commit: the gate diffs the whole")
        print("            push range, so the matrix still runs")
    if scenario:
        print("note        the file list is a --files scenario, not a commit in this repository")


def main():
    parser = argparse.ArgumentParser(description="Model which build-foundation jobs a push would run (port rule).")
    parser.add_argument("range", nargs="?", metavar="REV-RANGE",
                        help="push to model: 'A..B', or one commit and its own diff")
    parser.add_argument("--files", nargs="+", metavar="PATH",
                        help="scenario: model a push that changed exactly these paths")
    parser.add_argument("--dispatch", action="store_true", help="model a workflow_dispatch instead of a push")
    parser.add_argument("--no-base", action="store_true",
                        help="model a push whose github.event.before is all zeros (new or force-pushed ref): "
                             "the gate must fall back to running the matrix")
    parser.add_argument("--repo", default=".", help="repository to read (default: .)")
    parser.add_argument("--workflow", default=DEFAULT_WORKFLOW,
                        help=f"workflow file, relative to --repo (default: {DEFAULT_WORKFLOW})")
    args = parser.parse_args()
    if sum([bool(args.range), bool(args.files), args.dispatch]) != 1:
        raise ModelError("give exactly one of: a REV-RANGE, --files, or --dispatch")
    if args.no_base and args.dispatch:
        raise ModelError("--no-base describes a push; it cannot be combined with --dispatch")

    wf_path = args.workflow if os.path.isabs(args.workflow) else os.path.join(args.repo, args.workflow)
    workflow = load_workflow(wf_path)
    if not workflow["dispatch"]:
        raise ModelError(f"{wf_path}: no workflow_dispatch trigger")

    resolvable = not args.no_base
    if args.dispatch:
        report(workflow, wf_path, "workflow_dispatch (manual)")
        return
    on_branches = f"push to {workflow['branches']}"
    if args.files:
        report(workflow, wf_path, f"{on_branches}, --files scenario (not a commit in this repository)", scenario=True,
               changed=list(args.files), tip_files=list(args.files), head_line="(scenario: --files)",
               base_resolvable=resolvable)
        return
    before, after, changed = resolve_range(args.repo, args.range)
    report(workflow, wf_path, f"{on_branches}, model of {before[:12]}..{after[:12]}", changed=changed,
           tip_files=commit_files(args.repo, after), base_resolvable=resolvable,
           head_line=git(args.repo, "log", "-1", "--format=%h %s", after)[0])


if __name__ == "__main__":
    main()
