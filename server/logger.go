// Package main — leveled logging for the rendezvous server.
//
// Three levels (debug < info < error); messages below the configured
// level are dropped. Everything goes to stdout (container-friendly).
package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

// logLevel is a numeric log threshold: messages below the level are dropped.
type logLevel int

const (
	levelDebug logLevel = iota
	levelInfo
	levelError
)

// parseLogLevel parses the -log / DAYBREAK_LOG_LEVEL value.
func parseLogLevel(s string) (logLevel, error) {
	switch strings.ToLower(strings.TrimSpace(s)) {
	case "debug":
		return levelDebug, nil
	case "info":
		return levelInfo, nil
	case "error":
		return levelError, nil
	}
	return levelInfo, fmt.Errorf("invalid log level %q (want debug, info or error)", s)
}

// serverLogger is a leveled wrapper around log.Logger. Safe for
// concurrent use (log.Logger locks internally).
type serverLogger struct {
	inner *log.Logger
	level logLevel
}

func newServerLogger(level logLevel) *serverLogger {
	return &serverLogger{
		inner: log.New(os.Stdout, "", log.LstdFlags|log.Lmicroseconds),
		level: level,
	}
}

func (l *serverLogger) Debugf(format string, args ...any) { l.log(levelDebug, format, args...) }
func (l *serverLogger) Infof(format string, args ...any)  { l.log(levelInfo, format, args...) }
func (l *serverLogger) Errorf(format string, args ...any) { l.log(levelError, format, args...) }

func (l *serverLogger) log(lv logLevel, format string, args ...any) {
	if lv < l.level {
		return
	}
	l.inner.Printf(format, args...)
}
