#include "bits/stdc++.h"
using namespace std;

void printTimesAsTable(const vector<long long>& normalTimes, const vector<long long>& inlineTimes, const int rounds = 10)
{
    cout << left << setw(10) << "Round"
        << setw(20) << "Normal (us)"
        << setw(20) << "Inline (us)" << '\n';

    cout << string(50, '-') << '\n';

    for (int i = 0; i < rounds; ++i) {
        cout << left << setw(10) << i + 1
            << setw(20) << normalTimes[i]
            << setw(20) << inlineTimes[i] << '\n';
    }

    // Calculate averages
    long long normalTotal = accumulate(normalTimes.begin(), normalTimes.end(), 0LL);
    long long inlineTotal = accumulate(inlineTimes.begin(), inlineTimes.end(), 0LL);

    cout << string(50, '-') << '\n';

    long long normalAverage = normalTotal / rounds;
    long long inlineAverage = inlineTotal / rounds;

    cout << left << setw(10) << "Average"
        << setw(20) << normalAverage
        << setw(20) << inlineAverage << '\n';
    
    double speedup = static_cast<double>(normalAverage) / inlineAverage;
    cout << "Average Speedup (normal/inline): " << speedup << "x" << '\n' << '\n';
}

void printSummary(const vector<long long>& normalTimes, const vector<long long>& inlineTimes)
{
    long long normalTotal = accumulate(normalTimes.begin(), normalTimes.end(), 0LL);
    long long inlineTotal = accumulate(inlineTimes.begin(), inlineTimes.end(), 0LL);

    vector<long long> sortedNormalTimes = normalTimes;
    vector<long long> sortedInlineTimes = inlineTimes;

    sort(sortedNormalTimes.begin(), sortedNormalTimes.end());
    sort(sortedInlineTimes.begin(), sortedInlineTimes.end());

    long long medianNormal = sortedNormalTimes[sortedNormalTimes.size() / 2];
    long long medianInline = sortedInlineTimes[sortedInlineTimes.size() / 2];

    cout << "Median normal (us): " << medianNormal << '\n';
    cout << "Median inline (us): " << medianInline << '\n';
    double speedup = static_cast<double>(medianNormal) / medianInline;
    cout << "Median Speedup (normal/inline): " << speedup << "x" << '\n' << '\n';

    long long minNormal = *min_element(normalTimes.begin(), normalTimes.end());
    long long minInline = *min_element(inlineTimes.begin(), inlineTimes.end());
    cout << "Min normal (us):    " << minNormal << '\n';
    cout << "Min inline (us):    " << minInline << '\n';
    double minSpeedup = static_cast<double>(minNormal) / minInline;
    cout << "Min Speedup (normal/inline): " << minSpeedup << "x" << '\n';
}