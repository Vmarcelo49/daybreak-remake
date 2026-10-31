// Package main — rooms: a code, and where its host can be reached. Nothing else is known, and nothing
// survives a restart: hosts keep asking, and are given a room again.
package main

import (
	"sync"
	"time"
)

// A host asks about once a second, so a minute of silence means it has gone or its match has started.
const roomLifetime = 60 * time.Second

// Enough for someone to mistype a code, and too few to try the 1M codes.
const (
	joinsPerMinute = 20
	maxRooms       = 100000
)

type room struct {
	code     string
	clientID uint32
	public   endpoint
	private  endpoint
	lastSeen time.Time
}

type joinBudget struct {
	windowStart time.Time
	used        int
}

type rooms struct {
	mu       sync.Mutex
	byCode   map[string]*room
	byClient map[uint32]*room
	budgets  map[[4]byte]*joinBudget
	random   func() int
}

func newRooms(random func() int) *rooms {
	return &rooms{byCode: map[string]*room{}, byClient: map[uint32]*room{}, budgets: map[[4]byte]*joinBudget{}, random: random}
}

// host gives a host its room, the same one each time it asks. Nil when the server is full.
func (r *rooms) host(clientID uint32, public, private endpoint, now time.Time) *room {
	r.mu.Lock()
	defer r.mu.Unlock()
	if existing, ok := r.byClient[clientID]; ok && now.Sub(existing.lastSeen) < roomLifetime {
		existing.public, existing.private, existing.lastSeen = public, private, now
		return existing
	}
	if len(r.byCode) >= maxRooms {
		return nil
	}
	created := &room{code: r.freeCode(now), clientID: clientID, public: public, private: private, lastSeen: now}
	r.byCode[created.code] = created
	r.byClient[clientID] = created
	return created
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

// allowJoin counts a join against its sender. A client repeats a join only until it is answered.
func (r *rooms) allowJoin(ip [4]byte, now time.Time) bool {
	r.mu.Lock()
	defer r.mu.Unlock()
	budget, ok := r.budgets[ip]
	if !ok || now.Sub(budget.windowStart) >= time.Minute {
		budget = &joinBudget{windowStart: now}
		r.budgets[ip] = budget
	}
	budget.used++
	return budget.used <= joinsPerMinute
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
