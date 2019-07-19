#include <iostream>
#include <vector>

using namespace std;

int inversions(const vector<int>& perm) {
	int count = 0;
	int size = perm.size();

	for (int i = 0; i < size; ++i) {
		for (int k = i + 1; k < size; ++k) {
			if (perm[i] > perm[k]) {
				count = (count + 1) % 10000;
			}
		}
	}

	return count;
}

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int N;
		cin >> N;
		vector<int> perm = vector<int>(N);

		for (int i = 0; i < N; ++i) {
			cin >> perm[i];
		}

		cout << inversions(perm) << endl;
	}
}
