// Package main — the rendezvous server for Higurashi Daybreak's online play.
//
// It only introduces: a host gets a room code, and a joiner with that code learns the host's public and
// private addresses while the host learns the joiner's. Both then send to each other, which opens their
// routers, and the rest of the room's links form from what the host's lobby tells everyone. No game
// packet ever passes through here.
//
// Adapted from the signaling-only relay in Vmarcelo49/ReCaster, server/. That one uses TCP for signaling
// and pairs two peers. This one is UDP only and takes up to a full room, because a game client already
// resends everything and has only the one socket whose address matters.
//
// Usage:
//
//	daybreak-rendezvous [-addr :37565] [-log info]
//
// Flags can also be set by environment: DAYBREAK_RENDEZVOUS_ADDR and DAYBREAK_LOG_LEVEL.
package main

import (
	"context"
	"encoding/binary"
	"flag"
	"log"
	"math/rand"
	"net"
	"net/netip"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func main() {
	var (
		addr     = flag.String("addr", getenvDefault("DAYBREAK_RENDEZVOUS_ADDR", ":37565"), "UDP listen address")
		logLevel = flag.String("log", getenvDefault("DAYBREAK_LOG_LEVEL", "info"), "log level (debug, info or error)")
	)
	flag.Parse()
	level, err := parseLogLevel(*logLevel)
	if err != nil {
		log.Fatalf("%v", err)
	}
	logger := newServerLogger(level)

	conn, err := net.ListenPacket("udp4", *addr)
	if err != nil {
		logger.Errorf("cannot listen on %s: %v", *addr, err)
		os.Exit(1)
	}
	defer conn.Close()
	logger.Infof("daybreak-rendezvous listening on %s", conn.LocalAddr())

	ctx, cancel := signal.NotifyContext(context.Background(), syscall.SIGINT, syscall.SIGTERM)
	defer cancel()
	go func() {
		<-ctx.Done()
		conn.Close()
	}()
	serve(ctx, conn.(*net.UDPConn), newRooms(rand.Int), logger)
	logger.Infof("daybreak-rendezvous stopped")
}

func serve(ctx context.Context, conn *net.UDPConn, known *rooms, logger *serverLogger) {
	go func() {
		ticker := time.NewTicker(10 * time.Second)
		defer ticker.Stop()
		for {
			select {
			case <-ctx.Done():
				return
			case now := <-ticker.C:
				known.sweep(now)
				logger.Debugf("%d rooms", known.count())
			}
		}
	}()

	buffer := make([]byte, 2048)
	for {
		size, from, err := conn.ReadFromUDPAddrPort(buffer)
		if err != nil {
			if ctx.Err() != nil {
				return
			}
			logger.Errorf("read: %v", err)
			continue
		}
		handle(conn, known, buffer[:size], from, time.Now(), logger)
	}
}

func handle(conn *net.UDPConn, known *rooms, packet []byte, from netip.AddrPort, now time.Time, logger *serverLogger) {
	req, ok := parseRequest(packet)
	if !ok || !from.Addr().Unmap().Is4() {
		return
	}
	ip := from.Addr().Unmap().As4()
	public := makeEndpoint(ip, from.Port())
	send := func(to netip.AddrPort, answer []byte) { conn.WriteToUDPAddrPort(answer, to) }

	if req.version != protocolVersion {
		send(from, answerError(failVersion))
		return
	}
	switch req.kind {
	case kindHost:
		if hosted := known.host(req.clientID, public, req.private, now); hosted != nil {
			send(from, answerHosted(hosted.code, public))
		}
	case kindJoin:
		if !known.allowJoin(ip, now) {
			send(from, answerError(failTooManyTries))
			return
		}
		found := known.find(req.code, now)
		if found == nil {
			send(from, answerError(failNoRoom))
			return
		}
		logger.Debugf("join %s", req.code)
		send(from, answerRoom(found.public, found.private, public))
		send(endpointAddr(found.public), answerJoiner(public, req.private))
	}
}

func endpointAddr(e endpoint) netip.AddrPort {
	return netip.AddrPortFrom(netip.AddrFrom4([4]byte(e[:4])), binary.BigEndian.Uint16(e[4:]))
}

func getenvDefault(key, def string) string {
	if v := os.Getenv(key); v != "" {
		return v
	}
	return def
}
