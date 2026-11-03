#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>
#include "square.h"                 // declares normalSquare() and defines inlineSquare()
#include "printer.h"                // table/summary printing helpers 

using namespace std;
using namespace std::chrono;

constexpr size_t SIZE = 1 << 20;    // ~1M (1048576) elements (4 MB)
constexpr int REPS = 100;           // ~1e8 operations in total
constexpr int ROUNDS = 20;          // Number of rounds to run


// Runs function f over the whole data array REPS times and returns the elapsed time
// in microseconds.
//
// F is a template parameter so each call site gets its own copy of measure() with the
// lambda's exact type. That lets the compiler see the lambda's body and inline it.
// If F were std::function or a function pointer, inlining would often fail and the
// experiment would be unfair.
template <typename F>
long long measure(F f, const vector<std::uint32_t>& data, std::uint32_t& result)
{
    // Accumulator. Unsigned overflow is well-defined (it wraps), so this is safe.
    std::uint32_t sum = 0;

    auto start = steady_clock::now();

    for (int rep = 0; rep < REPS; ++rep)
    {
        for (size_t i = 0; i < data.size(); ++i)
        {
            // "+ rep" makes every pass use different values, so the compiler cannot
            // compute one pass and just multiply the result by REPS.
            // Adding to sum makes each iteration's result "used", so the loop can't
            // be removed as dead code.
            sum += f(data[i] + rep);
        }
    }

    auto end = steady_clock::now();

    // Pass the sum out to the caller. main() reads it later (Results match), which
    // forces the compiler to really compute the loop. If nobody used it, the compiler
    // could delete the whole loop and the measured time would be ~0.
    result = sum;
    return duration_cast<microseconds>(end - start).count();
}

int main()
{
    // Random runtime data: the compiler cannot know these values in advance, so it
    // cannot precompute the answer at compile time.
    vector<std::uint32_t> data(SIZE);
    mt19937 rng(random_device{}());
    for (auto& x : data)
    {
        x = rng();
    }

    vector<long long> normalTimes;      // one time (us) per round, normal function
    vector<long long> inlineTimes;      // one time (us) per round, inline function

    // The checksums of each version. Only used to prove both versions compute the
    // same thing, and to keep the compiler from removing the work.
    std::uint32_t r1 = 0;
    std::uint32_t r2 = 0;

    // Each lambda wraps one function and runs one timed measurement.
    // [&] captures normalTimes, data and r1 by reference.
    // The inner lambda is passed to measure() as F. It simply forwards to
    // normalSquare, which lives in square.cpp, so the compiler sees only a
    // declaration and must emit a real function call.
    auto runNormal = [&]()
    {
        normalTimes.push_back(measure([](std::uint32_t v) { return normalSquare(v); }, data, r1));
    };

    // Same thing, but inlineSquare is defined in square.h, so the compiler can see its
    // body and inline it into the loop (and then vectorize the loop).
    auto runInline = [&]()
    {
        inlineTimes.push_back(measure([](std::uint32_t v) { return inlineSquare(v); }, data, r2));
    };

    for (int round = 0; round < ROUNDS; ++round)
    {
        // Alternate which version runs first. CPU clock speed, cache state and thermal
        // throttling change over time, so the one that always runs first (or second)
        // would be treated unfairly.
        if (round % 2 == 0)
        {
            runNormal();
            runInline();
        }
        else
        {
            runInline();
            runNormal();
        }
    }

    // Print the per-round table, then the summary (average, median, min).
    printTimesAsTable(normalTimes, inlineTimes, ROUNDS);
    cout << '\n';
    printSummary(normalTimes, inlineTimes);

    // Both versions must produce the same checksum. This also uses r1 and r2, so the
    // compiler cannot throw the measured loops away.
    cout << "\nResults match: " << (r1 == r2 ? "yes" : "no") << '\n';

    return 0;
}