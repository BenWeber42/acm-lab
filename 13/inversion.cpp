#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
 * Counts the inversions for the elements with indice [lower, upper]
 * And sorts perm
 */
int inversions(vector<int>& perm, int lower, int upper) {

	assert(lower <= upper);

	// base case
	if (lower == upper) {
		return 0;
	}

	// divide
	int lower1, upper1, lower2, upper2;
	lower1 = lower;
	upper1 = lower/2 + upper/2;
	lower2 = upper1 + 1;
	upper2 = upper;
	int count = (inversions(perm, lower1, upper1)
					+ inversions(perm, lower2, upper2)) % 10000;

	// conquer
	
	// count
	int i = lower1;
	int k = lower2;
	while (i <= upper1) {
		while (perm[i] > perm[k] && k <= upper2) {
			++k;
		}
		count += k - lower2;
		count = count % 10000;
		++i;
	}
	
	// merge
	vector<int> buffer = vector<int>(perm.begin() + lower, perm.begin() + upper + 1);
	i = 0;
	k = lower2 - lower;
	int m = lower;
	while (i + lower <= upper1 && k + lower <= upper2) {
		if (buffer[i] < buffer[k]) {
			perm[m++] = buffer[i++];
		} else {
			perm[m++] = buffer[k++];
		}
	}

	while (i + lower <= upper1) {
		perm[m++] = buffer[i++];
	}

	while (k + lower <= upper2) {
		perm[m++] = buffer[k++];
	}

	count = count % 10000;
	
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

		cout << inversions(perm, 0, perm.size() - 1) << endl;
	}
}
