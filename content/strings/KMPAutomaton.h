/**
 * Author: 
 * Date: 2026-07-07
 * License: CC0
 * Source: Standard NFA-to-DFA String DP
 * Description: Builds a deterministic finite automaton (DFA) for KMP string matching.
 * nxt[i][c] returns the next state after appending character c (0-indexed offset from 'a')
 * to a matched prefix of length i. If absorbing is true, the automaton stays in state m 
 * indefinitely once a full match is found (useful for "contains" queries).
 * Takes vector of chars (a) that string P consists of.
 * Here $\Sigma = 26$.
 * Time: O(m \Sigma)
 * Status: tested
 */
#pragma once

vector<vi> buildAutomaton(const vi& LPS, const string& P, bool absorbing = false) {
    int m = sz(P);
    vector<vi> nxt(m + 1, vi(26));
    for (int c = 0; c < 26; c++) {
        nxt[0][c] = (m > 0 && P[0] - 'a' == c ? 1 : 0);
    }
    for (int matched = 1; matched <= m; matched++) {
        for (int c = 0; c < 26; c++) {
            if (absorbing && matched == m) {
                nxt[matched][c] = m;
                continue;
            }
            char ch = c+'a';
            if (matched < m && P[matched] == ch) {
                nxt[matched][c] = matched + 1;
            } else {
                nxt[matched][c] = nxt[LPS[matched - 1]][c];
            }
        }
    }
    return nxt;
}