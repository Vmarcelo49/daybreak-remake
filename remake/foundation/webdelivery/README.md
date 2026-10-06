# Self-hosted web asset delivery (issue #4)

A host supplies their own Higurashi Daybreak installation. This service prepares it
once into a persistent directory, then serves the web client and **individual assets**
from one origin. A browser downloads only what the current screen needs, validates
every asset against the catalog's sha256, and caches each one independently.

Game data never enters Git, the image, or this directory: the install is mounted
read-only, the prepared tree is a volume, and `prepare` writes a `.gitignore` into its
own output so the data stays untracked wherever the host puts it.

## Quick start (Docker)

```bash
export DAYBREAK_INSTALL=/path/to/Higurashi-Daybreak   # the folder with daybreak00.dat

# once: build the web client, then copy it into the Docker context
(cd .. && ./build.sh web)
./scripts/package-client.sh ../build/web

docker compose up --build          # prepare, then serve, on http://localhost:8080/
```

Open <http://localhost:8080/> and follow *Start the client*. That link is
`/client/foundation_demo.html?delivery=1`, which turns on the per-asset delivery client
and materialises the delivered assets at the paths the port's own asset layer already
reads (`data/...`, `movie/...`).

Re-running `docker compose up` reuses the volume: `prepare` sees the same install
(sizes and mtimes) and reports "up to date" instead of re-extracting ~2 GB.

## Quick start (no Docker)

```bash
python3 -m daybreak_web prepare --install /path/to/Higurashi-Daybreak --out ./web-data
python3 -m daybreak_web serve   --out ./web-data --client ../build/web --port 8080
```

`python3 -m daybreak_web --help` lists every command. The service is stdlib-only;
there is nothing to install.

## The commands

| Command | What it does |
|---|---|
| `prepare` | Reads the host's `.DAT` archives, writes the **winning** copy of every asset into `--out`, precompresses what gzip actually helps, and writes `catalog.json`. Repeatable: an unchanged install is reused, not re-extracted. |
| `verify` | Re-hashes the prepared tree against the catalog. |
| `order` | Prints which archive wins for every logical name (read-only; this is also the oracle the native ordering test compares against). |
| `measure` | Transfer sizes per extension and per loading group, from the catalog. |
| `serve` | The same-origin HTTP surface: client, catalog, manifests, one asset per request. |

Useful options: `--include <prefix>` (prepare only part of the install),
`--hash-copies` (also hash the losing duplicate copies, which is what proves how many
duplicate groups differ in bytes), `--gzip auto|off`. `measure --match` takes
`stage/fighters/weapons` — slashes, because a fighter spec carries its own colon
(`stage21/rena:0,mion:0/001,002`).

## The HTTP surface

| Route | Answer |
|---|---|
| `GET /` | A small index that points at the client and reports preparation status. |
| `GET /client/<file>` | The built web client (wasm/js/html/data), same origin. |
| `GET /api/health` | Catalog version, asset count, prepared and transfer bytes. `503` when nothing is prepared. |
| `GET /api/catalog` | The versioned catalog as JSON, with `ETag`/`304`. |
| `GET /api/manifest/startup` | The startup group, one line per asset. |
| `GET /api/manifest/match?stage=stage21&slot=rena:0&slot=mion:0&weapon=001` | The dependency set for a confirmed match. |
| `GET /api/asset/<logical-id>` | One asset. `ETag` is its sha256, `Cache-Control: immutable`, gzip when the catalog has a compressed copy. |

Only catalogued ids are reachable — the request's own bytes never become a filesystem
path, so there is nothing to traverse. A missing asset is `404 unknown-asset`; an
install that no longer matches the catalog is `409 incompatible-install`.

## What `prepare` guarantees

The winning copy is the one the **game** reads, not the one an alphabetical extraction
happens to leave behind. The archive order, duplicate resolution and case-insensitive
matching are the rules the original executable implements and the native asset layer
ports (`src/assets/dat_bundle.cpp`): bundles are searched in registration order
(`daybreak07`, `04`, `00`, `05`, `02`, `06`), first match wins, and a lookup is exact
first and then ASCII-case-insensitive. `remake/foundation/tests/web_catalog_order.cpp`
compares this service's ordering against the native reader's — 11,261 names and 983
duplicate names on a real install, and a synthetic install that needs no game data.

Losing copies are recorded in the catalog, never written. `--hash-copies` measures how
many duplicate groups actually differ in bytes.

## Loading groups

`startup` assets reach and operate the front end; `match` assets are the selected
stage, fighters and weapons; everything else is `other` and is only ever fetched on
demand. Within startup, the manifest marks **gate** assets — the ones the first usable
screen needs. The opening movie and BGM are fetched at startup but are not gate assets:
the browser decodes the movie rather than wasm, and BGM is streamed, so neither may hold
the front end back.

## Compression

`prepare` keeps a gzip copy only where it measurably helps, and records the size in the
catalog, so the transfer cost is a number in the catalog rather than a guess at serve
time. Measured on a real install (`measure`):

| extension | raw | transfer | ratio |
|---|---|---|---|
| `.x` (models) | 215.2 MB | 100.8 MB | 0.468 |
| `.cnv` (textures/audio containers) | 186.9 MB | 186.9 MB | 1.000 |
| `.mpg` (movies) | 1641.2 MB | 1641.2 MB | 1.000 |
| `.ogg` (music) | 50.3 MB | 50.3 MB | 1.000 |

Already-compressed containers are skipped, models are compressed, and no custom codec
was needed — which is why LZ4 was not adopted.

## Notes

- **HTTPS**: put a standard reverse proxy in front; nothing here assumes plain HTTP
  beyond the container's own port.
- **One host, one install.** There is no auth, no multi-tenancy and no hosting of game
  data; that is the issue's stated scope boundary.
- **Browser storage is best effort.** If IndexedDB is unavailable the session runs
  uncached instead of failing.
