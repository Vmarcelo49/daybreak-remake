// Package main — rooms: a code, where its host can be reached, and the secret that proves a renewal
// is the host's own. Nothing else is known, and nothing survives a restart: hosts keep asking, and are
// given a room again.
package main

import (
	"crypto/rand"
	"crypto/subtle"
	"sync"
	"time"
)

// A host asks about once a second, so a minute of silence means it has gone or its match has started.
const roomLifetime = 60 * time.Second

// Enough for someone to mistype a code, and too few to try the 1M codes. The host budget allows four
// hosts behind one NAT asking once a second, and bounds a flood of guessed renewal secrets (issue #126).
const (
	joinsPerMinute = 20
	hostsPerMinute = 240
	maxRooms       = 100000
)

type room struct {
	code     string
	clientID uint32
	// Issued by the server at creation, echoed by the host to renew. Never sent to a joiner.
	secret   [secretSize]byte
	public   endpoint
	private  endpoint
	lastSeen time.Time
}

type ipBudget struct {
	windowStart time.Time
	joins       int
	hosts       int
}

type rooms struct {
	mu       sync.Mutex
	byCode   map[string]*room
	byClient map[uint32]*room
	budgets  map[[4]byte]*ipBudget
	random   func() int
}

func newRooms(random func() int) *rooms {
	return &rooms{byCode: map[string]*room{}, byClient: map[uint32]*room{}, budgets: map[[4]byte]*ipBudget{}, random: random}
}

// host gives a host its room, the same one each time it asks. A live room is renewed only with the
// secret issued for it: the client ID is public to every room member (src/net/lobby.cpp encode_plan),
// so knowing it must not let a stranger redirect the room (issue #126). A wrong or missing secret
// changes nothing, not even lastSeen. With no live room the request starts a fresh room and secret,
// whatever secret it carries — that is the server-restart and post-expiry path. Nil with no failure
// when the server is full or no secret could be generated; the client simply asks again.
func (r *rooms) host(clientID uint32, secret [secretSize]byte, public, private endpoint, now time.Time) (*room, failure) {
	r.mu.Lock()
	defer r.mu.Unlock()
	if existing, ok := r.byClient[clientID]; ok && now.Sub(existing.lastSeen) < roomLifetime {
		if subtle.ConstantTimeCompare(existing.secret[:], secret[:]) != 1 {
			return nil, failUnauthorized
		}
		existing.public, existing.private, existing.lastSeen = public, private, now
		return existing, 0
	}
	if len(r.byCode) >= maxRooms {
		return nil, 0
	}
	var issued [secretSize]byte
	if _, err := rand.Read(issued[:]); err != nil {
		return nil, 0
	}
	created := &room{code: r.freeCode(now), clientID: clientID, secret: issued, public: public, private: private, lastSeen: now}
	r.byCode[created.code] = created
	r.byClient[clientID] = created
	return created, 0
}

func (r *rooms) freeCode(now time.Time) string {
	for {
		buffer := make([]byte, codeLength)
		for i := range buffer {
			buffer[i] = codeAlphabet[r.random()%len(codeAlphabet)]
		}
		code := string(buffer)
		if existing, taken := r.byCode[code]; !taken || now.Sub(existing.lastSeen) >= roomLifetime {
			if taken {
				delete(r.byClient, existing.clientID)
			}
			return code
		}
	}
}

// find returns the live room for a code, or nil.
func (r *rooms) find(code string, now time.Time) *room {
	r.mu.Lock()
	defer r.mu.Unlock()
	found, ok := r.byCode[code]
	if !ok || now.Sub(found.lastSeen) >= roomLifetime {
		return nil
	}
	copied := *found
	return &copied
}

// budgetFor returns the sender's window, starting a fresh one when the minute is up. Callers hold mu.
func (r *rooms) budgetFor(ip [4]byte, now time.Time) *ipBudget {
	budget, ok := r.budgets[ip]
	if !ok || now.Sub(budget.windowStart) >= time.Minute {
		budget = &ipBudget{windowStart: now}
		r.budgets[ip] = budget
	}
	return budget
}

// allowJoin counts a join against its sender. A client repeats a join only until it is answered.
func (r *rooms) allowJoin(ip [4]byte, now time.Time) bool {
	r.mu.Lock()
	defer r.mu.Unlock()
	budget := r.budgetFor(ip, now)
	budget.joins++
	return budget.joins <= joinsPerMinute
}

// allowHost counts every host request against its sender, failed renewals included, so a flood of
// guessed secrets is bounded (issue #126). A host asks once a second, well inside the budget.
func (r *rooms) allowHost(ip [4]byte, now time.Time) bool {
	r.mu.Lock()
	defer r.mu.Unlock()
	budget := r.budgetFor(ip, now)
	budget.hosts++
	return budget.hosts <= hostsPerMinute
}

// sweep forgets what has expired.
func (r *rooms) sweep(now time.Time) {
	r.mu.Lock()
	defer r.mu.Unlock()
	for code, found := range r.byCode {
		if now.Sub(found.lastSeen) >= roomLifetime {
			delete(r.byCode, code)
			delete(r.byClient, found.clientID)
		}
	}
	for ip, budget := range r.budgets {
		if now.Sub(budget.windowStart) >= time.Minute {
			delete(r.budgets, ip)
		}
	}
}

func (r *rooms) count() int {
	r.mu.Lock()
	defer r.mu.Unlock()
	return len(r.byCode)
}
