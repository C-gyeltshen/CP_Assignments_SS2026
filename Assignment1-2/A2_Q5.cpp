#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// ── Part (a): KMP — Longest Prefix Suffix (LPS) array ────────
//
// LPS[i] = length of the longest proper prefix of pattern[0..i]
//          that is ALSO a suffix of pattern[0..i].
// "Proper" means it is not the whole substring itself.
//
// Building algorithm: O(M) time and space (M = pattern length).
std::vector<int> buildLPS(const std::string& pattern) {
    int M = (int)pattern.size();
    std::vector<int> lps(M, 0);

    int len = 0;    // length of previous longest prefix-suffix
    int i   = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            // Characters match: extend the prefix-suffix
            lps[i] = ++len;
            ++i;
        } else {
            if (len != 0) {
                // Fall back — do NOT increment i
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }
    return lps;
}

// ── Part (b): Rabin-Karp string search ───────────────────────
//  Uses a rolling polynomial hash to find pattern occurrences.
//  BASE and MOD chosen to minimise collision probability.
static const long long RK_BASE = 31;
static const long long RK_MOD  = 1e9 + 9;

std::vector<int> rabinKarp(const std::string& text,
                           const std::string& pattern)
{
    int N = (int)text.size();
    int M = (int)pattern.size();
    std::vector<int> matches;
    if (M > N) return matches;

    // Precompute BASE^M mod MOD
    long long power = 1;
    for (int i = 0; i < M - 1; ++i)
        power = (power * RK_BASE) % RK_MOD;

    // Compute hash of pattern and first window of text
    long long patHash  = 0, winHash = 0;
    for (int i = 0; i < M; ++i) {
        patHash = (patHash * RK_BASE + (pattern[i] - 'a' + 1)) % RK_MOD;
        winHash = (winHash * RK_BASE + (text[i]   - 'a' + 1)) % RK_MOD;
    }

    for (int i = 0; i <= N - M; ++i) {
        if (winHash == patHash) {
            // Hash match — verify character by character to rule out collision
            if (text.substr(i, M) == pattern)
                matches.push_back(i);
        }
        // Roll the hash forward
        if (i < N - M) {
            winHash = (RK_BASE * (winHash -
                       (text[i] - 'a' + 1) * power % RK_MOD + RK_MOD)
                       + (text[i + M] - 'a' + 1)) % RK_MOD;
        }
    }
    return matches;
}

// ── main ──────────────────────────────────────────────────────
int main() {
    // ── Part (a): LPS for "ABABCABAB" ────────────────────────
    std::string pattern = "ABABCABAB";
    std::vector<int> lps = buildLPS(pattern);

    std::cout << "=== Part (a): KMP — LPS Array ===\n\n";
    std::cout << "Pattern: " << pattern << "\n\n";

    // Print index row
    std::cout << "Index  : ";
    for (int i = 0; i < (int)pattern.size(); ++i)
        std::cout << i << "  ";
    std::cout << "\nChar   : ";
    for (char c : pattern) std::cout << c << "  ";
    std::cout << "\nLPS    : ";
    for (int v : lps) std::cout << v << "  ";
    std::cout << "\n\n";

    // Step-by-step walkthrough
    std::cout << "Step-by-step derivation:\n";
    std::cout << "  i=0  A          → LPS[0] = 0  (by definition)\n";
    std::cout << "  i=1  AB         → no proper prefix = suffix → LPS[1] = 0\n";
    std::cout << "  i=2  ABA        → 'A' is both prefix and suffix → LPS[2] = 1\n";
    std::cout << "  i=3  ABAB       → 'AB' matches → LPS[3] = 2\n";
    std::cout << "  i=4  ABABC      → no match → LPS[4] = 0\n";
    std::cout << "  i=5  ABABCA     → 'A' matches → LPS[5] = 1\n";
    std::cout << "  i=6  ABABCAB    → 'AB' matches → LPS[6] = 2\n";
    std::cout << "  i=7  ABABCABA   → 'ABA' matches → LPS[7] = 3\n";
    std::cout << "  i=8  ABABCABAB  → 'ABAB' matches → LPS[8] = 4\n";

    // ── Part (b): Rabin-Karp demonstration ───────────────────
    std::cout << "\n=== Part (b): Rabin-Karp Demonstration ===\n\n";

    // Convert to lowercase for the hash function (uses 'a'-based encoding)
    std::string text2    = "ababcababababcabab";
    std::string pattern2 = "ababcabab";
    auto matches = rabinKarp(text2, pattern2);

    std::cout << "Text   : " << text2    << '\n';
    std::cout << "Pattern: " << pattern2 << '\n';
    std::cout << "Matches at indices: ";
    for (int idx : matches) std::cout << idx << " ";
    std::cout << '\n';

    return 0;
}
