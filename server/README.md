# Rendezvous server

Introduces online players so they can connect without forwarding a port. A host gets a 4-letter room code, and
a joiner with that code learns the host's public and private addresses while the host learns the joiner's. **No
game packet passes through it.** Adapted from the relay in `Vmarcelo49/ReCaster`, `server/`. It uses UDP only and
takes a full room of up to 4.

## Run it

Any machine with a public IPv4 address, and UDP port 37565 open:

```bash
cd server
docker compose up -d
```

Without Docker, with Go 1.22 or later:

```bash
cd server
go build -o daybreak-rendezvous .
./daybreak-rendezvous -addr :37565 -log info
```

To publish another port, put `DAYBREAK_PUBLIC_PORT=3939` in a `.env` file beside `docker-compose.yml`.

The game uses the project's own server by default. To use yours, put the address in the game: `server = 203.0.113.10:37565` under `[network]` in the settings file, or
the SERVER row of the online menu.

## What it keeps

In memory, and only until a minute after the host last asked: each room's code, an ID the client made up, the
host's public and private addresses, and a random 128-bit renewal secret issued to the host alone (issue #126).
Addresses and secrets are not logged. Renewing a live room requires that secret, so knowing the client ID — which
every room member sees — is not enough to redirect it. With no live room, any request starts a fresh room and secret,
which is what happens after a server restart or an expiry.

## Limits

- 20 joins per minute and 240 host requests per minute per IP address, against guessing codes and renewal secrets.
- Hosting needs protocol version 2; version-1 hosts are refused, but version-1 joins are still accepted so released
  clients can join and play. An updated client falls back to version 1 for its lobby if the server refuses version 2.
- The renewal secret is a bearer token: someone who observes the host's traffic to the server can still renew the
  room. UDP spoofing and on-path capture are not fixed. See `docs/ONLINE-PLAN.md` for the full trust model.
- IPv4 only.
- Routers that give each destination a different port, which is symmetric NAT, cannot be punched through. The
  game says which players could not connect, and a relay would be the fix.
