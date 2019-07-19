#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>

using namespace std;

int sum(const vector<int>& vec, int i1, int i2) {
	if (i1 == 0) {
		return vec[i2];
	} else {
		return vec[i2] - vec[i1 - 1];
	}
}

int elem(const vector<int>& vec, int index) {
	if (index == 0) {
		return vec[0];
	} else {
		return vec[index] - vec[index - 1];
	}
}

int remove_array(const vector<int>& a, const vector<int>& b, int ka, int kb,
		int n, vector<int>& memo) {
	int size = a.size() - 1;
	int best = numeric_limits<int>::max();

	if (ka == size || kb == size) {
		return sum(a, ka, size)*sum(b, kb, size);
	}

	if (memo[n*ka + kb] != 0) {
		return memo[n*ka + kb];
	}

	for (int i = kb; i < size; ++i) {
		best = min(best,
				elem(a, ka)*sum(b, kb, i) + remove_array(a, b, ka + 1, i + 1, n, memo));
	}

	for (int i = ka; i < size; ++i) {
		best = min(best,
				elem(b, kb)*sum(a, ka, i) + remove_array(a, b, i + 1, kb + 1, n, memo));
	}

	best = min(best,
			sum(a, ka, size)*sum(b, kb, size));

	memo[n*ka + kb] = best;

	return best;
}

int main() {
	int n;
	cin >> n;

	vector<int> a = vector<int>(n);
	vector<int> b = vector<int>(n);
	vector<int> memo = vector<int>(n*n);

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}
	
	partial_sum(a.begin(), a.end(), a.begin());
	partial_sum(b.begin(), b.end(), b.begin());

	cout << remove_array(a, b, 0, 0, n, memo) << endl;
}
