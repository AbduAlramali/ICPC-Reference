/**
 * Author: abdua
 * Date: 2026-08-10
 * Description: Stress testing template using system commands to compile and run solutions.
 * Compile: g++ -O3 stress.cpp -o stress
 * Run: ./stress
 * Notes: Make sure ac.cpp (correct/brute solution) and wa.cpp (incorrect/intended solution) are in the same folder.
 */
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

mt19937 mt(2005);
using ll = long long;

long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(mt);
}

void gen_tests() {
    ofstream out("test.in");
    int t = rnd(1, 5);
    out << t << '\n';
    while (t--) {
        int n = rnd(1, 20);
        ll l = rnd(1, n);
        ll r = rnd(l, n);
        out << n << " " << l << " " << r << '\n';

        vector<int> labels(n);
        iota(labels.begin(), labels.end(), 1);
        shuffle(labels.begin(), labels.end(), mt);
        vector<pair<int, int>> edges;
        for (int i = 1; i < n; i++) {
            int par = rnd(0, i - 1);
            edges.push_back({labels[i], labels[par]});
        }
        shuffle(edges.begin(), edges.end(), mt);
        for (auto edge : edges) {
            if (rnd(0, 1)) {
                out << edge.first << " " << edge.second << "\n";
            } else {
                out << edge.second << " " << edge.first << "\n";
            }
        }

        for (int i = 0; i < n; i++) {
            out << rnd(-1000, 1000) << (i == n - 1 ? "" : " ");
        }
        out << "\n";
    }
    out.close();
}

bool check() {
    ifstream acfile("ac.txt");
    ifstream wafile("wa.txt");

    string actxt, watxt;
    getline(acfile, actxt, '\0');
    getline(wafile, watxt, '\0');

    return actxt == watxt;
}

signed main() {
    system("g++ ac.cpp -o ac");
    system("g++ wa.cpp -o wa");
    int tc = 1;
    while (true) {
        gen_tests();
        system("./ac < test.in > ac.txt");
        system("./wa < test.in > wa.txt");
        cout << "Stress Test " << tc++ << " : ";
        if (check()) {
            cout << "OK\n";
        } else {
            cout << "WA - Bug found!\n";
            break;
        }
    }
    return 0;
}
