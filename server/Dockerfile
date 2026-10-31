# Multi-stage build for the rendezvous server, as in ReCaster's relay.
#
#   docker build -t daybreak-rendezvous ./server
#   docker run -d --name daybreak-rendezvous -p 37565:37565/udp --restart unless-stopped daybreak-rendezvous
FROM golang:1.22-alpine AS builder
WORKDIR /app
COPY go.mod ./
COPY . .
RUN CGO_ENABLED=0 go build -ldflags="-s -w" -o /daybreak-rendezvous .

FROM scratch
COPY --from=builder /daybreak-rendezvous /daybreak-rendezvous
EXPOSE 37565/udp
ENTRYPOINT ["/daybreak-rendezvous"]
