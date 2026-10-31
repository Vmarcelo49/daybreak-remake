// Package main — the rendezvous server's wire format. src/net/rendezvous.cpp is the other side.
//
// Everything is UDP on one port, because the point is to see the address of the socket the game plays
// from. A lost packet costs nothing: clients keep asking until they get an answer.
package main

import "encoding/binary"

const (
	protocolVersion = 1
	codeLength      = 4
	// No I, O, 0 or 1, which read alike when shared aloud.
	codeAlphabet = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789"

	// A request is at least as large as any answer, so the server cannot amplify a forged sender.
	requestSize = 48
	addressSize = 6
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
}

// parseRequest refuses anything that is not exactly a request, since these bytes come from strangers.
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
	}
	return r, true
}

func answerHosted(code string, public endpoint) []byte {
	out := []byte{answerPrefix, kindHosted}
	out = append(out, code...)
	return append(out, public[:]...)
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
