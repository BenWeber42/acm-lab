#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Cmp {
public:
	Cmp(vector<int>* costs): costs(costs) {}
	bool operator()(const int& first, const int& second) const {
		return (*costs)[first] < (*costs)[second]
			|| ((*costs)[first] == (*costs)[second] && first < second);
	}
private:
	vector<int>* costs;
};

void remove_reachable(set<int>& uncovered, const vector<vector<int> >& roads,
		const int station) {

	if (uncovered.find(station) == uncovered.end()) {
		return;
	}

	uncovered.erase(station);

	for (vector<int>::const_iterator it = roads[station].begin();
			it != roads[station].end(); ++it) {

		remove_reachable(uncovered, roads, *it);
	}
}

void remove_reachable(set<int, Cmp>& uncovered, const vector<vector<int> >& roads,
		const int station) {

	if (uncovered.find(station) == uncovered.end()) {
		return;
	}

	uncovered.erase(station);

	for (vector<int>::const_iterator it = roads[station].begin();
			it != roads[station].end(); ++it) {

		remove_reachable(uncovered, roads, *it);
	}
}

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int n, m;
		cin >> n;
		cin >> m;

		vector<vector<int> > roads(n);
		vector<vector<int> > roadsR(n); // reversed roads
        vector<int> outgoing(n);

		set<int> roots;
		for (int i = 0; i < n; ++i) {
			roots.insert(i);
		}

		set<int> uncovered(roots);

		for (int k = 0; k < m; ++k) {
			int i, j;
			cin >> i;
			cin >> j;
			if (i == j) {
				continue;
			}
			roads[i - 1].push_back(j - 1);
			roadsR[j - 1].push_back(i - 1);
            ++outgoing[i - 1];
			roots.erase(j - 1);
		}

		vector<int> costs(n);
		for (int i = 0; i < n; ++i) {
			int cost;
			cin >> cost;
			costs[i] = cost;
		}

		int cost = 0;
		for (set<int>::iterator it = roots.begin();
				it != roots.end(); ++it) {
			remove_reachable(uncovered, roads, *it);
			cost += costs[*it];
		}

        // remove leafs:
        vector<int> leafs;
        for (int i = 0; i < n; ++i) {
            if (outgoing[i] == 0)
                leafs.push_back(i);
        }

        for (int i = 0; i < leafs.size(); ++i) {
            uncovered.erase(leafs[i]);
            for (int k = 0; k < roadsR[leafs[i]].size(); ++k) {
                --outgoing[roadsR[leafs[i]][k]];
                if (outgoing[roadsR[leafs[i]][k]] == 0) {
                    leafs.push_back(roadsR[leafs[i]][k]);
                }
            }
        }

		// at this point there are only circles left
		set<int, Cmp> sorted(uncovered.begin(), uncovered.end(), Cmp(&costs));

		while (!sorted.empty()) {
			int candidate = *sorted.begin();
			remove_reachable(sorted, roads, candidate);
			cost += costs[candidate];
		}

		cout << cost << endl;
	}
}
