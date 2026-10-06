# The self-hosted delivery service: the web client and the asset API, one origin.
#
# What the image contains: this server and the built web client. What it does NOT
# contain, by construction: any game data. The host's install is mounted read-only at
# run time and the prepared tree lives in a volume, so `docker history` on this image
# can never show a game file — which is the issue's "keep game data out of Git and the
# Docker image" rule expressed as a property of the build rather than a promise.
#
# Build context is this directory, so the only way the client gets in is
# scripts/package-client.sh (which copies the emcc output into client/). The install
# is not in the context and could not be copied even by mistake.
FROM python:3.12-slim

# The service is stdlib-only on purpose: a pinned base image plus zero dependencies is
# a smaller attack surface and a reproducible build without a lockfile.
ENV PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1

WORKDIR /app
COPY daybreak_web/ /app/daybreak_web/
COPY client/ /app/client/

# The prepared tree is a volume: prepared once, reused on every restart.
VOLUME ["/data"]
EXPOSE 8080

# A host that forgot to prepare gets a clear 503 from /api/health instead of a
# container that looks healthy and serves nothing.
HEALTHCHECK --interval=30s --timeout=5s --start-period=5s --retries=3 \
    CMD python3 -c "import urllib.request,sys; \
sys.exit(0 if urllib.request.urlopen('http://127.0.0.1:8080/api/health', timeout=4).status==200 else 1)"

ENTRYPOINT ["python3", "-m", "daybreak_web"]
CMD ["serve", "--out", "/data", "--client", "/app/client", "--port", "8080"]
