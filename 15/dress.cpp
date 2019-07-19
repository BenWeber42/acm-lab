#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void sort(int n, vector<int> deps, vector< vector<int> > depsR) {
	
	priority_queue<int> c = priority_queue<int>();

	// find clothes without dependencies
	for (int i = 0; i < n; ++i) {
		if (deps[i] == 0) {
			c.push(i);
		}
	}

	// sort:
	while (!c.empty()) {
		int next = c.top();
		c.pop();

		// output
		cout << next + 1 << endl;

		int size = depsR[next].size();
		for (int i = 0; i < size; ++i) {
			int dependend = depsR[next][i];
			--deps[dependend];
			if (deps[dependend] == 0) {
				c.push(dependend);
			}
		}
	}
}

int main() {
	int testcases;

	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int n, m;
		cin >> n;
		cin >> m;
		vector<int> dependencies(n);
		vector< vector<int> > dependencies_reversed(n);

		for (int i = 0; i < m; ++i) {
			int before, after;
			cin >> after;
			cin >> before;

			++dependencies[after - 1];
			dependencies_reversed[before - 1].push_back(after - 1);
		}
		sort(n, dependencies, dependencies_reversed);
	}
}
