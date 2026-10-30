# Local live animation debugger (work in progress)

The host owns this port-side development instrument. It does not attach the DSH
GUI to the game. Enable the Linux development build with
`cmake -S remake/foundation -B remake/foundation/build/linux -DFOUNDATION_LIVE_DEBUG=ON`,
then build `foundation_demo`. Normal builds default OFF, and normal launches do not
create an endpoint. Windows/web currently have no transport.

Launch a **visible standalone match** with `--live-debug --no-audio`
and `SDL_AUDIO_DRIVER=dummy`. The game prints a fresh private session directory and
starts paused. Connect `python3 remake/foundation/scripts/live_debug.py <directory>`.
The client is interactive and retains one socket; disconnect pauses the match and
clears input scheduling/breakpoints. Do not use separate client processes for an
ordered sequence that must survive across commands.

## Security boundary

A randomly named mode-0700 directory contains a mode-0600 Unix socket and a
mode-0600 process/session manifest. The server checks same-user peer credentials
and a fresh random 256-bit credential. The client checks server PID/UID against the
manifest. The narrow ASCII protocol accepts only known commands and action names;
responses are version-1 JSON. No shell, source evaluation, arbitrary file reads,
or caller-chosen server output paths exist. Disconnect fails closed. Requests,
scheduled inputs and breakpoints are bounded. This is **not** isolation against
other malicious processes running as the same Unix user.

## Commands

- `status`: authoritative snapshot and presentation count.
- `pause`: freeze and acknowledge after presenting the frozen tick.
- `step N`: execute exactly N match ticks, then present and return evidence.
- `resume`: run the fixed 64-Hz simulation again.
- `input F SPAN ACTIONS`: append a full held-mask span for fighter F; comma-separated
  `Forward,Back,Left,Right,Attack,Guard,Shoot,Jump,Special,Tactics,Lock`, or `-`.
  Reports first/release ticks. Insert a `-` span between repeated taps. Events at the
  same boundary apply in queue order; edges derive once per gameplay tick.
- `break KIND F VALUE CHAR ITEM`: kinds `state`, `move`, `bind`, `volume`, `contact`.
  VALUE matches a numeric state/move/set or -1; CHAR/ITEM scope by character index
  and equipped item ID or -1. `volume` requires a live nonzero-radius record and
  tested hit volume; `contact` currently means confirmed melee contact, not projectile
  contact. State/move/bind breakpoints fire on a change, not every held tick.
- `clear`: clear scheduling and breakpoints.
- `detach`: release this client's control, freezing the match.

Completed steps/breakpoints return a snapshot and PPM path in the private directory.
The PPM uses the same renderer, scene, cameras, HUD and authoritative pose as the
visible window, but is an **offscreen rerender**, not a compositor screenshot.
The debugger pins presentation interpolation to the current tick; it does not
verify ordinary live interpolation. Simulation remains paused while evidence is
read. The user must confirm animation identity in the visible window explicitly.
Renderer failures must not be mistaken for successful evidence. Session metadata
is removed on exit; evidence images remain for collection.

## Initial controlled observation (not acceptance)

Rena+0/item001 versus Mion+0/item002, shrine stage03, silent visible Linux Vulkan
run: tick114 reached airborne Run with `air_dash=true`, `bound_move=-1`, set0,
fallback=true. Tick115 Attack bound move311/tag40/Anim-84. At tick121 the same tag
was still bound at elapsed7 with no active volume or contact. A live-window screenshot
was taken while simulation was frozen. The user could not identify the animation
confidently from the early pose, tentatively guessed a grounded horizontal kick,
and accidentally closed the window. This is **inconclusive**, not kick confirmation.
The close produced a surface-acquisition failure (status3) and process exit1.

The candidate dash fix now scopes Rena+0 airborne dash to row30 based on
`FUN_00445ee0` airborne directional branches (lines69–110). It still needs rebuilt
live validation. Rena's 300/311 selector/facing contract is no longer applied to other
combos; their pre-candidate aerial340 binding is retained, not newly declared faithful.
The broader selector/cancel-tree recovery stays in issue #66. Earlier fixed-time
captures are not evidence of correct aerial animation identity.

## Subsequent negative visual evidence

The rebuilt row30 dash bound tag54 without fallback at tick195. At tick208,
move311/tag40/Anim-84 elapsed13 had a live nonzero-radius volume and no contact.
**The user identified the live pose as the ground side-attack animation**, rejecting
it as the expected air-dash kick. The initial inconclusive pose is not upgraded.

