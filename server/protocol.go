// Package main — the rendezvous server's wire format. src/net/lobby.cpp is the other side.
//
// Everything is UDP on one port, because the point is to see the address of the socket the game plays
// from. A lost packet costs nothing: clients keep asking until they get an answer.
package main

import "encoding/binary"

const (
	// Version 2 authenticates room renewal with a server-issued secret: the client ID alone is
	// public to every room member, so it cannot prove ownership (issue #126, owner-approved
	// Option B 2026-11-19). Version 1 is the released 1.0.x protocol, kept for joins only.
	protocolVersion = 2
	legacyVersion   = 1
	codeLength      = 4
	// No I, O, 0 or 1, which read alike when shared aloud.
	codeAlphabet = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789"

	// A request is at least as large as any answer, so the server cannot amplify a forged sender.
	requestSize = 48
	addressSize = 6
	// 128 bits, so guessing a renewal secret is infeasible even without the rate limit.
	secretSize = 16
	// The secret rides in the request's padding, so the request stays 48 bytes.
	secretOffset = 21
)

var requestMagic = [4]byte{'D', 'B', 'R', '1'}

const (
	kindHost = 'H'
	kindJoin = 'J'

	answerPrefix = 'R'
	kindHosted   = 'h'
	kindRoom     = 'j'
	kindJoiner   = 'n'
	kindError    = 'x'
)

type failure byte

const (
	failNoRoom       failure = 1
	failVersion      failure = 2
	failTooManyTries failure = 3
	// A host request whose secret does not match the live room's. The room is left untouched.
	failUnauthorized failure = 4
)

// endpoint is an IPv4 address and port, as the wire carries them.
type endpoint [addressSize]byte

func makeEndpoint(ip [4]byte, port uint16) endpoint {
	var e endpoint
	copy(e[:4], ip[:])
	binary.BigEndian.PutUint16(e[4:], port)
	return e
}

type request struct {
	kind     byte
	version  uint16
	clientID uint32
	private  endpoint
	code     string
	secret   [secretSize]byte
}

// parseRequest refuses anything that is not exactly a request, since these bytes come from strangers.
// Layout: magic(4) kind(1) version(2 LE) clientID(4 LE) private(6) code(4, join only)
// secret(16 bytes, host only, at offsets 21..36) padding(to 48).
func parseRequest(packet []byte) (request, bool) {
	var r request
	if len(packet) != requestSize || [4]byte(packet[:4]) != requestMagic {
		return r, false
	}
	r.kind = packet[4]
	if r.kind != kindHost && r.kind != kindJoin {
		return r, false
	}
	r.version = binary.LittleEndian.Uint16(packet[5:])
	r.clientID = binary.LittleEndian.Uint32(packet[7:])
	copy(r.private[:], packet[11:])
	if r.kind == kindJoin {
		r.code = string(packet[17 : 17+codeLength])
	} else {
		copy(r.secret[:], packet[secretOffset:secretOffset+secretSize])
	}
	return r, true
}

// answerHosted tells a host its code, its public endpoint, and the secret it must echo to renew
// the room. The secret goes to the host alone: room and joiner answers never carry it.
func answerHosted(code string, public endpoint, secret [secretSize]byte) []byte {
	out := []byte{answerPrefix, kindHosted}
	out = append(out, code...)
	out = append(out, public[:]...)
	return append(out, secret[:]...)
}

func answerRoom(hostPublic, hostPrivate, yourPublic endpoint) []byte {
	out := []byte{answerPrefix, kindRoom}
	out = append(out, hostPublic[:]...)
	out = append(out, hostPrivate[:]...)
	return append(out, yourPublic[:]...)
}

func answerJoiner(public, private endpoint) []byte {
	out := []byte{answerPrefix, kindJoiner}
	out = append(out, public[:]...)
	return append(out, private[:]...)
}

func answerError(why failure) []byte {
	return []byte{answerPrefix, kindError, byte(why)}
}
