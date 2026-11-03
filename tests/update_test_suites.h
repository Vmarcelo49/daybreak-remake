#pragma once
// tests/update_test_suites.h — the shared harness for the update tests.
//
// The three suites are compiled twice: into their own CTest binaries on Linux, and into
// update_selftest.exe for the Windows build, where CTest does not run. So each suite is a
// function here and its own main is compiled out under DAYBREAK_UPDATE_SELFTEST.
#include <cstdint>
#include <cstdio>
#include <string>

namespace update_test {

inline int& checks() {
    static int value = 0;
    return value;
}

inline int& failures() {
    static int value = 0;
    return value;
}

inline void check(bool condition, const std::string& what) {
    ++checks();
    if (!condition) {
        ++failures();
        std::fprintf(stderr, "FAIL: %s\n", what.c_str());
    }
}

inline void expect(const std::string& actual, const std::string& expected,
                   const std::string& what) {
    check(actual == expected,
          what + " (got '" + actual + "', expected '" + expected + "')");
}

inline void expectEqual(std::uint64_t actual, std::uint64_t expected,
                        const std::string& what) {
    check(actual == expected, what + " (got " + std::to_string(actual) + ", expected " +
                                  std::to_string(expected) + ")");
}

inline int report(const char* suite) {
    std::printf("%s: %d checks, %d failure(s)\n", suite, checks(), failures());
    return failures() == 0 ? 0 : 1;
}

}  // namespace update_test

// Defined by the suite .cpp files; update_selftest.cpp calls all three.
int runUpdateLogicTests();
int runUpdateCryptoTests(int argc, char** argv);
int runUpdateArchiveTests();
