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

Then put the address in the game: `server = 203.0.113.10:37565` under `[network]` in the settings file, or
the SERVER row of the online menu.

## What it keeps

In memory, and only until a minute after the host last asked: each room's code, an ID the client made up, and the
host's public and private addresses. Addresses are not logged.

## Limits

- 20 joins per minute per IP address, against guessing codes.
- IPv4 only.
- Routers that give each destination a different port, which is symmetric NAT, cannot be punched through. The
  game says which players could not connect, and a relay would be the fix.