A separate fresh session tested move340/tag88/Anim-36 after actual row30 dash.
Tick129 elapsed16 was inconclusive; the user requested more ticks. Exactly five
more ticks produced tick134 elapsed21, and **the user identified it as slash/wrong
attack**. Row340 is therefore also rejected for this context. These negative findings
supersede the earlier 311 success wording in candidate notes.

The visible renderer integration test passed exact100-tick advance, no gameplay
advance during rendering/evidence reads, ordered press/release edges, state and
move breakpoints, and a live volume breakpoint with no confirmed contact. This
validates control/evidence synchronization, **not the candidate animation**.
Its first attempt failed because clearing scheduled inputs before their release
prevented the expected release edge; the recipe was corrected to consume the
release before clearing. Debug mode now excludes focus-loss battle-menu pause,
which otherwise interfered with external tick control.

Source inspection now identifies `FUN_00445ee0:319–323` selecting move332 from
row30 with phase<2. This is the next bounded Rena+0 candidate; it needs live visual
validation rather than another prediction-only pass.

## Live user confirmation and further rejection

Fresh Rena+0 session: actual row30/tag54 aerial dash at tick113; Attack selected
332/tag83 at tick114. At tick130 the move reached phase1/tag84, elapsed5.
**The user explicitly confirmed the expected air-dash kick in the live window.**
This confirms that observed pose/context only; facing variants and full phase
transition fidelity remain separate gates.

In the same session, after landing and a new ordinary Jump, Attack selected
300/tag31 at tick239. At tick247 elapsed9 the user **rejected** it: it is a jump
slash but comes from the right, matching the regular grounded attack. The expected
ordinary-jump attack prepares the weapon on the left and cuts right. Therefore the
previous candidate's ordinary300 claims are also invalid. Row320 is the next
bounded candidate under live investigation, not yet a confirmed correction.

Ordinary row320 showed startup tag47 then gated approach tag81. The user
recognized the correct left-preparation startup but did not see the slash. The
attack exited before the slash phase: its generic contact-derived lifetime timer
preempted the gated section. The scoped runtime correction now keeps rows320/332
on their phase timelines and implements row320's explicit phase1 exit after tick10
at distance-squared<40000 or after tick25 (`FUN_0043ffc0:946–954`). Other unrecovered
mode/counter/approach callbacks remain unclaimed. Rebuilt slash-phase visual
confirmation is still required.

With the bounded phase-exit correction, move320 reached slash phase2/tag82 at
tick146 and elapsed4 at tick150. **The user confirmed the correct animation but
reported incorrect timing**, suggesting further RE is needed. This is a visual
identity confirmation, not a timing/parity pass. Issue31 must remain open.

Focused tests last run: debug protocol, fighter script and melee rules passed;
animation data failed two stale expectations still describing ordinary300. Those
expectations have been corrected to the new route but not yet rebuilt/rerun.
The full native suite and Linux/Windows/web final builds are still outstanding.

## Outstanding gates

- Complete rendered integration, breakpoint and lifecycle tests; strengthen snapshots.
- Recheck row30 dash pose and observe later, distinctive attack poses.
- Back/current facing and changed target bearing in both contexts, plus other-combo
  table smoke check and explicit user live-window confirmation.
- Required focused/full native suites, Linux/Windows/web builds and final diff review.
- Final exact evidence ledger and evidence-backed issue31 comment; leave issue OPEN.

## Landing verification (2026-10-12)

The outstanding build/test gates are closed on the exact tree described above:
rebuilt Linux suite **68/68 passed, zero failures/skips** (186.48 s), with
`animation_data_test` 83568 checks / 0 failures (the corrected 320/332 route now
green), `fighter_script_test` 1812 checks, `melee_rules_test` 236 checks and
`live_debug_test` green. Windows (MinGW) and web (Emscripten) cross-builds both
linked with exit 0; `live_debug.cpp`'s `__linux__` guards hold on both.

Tool assessment: the debugger itself needs no further code work — the protocol,
security boundary, evidence pipeline and the opt-in visible render integration
test are complete. What remains open are the owner-in-the-loop gates below
(row30 dash pose recheck, back/current facing and changed-bearing variants,
other-combo table smoke with explicit live-window confirmation) plus the
evidence-backed issue #31 comment. Issue #31 stays OPEN; move320's timing and
row332's facing variants remain unverified claims until those gates run.
