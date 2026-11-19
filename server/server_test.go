package main

import (
	"context"
	"encoding/binary"
	"net"
	"testing"
	"time"
)

func request_(kind byte, version uint16, clientID uint32, private endpoint, code string, secret [secretSize]byte) []byte {
	out := make([]byte, requestSize)
	copy(out, requestMagic[:])
	out[4] = kind
	binary.LittleEndian.PutUint16(out[5:], version)
	binary.LittleEndian.PutUint32(out[7:], clientID)
	copy(out[11:], private[:])
	copy(out[17:], code)
	copy(out[secretOffset:], secret[:])
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

func hostedSecret(t *testing.T, hosted []byte) [secretSize]byte {
	t.Helper()
	if len(hosted) != 2+codeLength+addressSize+secretSize || hosted[1] != kindHosted {
		t.Fatalf("not a hosted answer: %v", hosted)
	}
	var secret [secretSize]byte
	copy(secret[:], hosted[2+codeLength+addressSize:])
	return secret
}

func TestHostGetsTheSameRoomEachTime(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	first := exchange(t, host, request_(kindHost, protocolVersion, 7, endpoint{}, "", [secretSize]byte{}))
	secret := hostedSecret(t, first)
	second := exchange(t, host, request_(kindHost, protocolVersion, 7, endpoint{}, "", secret))
	if second[1] != kindHosted || string(first[2:6]) != string(second[2:6]) {
		t.Fatalf("rooms differ: %q and %q", first, second)
	}
	if hostedSecret(t, second) != secret {
		t.Fatal("a renewal rotated the secret")
	}
	public := host.LocalAddr().(*net.UDPAddr)
	if binary.BigEndian.Uint16(first[10:]) != uint16(public.Port) {
		t.Fatalf("the host was not told its address: %v", first)
	}
}

func TestEveryJoinerMeetsTheHost(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	hosted := exchange(t, host, request_(kindHost, protocolVersion, 1, endpoint{192, 168, 0, 2, 0, 9}, "", [secretSize]byte{}))
	code := string(hosted[2:6])

	for id := uint32(2); id <= 4; id++ {
		// Released clients join with version 1; updated ones with version 2. Both are welcome.
		version := uint16(legacyVersion)
		if id == 4 {
			version = protocolVersion
		}
		joiner := client(t, server)
		private := endpoint{10, 0, 0, byte(id), 0, 9}
		answer := exchange(t, joiner, request_(kindJoin, version, id, private, code, [secretSize]byte{}))
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
	if got := exchange(t, joiner, request_(kindJoin, protocolVersion, 1, endpoint{}, "ZZZZ", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failNoRoom {
		t.Fatalf("a wrong code: %v", got)
	}
	if got := exchange(t, joiner, request_(kindJoin, legacyVersion, 1, endpoint{}, "ZZZZ", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failNoRoom {
		t.Fatalf("a released client's join: %v", got)
	}
	if got := exchange(t, joiner, request_(kindJoin, protocolVersion+1, 1, endpoint{}, "ZZZZ", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failVersion {
		t.Fatalf("a wrong version: %v", got)
	}
	// Hosting without the authenticated protocol is refused: a version-1 request carries no
	// renewal secret, and the client ID alone is public (issue #126).
	if got := exchange(t, joiner, request_(kindHost, legacyVersion, 1, endpoint{}, "", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failVersion {
		t.Fatalf("a v1 host request: %v", got)
	}
	if got := exchange(t, joiner, request_(kindHost, 0, 1, endpoint{}, "", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failVersion {
		t.Fatalf("a version-0 host request: %v", got)
	}
	var last []byte
	for i := 0; i <= joinsPerMinute; i++ {
		last = exchange(t, joiner, request_(kindJoin, protocolVersion, 1, endpoint{}, "ZZZZ", [secretSize]byte{}))
	}
	if last[1] != kindError || failure(last[2]) != failTooManyTries {
		t.Fatalf("guessing was not limited: %v", last)
	}
}

func TestMalformedPacketsGetNoAnswer(t *testing.T) {
	server := startServer(t)
	stranger := client(t, server)
	good := request_(kindHost, protocolVersion, 1, endpoint{}, "", [secretSize]byte{})
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
	var s [secretSize]byte
	answers := [][]byte{answerHosted("ABCD", e, s), answerRoom(e, e, e), answerJoiner(e, e), answerError(failNoRoom)}
	sizes := []int{28, 20, 14, 3}
	for i, answer := range answers {
		if len(answer) != sizes[i] {
			t.Fatalf("answer %d is %d bytes, want %d", i, len(answer), sizes[i])
		}
		if len(answer) > requestSize {
			t.Fatalf("an answer of %d bytes amplifies", len(answer))
		}
	}
}

func TestWireLayout(t *testing.T) {
	private := endpoint{192, 168, 0, 2, 0x12, 0x34}
	var secret [secretSize]byte
	for i := range secret {
		secret[i] = byte(i + 1)
	}
	packet := request_(kindHost, protocolVersion, 0x11223344, private, "", secret)
	if len(packet) != requestSize {
		t.Fatalf("a request is %d bytes", len(packet))
	}
	req, ok := parseRequest(packet)
	if !ok || req.kind != kindHost || req.version != protocolVersion || req.clientID != 0x11223344 || req.private != private || req.secret != secret {
		t.Fatalf("host request round trip: %+v", req)
	}
	// The padding past the secret is unused, so a client may leave anything there.
	for i := secretOffset + secretSize; i < requestSize; i++ {
		packet[i] = 0xff
	}
	if again, ok := parseRequest(packet); !ok || again.secret != secret {
		t.Fatal("padding changed the parsed secret")
	}
	join := request_(kindJoin, protocolVersion, 5, private, "ABCD", [secretSize]byte{})
	if req, ok := parseRequest(join); !ok || req.code != "ABCD" {
		t.Fatalf("join request round trip: %+v", req)
	}
	public := endpoint{203, 0, 113, 7, 0x99, 0x88}
	hosted := answerHosted("ABCD", public, secret)
	if len(hosted) != 28 || hosted[0] != answerPrefix || hosted[1] != kindHosted ||
		string(hosted[2:6]) != "ABCD" || endpoint(hosted[6:12]) != public || [secretSize]byte(hosted[12:28]) != secret {
		t.Fatalf("hosted answer layout: %v", hosted)
	}
}

// Issue #126: a stranger who knows only the host ID cannot renew or redirect a live room, whether
// it guesses a secret, sends none, or speaks the released protocol.
func TestUnauthorizedRenewalIsRejected(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	hosted := exchange(t, host, request_(kindHost, protocolVersion, 7, endpoint{192, 168, 0, 2, 0, 9}, "", [secretSize]byte{}))
	code := string(hosted[2:6])
	secret := hostedSecret(t, hosted)
	hostPort := uint16(host.LocalAddr().(*net.UDPAddr).Port)

	attacker := client(t, server)
	wrong := secret
	wrong[0] ^= 0xff
	for _, guess := range [][secretSize]byte{wrong, {}} {
		got := exchange(t, attacker, request_(kindHost, protocolVersion, 7, endpoint{203, 0, 113, 7, 0, 9}, "", guess))
		if got[1] != kindError || failure(got[2]) != failUnauthorized {
			t.Fatalf("a stranger renewed the room: %v", got)
		}
	}
	if got := exchange(t, attacker, request_(kindHost, legacyVersion, 7, endpoint{}, "", [secretSize]byte{})); got[1] != kindError || failure(got[2]) != failVersion {
		t.Fatalf("a v1 host request was not refused: %v", got)
	}
	// The room still points at the legitimate host, not at the stranger's endpoint.
	joiner := client(t, server)
	room := exchange(t, joiner, request_(kindJoin, protocolVersion, 8, endpoint{}, code, [secretSize]byte{}))
	if room[1] != kindRoom || binary.BigEndian.Uint16(room[6:]) != hostPort {
		t.Fatalf("the room was redirected: %v", room)
	}
}

// Issue #126 acceptance: the legitimate host renews through a normal address change. The secret,
// not the source address, is what proves ownership.
func TestLegitimateRenewalFromAChangedAddress(t *testing.T) {
	server := startServer(t)
	first := client(t, server)
	hosted := exchange(t, first, request_(kindHost, protocolVersion, 7, endpoint{}, "", [secretSize]byte{}))
	code := string(hosted[2:6])
	secret := hostedSecret(t, hosted)

	moved := client(t, server)
	renewed := exchange(t, moved, request_(kindHost, protocolVersion, 7, endpoint{}, "", secret))
	if renewed[1] != kindHosted || string(renewed[2:6]) != code {
		t.Fatalf("the legitimate host lost its room: %v", renewed)
	}
	joiner := client(t, server)
	room := exchange(t, joiner, request_(kindJoin, protocolVersion, 8, endpoint{}, code, [secretSize]byte{}))
	movedPort := uint16(moved.LocalAddr().(*net.UDPAddr).Port)
	if room[1] != kindRoom || binary.BigEndian.Uint16(room[6:]) != movedPort {
		t.Fatalf("the room kept the old address: %v", room)
	}
}

func TestUnauthorizedRenewalChangesNothing(t *testing.T) {
	now := time.Now()
	known := newRooms(func() int { return 3 })
	public := endpoint{192, 0, 2, 1, 0, 9}
	created, why := known.host(1, [secretSize]byte{}, public, endpoint{}, now)
	if why != 0 || created == nil {
		t.Fatalf("no room: %v", why)
	}
	attacker := endpoint{203, 0, 113, 7, 0, 9}
	if _, why := known.host(1, [secretSize]byte{1}, attacker, endpoint{}, now.Add(10*time.Second)); why != failUnauthorized {
		t.Fatalf("a wrong secret was not refused: %v", why)
	}
	found := known.find(created.code, now.Add(10*time.Second))
	if found == nil || found.public != public {
		t.Fatal("the room was redirected")
	}
	// lastSeen was not refreshed either: the room still expires a minute after the legitimate ask.
	if known.find(created.code, now.Add(roomLifetime)) != nil {
		t.Fatal("a failed renewal extended the room")
	}
}

// A host that lost its in-memory secret but kept its ID cannot renew the live room; once the room
// expires, the same ask starts a fresh one with a fresh secret.
func TestHostRestartWaitsForExpiry(t *testing.T) {
	now := time.Now()
	next := 0
	known := newRooms(func() int { next++; return next * 7 })
	first, _ := known.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now)
	if _, why := known.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now.Add(time.Second)); why != failUnauthorized {
		t.Fatalf("a secretless renewal was not refused: %v", why)
	}
	second, why := known.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now.Add(roomLifetime))
	if why != 0 || second == nil {
		t.Fatal("the expired room was not replaced")
	}
	if second.secret == first.secret {
		t.Fatal("the replacement reused the old secret")
	}
	if second.code == first.code {
		t.Fatal("the replacement reused the old code")
	}
}

// A restart loses every room by design. A host still echoing its old secret is a new host then,
// not a renewal: it is given a fresh room and secret, and keeps working.
func TestServerRestartIssuesAFreshSecret(t *testing.T) {
	now := time.Now()
	next := 0
	random := func() int { next++; return next * 7 }
	before := newRooms(random)
	first, _ := before.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now)
	after := newRooms(random)
	second, why := after.host(1, first.secret, endpoint{}, endpoint{}, now)
	if why != 0 || second == nil {
		t.Fatal("a host after a restart was refused")
	}
	if second.secret == first.secret {
		t.Fatal("the restart reissued the old secret")
	}
	if after.find(second.code, now) == nil {
		t.Fatal("the new room does not resolve")
	}
}

func TestRoomsExpire(t *testing.T) {
	now := time.Now()
	known := newRooms(func() int { return 3 })
	hosted, why := known.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now)
	if why != 0 || hosted == nil {
		t.Fatalf("no room: %v", why)
	}
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

func TestSecretsArePerRoomAndStable(t *testing.T) {
	now := time.Now()
	next := 0
	known := newRooms(func() int { next++; return next * 7 })
	a, _ := known.host(1, [secretSize]byte{}, endpoint{}, endpoint{}, now)
	b, _ := known.host(2, [secretSize]byte{}, endpoint{}, endpoint{}, now)
	if a.secret == b.secret {
		t.Fatal("two rooms share a secret")
	}
	// No rotation on renewal: a lost rotation answer would lock the host out until expiry.
	renewed, why := known.host(1, a.secret, endpoint{}, endpoint{}, now.Add(time.Second))
	if why != 0 || renewed.secret != a.secret {
		t.Fatal("a renewal rotated the secret")
	}
}

func TestHostBudget(t *testing.T) {
	now := time.Now()
	known := newRooms(func() int { return 3 })
	ip := [4]byte{127, 0, 0, 1}
	for i := 0; i < hostsPerMinute; i++ {
		if !known.allowHost(ip, now) {
			t.Fatalf("host request %d refused inside the budget", i+1)
		}
	}
	if known.allowHost(ip, now) {
		t.Fatal("the host budget did not run out")
	}
	// Joins keep their own counter, so a busy host does not spend a joiner's budget.
	for i := 0; i < joinsPerMinute; i++ {
		if !known.allowJoin(ip, now) {
			t.Fatalf("join %d refused inside the budget", i+1)
		}
	}
	if known.allowJoin(ip, now) {
		t.Fatal("the join budget did not run out")
	}
	if !known.allowHost(ip, now.Add(time.Minute)) || !known.allowJoin(ip, now.Add(time.Minute)) {
		t.Fatal("a new minute did not refill the budgets")
	}
}

// A flood of guessed secrets spends the same budget as legitimate asks, and is cut off.
func TestHostFloodIsBudgeted(t *testing.T) {
	server := startServer(t)
	host := client(t, server)
	exchange(t, host, request_(kindHost, protocolVersion, 9, endpoint{}, "", [secretSize]byte{}))
	for i := 1; i < hostsPerMinute; i++ {
		got := exchange(t, host, request_(kindHost, protocolVersion, 9, endpoint{}, "", [secretSize]byte{0xff}))
		if got[1] != kindError || failure(got[2]) != failUnauthorized {
			t.Fatalf("request %d: %v", i+1, got)
		}
	}
	got := exchange(t, host, request_(kindHost, protocolVersion, 9, endpoint{}, "", [secretSize]byte{0xff}))
	if got[1] != kindError || failure(got[2]) != failTooManyTries {
		t.Fatalf("the flood was not budgeted: %v", got)
	}
}
