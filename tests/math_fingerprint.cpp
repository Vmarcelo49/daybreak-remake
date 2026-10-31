// Online play (docs/ONLINE-PLAN.md, step 5): does this machine compute what another does? Prints one
// digest per kind of math the simulation depends on. Needs no game data, so it runs on a real Windows
// machine and compares with Linux. With --check, also holds det_math to the C runtime's accuracy.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "battle/det_math.h"

namespace {

struct Digest {
    std::uint64_t value = 1469598103934665603ull;
    template <class T>
    void add(T number) {
        // Every NaN counts as one, since their bits carry no meaning.
        if (number != number) number = T(0.25);
        unsigned char bytes[sizeof number];
        std::memset(bytes, 0, sizeof bytes);
        // 10 bytes of an 80-bit long double hold its value, and the rest is padding.
        std::memcpy(bytes, &number, sizeof(T) > 10 ? 10 : sizeof(T));
        for (unsigned char b : bytes) value = (value ^ b) * 1099511628211ull;
    }
};

// A repeatable spread: the game's angles and distances densely, then arbitrary bit patterns.
struct Numbers {
    std::uint32_t state = 12345;
    float next(unsigned i) {
        state = state * 1664525u + 1013904223u;
        if (i % 4 == 3) {
            float raw;
            std::memcpy(&raw, &state, sizeof raw);
            return raw;
        }
        const float unit = static_cast<float>(state >> 8) / 16777216.f;
        return (i % 4 == 0 ? 12.566371f : i % 4 == 1 ? 1.f : 20000.f) * (unit * 2.f - 1.f);
    }
};

constexpr unsigned kSamples = 4000000;

template <class Call>
void report(const char* name, Call call) {
    Numbers numbers;
    Digest digest;
    for (unsigned i = 0; i < kSamples; ++i) call(digest, numbers, i);
    std::printf("%-12s %016llx\n", name, static_cast<unsigned long long>(digest.value));
}

std::uint64_t ulps(double a, double b) {
    if (a != a || b != b) return a != a && b != b ? 0 : ~0ull;
    std::int64_t x, y;
    std::memcpy(&x, &a, sizeof x);
    std::memcpy(&y, &b, sizeof y);
    if (x < 0) x = INT64_MIN - x;
    if (y < 0) y = INT64_MIN - y;
    return x > y ? static_cast<std::uint64_t>(x - y) : static_cast<std::uint64_t>(y - x);
}

// det_math is not the C runtime's code, so it must at least agree with it about the answers.
int check_accuracy() {
    int failures = 0;
    const auto compare = [&](const char* name, auto ours, auto theirs) {
        Numbers numbers;
        std::uint64_t worst = 0;
        unsigned floatsDiffer = 0;
        for (unsigned i = 0; i < kSamples; ++i) {
            // Large arguments reduce differently on purpose (det_math.c).
            const double y = numbers.next(i), x = numbers.next(i);
            if (std::fabs(y) > 1.6e6 || std::fabs(x) > 1.6e6) continue;
            const double a = ours(y, x), b = theirs(y, x);
            worst = std::max(worst, ulps(a, b));
            floatsDiffer += static_cast<float>(a) != static_cast<float>(b) && a == a;
        }
        std::printf("%-6s worst %llu ulp, %u floats differ of %u\n", name, static_cast<unsigned long long>(worst), floatsDiffer, kSamples);
        if (worst > 2) ++failures;
    };
    compare("sin", [](double y, double) { return det_sin(y); }, [](double y, double) { return std::sin(y); });
    compare("cos", [](double y, double) { return det_cos(y); }, [](double y, double) { return std::cos(y); });
    compare("atan2", [](double y, double x) { return det_atan2(y, x); }, [](double y, double x) { return std::atan2(y, x); });
    return failures;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--check") {
        const int failures = check_accuracy();
        std::printf("math_fingerprint: %s\n", failures ? "failed" : "ok");
        return failures ? 1 : 0;
    }
    report("det_sin", [](Digest& d, Numbers& n, unsigned i) { d.add(det_sin(n.next(i))); });
    report("det_cos", [](Digest& d, Numbers& n, unsigned i) { d.add(det_cos(n.next(i))); });
    report("det_atan2", [](Digest& d, Numbers& n, unsigned i) { const double y = n.next(i); d.add(det_atan2(y, n.next(i))); });
    report("fmod", [](Digest& d, Numbers& n, unsigned i) { const double y = n.next(i); d.add(std::fmod(y, static_cast<double>(n.next(i)))); });
    report("sqrt", [](Digest& d, Numbers& n, unsigned i) { d.add(std::sqrt(static_cast<double>(n.next(i)))); });
    report("sqrtf", [](Digest& d, Numbers& n, unsigned i) { d.add(std::sqrt(n.next(i))); });
    report("nearbyintf", [](Digest& d, Numbers& n, unsigned i) { d.add(std::nearbyint(n.next(i))); });
    report("lrintf", [](Digest& d, Numbers& n, unsigned i) { const float f = n.next(i); if (std::fabs(f) < 1e9f) d.add(static_cast<double>(std::lrint(f))); });
    // legacy_trig and seven more core headers work in long double, whose result depends on the x87
    // precision the runtime sets up: 64 bits or, by Windows' own default, 53.
    report("long double", [](Digest& d, Numbers& n, unsigned i) {
        volatile long double a = n.next(i), b = n.next(i);
        d.add(a / (b == 0 ? 3.0L : b));
    });
    return 0;
}
