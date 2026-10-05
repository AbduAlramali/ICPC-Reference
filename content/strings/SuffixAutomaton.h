/**
 * Author: Common knowledge
 * Date: 2026-08-16
 * License: CC0
 * Description: Suffix Automaton (SAM) is a DAG representing all substrings of a string.
 *  Each node corresponds to an equivalence class of substrings.
 *  `link` points to the longest suffix in a different equivalence class.
 *  `first_pos` is the 0-based end position of the first occurrence in the string.
 *  `is_clone` is true if the state was created by cloning.
 *  `cnt` counts substring occurrences (populated if `occ = true`).
 *  `inv_link` contains the children in the suffix link tree (populated if `inv = true`).
 * Time: O(N \Sigma) build, O(N \Sigma) space.
 * Status: Tested
 */
#pragma once

struct SuffixAutomaton {
	struct State {
		array<int, 26> next;
		int link = -1, len = 0;
		bool is_clone = false;
		int first_pos = 0;
		long long cnt = 0;
		vector<int> inv_link;
		State() {
			next.fill(-1);
		}
	};
	vector<State> st;
	string s;
	int last = 0;
	// Build SAM. O(n)
	SuffixAutomaton(const string& _s = "", bool occ = true, bool inv = true) {
		build(_s, occ, inv);
	}
	// Convert char to index. O(1)
	int id(char c) const { return c - 'a'; }
	// Rebuild SAM. O(n)
	void build(const string& _s, bool occ = true, bool inv = true) {
		s = _s;
		st.clear();
		st.reserve(max(1LL, 2LL * (int)s.size()));
		st.emplace_back();
		last = 0;
		for (char c : s) extend(c);
		if (occ) build_occurrences();
		if (inv) build_inv_links();
	}
	// Add one character. Amortized O(1)
	void extend(char c) {
		int x = id(c);
		int cur = sz(st);
		st.emplace_back();
		st[cur].len = st[last].len + 1;
		st[cur].first_pos = st[cur].len - 1;
		st[cur].cnt = 1;
		int p = last;
		while (p >= 0 && st[p].next[x] == -1) {
			st[p].next[x] = cur;
			p = st[p].link;
		}
		if (p == -1) {
			st[cur].link = 0;
		} else {
			int q = st[p].next[x];
			if (st[p].len + 1 == st[q].len) {
				st[cur].link = q;
			} else {
				int clone = sz(st);
				st.push_back(st[q]);
				st[clone].len = st[p].len + 1;
				st[clone].is_clone = true;
				st[clone].cnt = 0;
				while (p >= 0 && st[p].next[x] == q) {
					st[p].next[x] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
	// States by len decreasing. O(S+n)
	vector<int> order_desc() const {
		int mx = 0, S = sz(st);
		for (auto& v : st) mx = max(mx, v.len);
		vector<int> cnt(mx + 1), ord(S);
		for (auto& v : st) cnt[v.len]++;
		rep(i, 1, mx + 1) cnt[i] += cnt[i - 1];
		for (int i = S - 1; i >= 0; i--) ord[--cnt[st[i].len]] = i;
		reverse(ord.begin(), ord.end());
		return ord;
	}
	// Build occurrence counts. O(S+n)
	void build_occurrences() {
		rep(i, 0, sz(st)) st[i].cnt = (i && !st[i].is_clone);
		for (int v : order_desc()) {
			if (st[v].link != -1) st[st[v].link].cnt += st[v].cnt;
		}
	}
	// Build suffix-link tree. O(S)
	void build_inv_links() {
		for (auto& v : st) v.inv_link.clear();
		rep(i, 1, sz(st)) st[st[i].link].inv_link.push_back(i);
	}
};
