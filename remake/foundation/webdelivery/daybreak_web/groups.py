"""Loading groups: what the front end needs, versus what a match needs.

PORT DECISION, derived from the loaders rather than invented. The group lists in
``docs/WEB-DELIVERY-PLAN.md`` ("startup group" / "match group at the VS
transition") are expressed here as prefix and name rules whose provenance is the
code that actually opens the files:

  * The front end's own literals — ``data/title/``, ``data/select/``,
    ``data/vs/``, ``data/object/`` (shared HUD art, including P01.cnv),
    ``data/directX/``, ``data/sysse/``, ``data/chat/``, ``data/network/``,
    ``data/bgm/`` and ``movie/op.mpg`` — come from ``src/ui/screen_*.cpp``.
  * The match side is directory-scoped by the loaders themselves:
    ``xm::loadStage`` walks one ``data/stageNN/`` directory (models 00..07,
    ``collision*``, ``env.dat``), ``xm::loadCharacter`` one ``data/<char>``
    directory plus the costume siblings ``_B.._F``, and ``xm::loadWeapon``
    either ``data/bullet/%03d/`` or a ``data/item/`` model
    (``src/assets/scene.h``).
  * ``data/item/`` is in BOTH: the selection screens read weapon definitions to
    name and dress the menu, and the same files are the weapon's data at match
    time. It is small and shared, so it loads with the front end and the match
    needs no second copy.

Everything not matched by a rule is ``other``: it is fetched on demand and is
never part of a group manifest. That is the safe default — a name nobody
classified cannot become an accidental bulk download.
"""

from __future__ import annotations

from typing import Iterable, Sequence

#: Group names in the catalog.
STARTUP = "startup"
MATCH = "match"
OTHER = "other"

#: Loaded to reach and operate the front end (plan §"Startup group").
STARTUP_PREFIXES: tuple[str, ...] = (
    "data/title/",
    "data/select/",
    "data/vs/",
    "data/object/",
    "data/directX/",
    "data/sysse/",
    "data/chat/",
    "data/network/",
    "data/bgm/",
    "data/item/",
)

#: Exact names the startup group also needs.
STARTUP_NAMES: tuple[str, ...] = ("movie/op.mpg",)

#: Shared HUD/battle art the plan puts in the second group but which is fixed
#: (no stage or fighter in it), so it loads at startup with the rest of the HUD.
#: ``data/effect/`` holds the effect textures and ``data/object/`` the sheets.
SHARED_BATTLE_PREFIXES: tuple[str, ...] = ("data/effect/", "data/bullet/common/")


def classify(asset_id: str) -> str:
    """Return ``startup``, ``match`` or ``other`` for one logical asset id."""
    if asset_id in STARTUP_NAMES:
        return STARTUP
    for prefix in STARTUP_PREFIXES + SHARED_BATTLE_PREFIXES:
        if asset_id.startswith(prefix):
            return STARTUP
    return OTHER


#: Startup assets that are NOT part of the gate: the first usable screen does not
#: need them, and the plan is explicit that only what the first screen requires may
#: hold the client back (Step 4: "mark only assets required by the first usable
#: screen as the startup gate"). The opening movie is decoded by the browser rather
#: than by wasm (movie_player.cpp's web stub), and BGM is streamed by the audio path
#: instead of being decoded from memory, so neither gates the front end even though
#: both are fetched at startup.
GATE_EXCLUDED_PREFIXES: tuple[str, ...] = ("movie/", "data/bgm/")


def is_gate(asset_id: str) -> bool:
    """True when the client must hold this asset before the first usable screen."""
    return classify(asset_id) == STARTUP and not any(
        asset_id.startswith(prefix) for prefix in GATE_EXCLUDED_PREFIXES)


def match_prefixes(stage: str, slots: Sequence[str]) -> list[str]:
    """The directory prefixes a match pulls in, from the loader scopes.

    ``stage`` is a stage directory name (``stage21``); each slot is
    ``character[:costume]`` with the costume index selecting the ``_B.._F``
    sibling the character loader reads alongside the base directory.

    Characters are always paired with a weapon at the call site — the front end
    never launches a bare fighter (issue #26) — so this function takes the
    fighter half only and the caller supplies the weapon directories through
    ``extra`` on :func:`match_asset_ids`.
    """
    prefixes = [f"data/{stage}/"]
    for slot in slots:
        character = slot.split(":", 1)[0]
        costume = 0
        if ":" in slot:
            try:
                costume = int(slot.split(":", 1)[1])
            except ValueError:
                costume = 0
        suffixes = {""} | {"_B", "_C", "_D", "_E", "_F"}
        if 1 <= costume <= 5:
            # Only the selected costume's sibling directory is needed.
            suffixes = {"", "_BCDEF"[costume - 1]}
        for suffix in suffixes:
            prefixes.append(f"data/{character}{suffix}/")
    return prefixes


def match_asset_ids(catalog_assets: Iterable[dict], stage: str, slots: Sequence[str],
                    weapons: Sequence[str] = ()) -> list[str]:
    """Catalog ids for one confirmed match, sorted.

    ``weapons`` are the selected weapon slots as ``%03d`` directory numbers
    (``081``) or ``item/NN`` ids; the caller resolves them from the selection,
    and this function only maps them to the loader's two weapon shapes.
    """
    prefixes = match_prefixes(stage, slots)
    for weapon in weapons:
        if weapon.startswith("item/"):
            prefixes.append(f"data/{weapon}")
        else:
            prefixes.append(f"data/bullet/{weapon}/")
    ids = []
    for asset in catalog_assets:
        asset_id = asset["id"]
        if any(asset_id.startswith(prefix) for prefix in prefixes):
            ids.append(asset_id)
    return sorted(set(ids))
