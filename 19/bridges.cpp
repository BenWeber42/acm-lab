#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

bool dfs(const vector<set<int> >& bridges, vector<pair<int, int> >& critical,
        set<int>& unvisited, int prev, int node) {

    bool circle = false;

    unvisited.erase(node);

    for (set<int>::iterator it = bridges[node].begin(); it != bridges[node].end(); ++it) {
        if (*it == prev)
            continue;

        if (unvisited.find(*it) == unvisited.end()) {
            circle = true;
            continue;
        }

        if (dfs(bridges, critical, unvisited, node, *it)) {
            circle = true;
        } else {
            critical.push_back(pair<int, int>(node, *it));
        }
    }
    return circle;
}

int main() {
    int testcases;
    cin >> testcases;

    for (int i = 0; i < testcases; ++i) {
        int n, m;
        cin >> n;
        cin >> m;
        vector<set<int> > bridges(n);

        for (int k = 0; k < m; ++k) {
            int e1, e2;
            cin >> e1;
            cin >> e2;
            bridges[e1 - 1].insert(e2 - 1);
            bridges[e2 - 1].insert(e1 - 1);
        }

        vector<pair<int, int> > critical;
        set<int> unvisited;
        for (int k = 0; k < n; ++k) {
            unvisited.insert(k);
        }

        while (!unvisited.empty()) {
            int c = *unvisited.begin();
            dfs(bridges, critical, unvisited, -1, c);
        }

        sort(critical.begin(), critical.end());

        cout << critical.size() << endl;

        for (vector<pair<int, int> >::iterator it = critical.begin();
                it != critical.end(); ++it) {

            if (it->first < it->second) {
                cout << it->first + 1 << ' ' << it->second + 1 << endl;
            } else {
                cout << it->second + 1 << ' ' << it->first + 1 << endl;
            }
        }
    }
}
