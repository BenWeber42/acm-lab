#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bsf(const vector< vector<int> >& edges, vector<int>& erdos_number) {
	int number = 1;
	vector<int> current = vector<int>();
	vector<int> next = vector<int>();
	current.push_back(0); // start with Erdos

	while (!current.empty()) {
		for (unsigned int i = 0; i < current.size(); ++i) {
			for (unsigned int k = 0; k < edges[current[i]].size(); ++k) {
				if (erdos_number[edges[current[i]][k]] == -1) {
					next.push_back(edges[current[i]][k]);
					erdos_number[edges[current[i]][k]] = number;
				}
			}
		}
		current.clear();
		swap(next, current);
		++number;
	}
}

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int v, e;
		cin >> v;
		cin >> e;

		vector< vector<int> > edges = vector< vector<int> >(v);
		vector<int> erdos_numbers = vector<int>(v, -1);
		erdos_numbers[0] = 0; // Paul Erdos himself is 0

		for (int i = 0; i < e; ++i) {
			int start, end;
			cin >> start;
			cin >> end;
			edges[start].push_back(end);
			edges[end].push_back(start);
		}

		bsf(edges, erdos_numbers);

		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int index;
			cin >> index;
			if (erdos_numbers[index] == -1) {
				cout << "infinity" << endl;
			} else {
				cout << erdos_numbers[index] << endl;
			}
		}

	}
}
