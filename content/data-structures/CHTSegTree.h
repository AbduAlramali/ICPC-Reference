/**
 * Author: Antigravity
 * Date: 2026-08-06
 * License: CC0
 * Source: user
 * Description: Segment tree of LineContainer (Convex Hull Trick) supporting range/point additions and point/range queries for maximum values.
 *  Uses power-of-two base size for correct inclusive range updates.
 *  Dependent on LineContainer.h.
 * Time: $O(\log^2 N)$ per update and query
 * Status: stress-tested
 */
#pragma once

#include "LineContainer.h"

struct CHTSegTree {
	static constexpr ll INF = 2e18;
	int n, base;
	vector<LineContainer> tree;

	CHTSegTree(int n) : n(n) {
		base = 1;
		while (base < n) base <<= 1;
		tree.resize(base << 1);
	}
	void update_at(int id, ll k, ll m) { 
        // adds the inserted line to the leaf and all of its ancestors.
		if (id < 0 || id >= n) return;
		int pos = id + base;
		while (pos > 0) {
			tree[pos].add(k, m);
			pos >>= 1;
		}
	}
	ll query_at(int id, ll x) {
        // walks all the way up to the root and evaluate every single line in the tree.
		if (id < 0 || id >= n) return -INF;
		ll ans = -INF;
		int pos = id + base;
		while (pos > 0) {
			if (!tree[pos].empty()) {
				ans = max(ans, tree[pos].query(x));
			}
			pos >>= 1;
		}
		return ans;
	}
	void update_range(int l, int r, ll k, ll m) {
        // updates just a node or range of nodes, no walking till the root
		if (l < 0) l = 0;
		if (r >= n) r = n - 1;
		if (l > r) return;
		int L = l + base, R = r + base;
		while (L <= R) {
			if (L & 1) tree[L++].add(k, m);
			if (!(R & 1)) tree[R--].add(k, m);
			L >>= 1; R >>= 1;
		}
	}
	ll query_range(int l, int r, ll x) {
        // query just a node or range of nodes, no walking till the root
		if (l < 0 || r >= n) return -INF;
		ll ans = -INF;
		int L = l + base, R = r + base;
		while (L <= R) {
			if (L & 1) {
				if (!tree[L].empty()) ans = max(ans, tree[L].query(x));
				L++;
			}
			if (!(R & 1)) {
				if (!tree[R].empty()) ans = max(ans, tree[R].query(x));
				R--;
			}
			L >>= 1; R >>= 1;
		}
		return ans;
	}
};
