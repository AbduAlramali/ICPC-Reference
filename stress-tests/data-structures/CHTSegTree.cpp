#include "../utilities/template.h"
#include "../../content/data-structures/CHTSegTree.h"

int main() {
	// Seed the random number generator
	srand(1337);

	int N = 50;
	int Q = 2000;

	// Stress Mode A: update_at & queries_range
	{
		CHTSegTree tree(N);
		vector<vector<pair<ll, ll>>> points(N);

		rep(q, 0, Q) {
			int type = rand() % 2;
			if (type == 0) { // update_at
				int id = rand() % N;
				ll k = rand() % 200 - 100;
				ll m = rand() % 20000 - 10000;
				tree.update_at(id, k, m);
				points[id].push_back({k, m});
			} else { // queries_range
				int l = rand() % N;
				int r = rand() % N;
				if (l > r) swap(l, r);
				ll x = rand() % 200 - 100;

				ll tree_ans = tree.queries_range(l, r, x);

				ll naive_ans = -CHTSegTree::INF;
				rep(i, l, r + 1) {
					for (auto& line : points[i]) {
						naive_ans = max(naive_ans, line.first * x + line.second);
					}
				}

				assert(tree_ans == naive_ans);
			}
		}
	}

	// Stress Mode B: update_range & queries_at
	{
		CHTSegTree tree(N);
		vector<vector<pair<ll, ll>>> ranges(N);

		rep(q, 0, Q) {
			int type = rand() % 2;
			if (type == 0) { // update_range
				int l = rand() % N;
				int r = rand() % N;
				if (l > r) swap(l, r);
				ll k = rand() % 200 - 100;
				ll m = rand() % 20000 - 10000;
				tree.update_range(l, r, k, m);
				rep(i, l, r + 1) {
					ranges[i].push_back({k, m});
				}
			} else { // queries_at
				int id = rand() % N;
				ll x = rand() % 200 - 100;

				ll tree_ans = tree.queries_at(id, x);

				ll naive_ans = -CHTSegTree::INF;
				for (auto& line : ranges[id]) {
					naive_ans = max(naive_ans, line.first * x + line.second);
				}

				assert(tree_ans == naive_ans);
			}
		}
	}

	cout << "CHTSegTree tests passed!" << endl;
	return 0;
}
