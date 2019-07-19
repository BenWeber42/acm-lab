#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class comp {
public:
	bool operator()(const int& l1, const int& l2) {
		return !(l1 < l2);
	}
};

int main() {

	int testcases;

	cin >> testcases;

	for (int k = 0; k < testcases; ++k) {
		int N;
		cin >> N;

		priority_queue<int, vector<int>, comp> lists =
			priority_queue<int, vector<int>, comp>(comp());

		for (int i = 0; i < N; ++i) {
			int l;
			cin >> l;

			lists.push(l);
		}

		int cost = 0;
		while (lists.size() > 1) {
			int l1 = lists.top();
			lists.pop();
			int l2 = lists.top();
			lists.pop();

			cost += l1 + l2 - 1;
			lists.push(l1 + l2);
		}

		cout << cost << endl;
	}
}
