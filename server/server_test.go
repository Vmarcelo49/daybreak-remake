package main

import (
	"context"
	"encoding/binary"
	"net"
	"testing"
	"time"
)

func request_(kind byte, version uint16, clientID uint32, private endpoint, code string) []byte {
	out := make([]byte, requestSize)
	copy(out, requestMagic[:])
	out[4] = kind
	binary.LittleEndian.PutUint16(out[5:], version)
	binary.LittleEndian.PutUint32(out[7:], clientID)
	copy(out[11:], private[:])
	copy(out[17:], code)
	return out
}

func startServer(t *testing.T) *net.UDPAddr {
	t.Helper()
	conn, err := net.ListenUDP("udp4", &net.UDPAddr{IP: net.IPv4(127, 0, 0, 1)})
	if err != nil {
		t.Fatal(err)
	}
	ctx, cancel := context.WithCancel(context.Background())
	t.Cleanup(func() {
		cancel()
		conn.Close()
	})
	next := 0
	known := newRooms(func() int { next++; return next * 7 })
	go serve(ctx, conn, known, newServerLogger(levelError))
	return conn.LocalAddr().(*net.UDPAddr)
}

func client(t *testing.T, server *net.UDPAddr) *net.UDPConn {
	t.Helper()
	conn, err := net.DialUDP("udp4", nil, server)
	if err != nil {
		t.Fatal(err)
	}
	t.Cleanup(func() { conn.Close() })
	return conn
}

func exchange(t *testing.T, conn *net.UDPConn, packet []byte) []byte {
	t.Helper()
	if packet != nil {
		if _, err := conn.Write(packet); err != nil {
			t.Fatal(err)
		}
	}
	buffer := make([]byte, 128)
	conn.SetReadDeadline(time.Now().Add(2 * time.Second))
	size, err := conn.Read(buffer)
	if err != nil {
		t.Fatalf("no answer: %v", err)
	}
	return buffer[:size]
}

func TestHostGetsTheSameRoomEachTime(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	first := exchange(t, host, request_(kindHost, protocolVersion, 7, endpoint{}, ""))
	second := exchange(t, host, request_(kindHost, protocolVersion, 7, endpoint{}, ""))
	if first[1] != kindHosted || string(first[2:6]) != string(second[2:6]) {
		t.Fatalf("rooms differ: %q and %q", first, second)
	}
	public := host.LocalAddr().(*net.UDPAddr)
	if binary.BigEndian.Uint16(first[10:]) != uint16(public.Port) {
		t.Fatalf("the host was not told its address: %v", first)
	}
}

func TestEveryJoinerMeetsTheHost(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	hosted := exchange(t, host, request_(kindHost, protocolVersion, 1, endpoint{192, 168, 0, 2, 0, 9}, ""))
	code := string(hosted[2:6])

	for id := uint32(2); id <= 4; id++ {
		joiner := client(t, server)
		private := endpoint{10, 0, 0, byte(id), 0, 9}
		answer := exchange(t, joiner, request_(kindJoin, protocolVersion, id, private, code))
		if answer[1] != kindRoom {
			t.Fatalf("joiner %d: %v", id, answer)
		}
		if answer[8] != 192 || answer[11] != 2 {
			t.Fatalf("joiner %d did not get the host's private address: %v", id, answer)
		}
		notice := exchange(t, host, nil)
		if notice[1] != kindJoiner || notice[11] != byte(id) {
			t.Fatalf("host did not hear of joiner %d: %v", id, notice)
		}
		port := joiner.LocalAddr().(*net.UDPAddr).Port
		if binary.BigEndian.Uint16(notice[6:]) != uint16(port) {
			t.Fatalf("host got the wrong public address for joiner %d", id)
		}
	}
}

func TestRefusals(t *testing.T) {
	server := startServer(t)
	joiner := client(t, server)
	if got := exchange(t, joiner, request_(kindJoin, protocolVersion, 1, endpoint{}, "ZZZZ")); got[1] != kindError || failure(got[2]) != failNoRoom {
		t.Fatalf("a wrong code: %v", got)
	}
	if got := exchange(t, joiner, request_(kindJoin, protocolVersion+1, 1, endpoint{}, "ZZZZ")); got[1] != kindError || failure(got[2]) != failVersion {
		t.Fatalf("a wrong version: %v", got)
	}
	var last []byte
	for i := 0; i <= joinsPerMinute; i++ {
		last = exchange(t, joiner, request_(kindJoin, protocolVersion, 1, endpoint{}, "ZZZZ"))
	}
	if last[1] != kindError || failure(last[2]) != failTooManyTries {
		t.Fatalf("guessing was not limited: %v", last)
	}
}

func TestMalformedPacketsGetNoAnswer(t *testing.T) {
	server := startServer(t)
	stranger := client(t, server)
	good := request_(kindHost, protocolVersion, 1, endpoint{}, "")
	badMagic := append([]byte{}, good...)
	badMagic[0] = 'X'
	badKind := append([]byte{}, good...)
	badKind[4] = 'Q'
	for _, packet := range [][]byte{{}, {1}, good[:47], append(append([]byte{}, good...), 0), badMagic, badKind} {
		stranger.Write(packet)
	}
	buffer := make([]byte, 128)
	stranger.SetReadDeadline(time.Now().Add(200 * time.Millisecond))
	if size, err := stranger.Read(buffer); err == nil {
		t.Fatalf("answered a malformed packet: %v", buffer[:size])
	}
}

func TestNoAnswerIsLargerThanARequest(t *testing.T) {
	var e endpoint
	for _, answer := range [][]byte{answerHosted("ABCD", e), answerRoom(e, e, e), answerJoiner(e, e), answerError(failNoRoom)} {
		if len(answer) > requestSize {
			t.Fatalf("an answer of %d bytes amplifies", len(answer))
		}
	}
}

func TestRoomsExpire(t *testing.T) {
	now := time.Now()
	known := newRooms(func() int { return 3 })
	hosted := known.host(1, endpoint{}, endpoint{}, now)
	if known.find(hosted.code, now.Add(roomLifetime-time.Second)) == nil {
		t.Fatal("a live room was not found")
	}
	if known.find(hosted.code, now.Add(roomLifetime)) != nil {
		t.Fatal("an expired room was found")
	}
	known.sweep(now.Add(roomLifetime))
	if known.count() != 0 {
		t.Fatal("sweep kept an expired room")
	}
}
