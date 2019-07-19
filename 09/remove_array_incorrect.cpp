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

int remove_array(const vector<int>& a, const vector<int>& b, int ka, int kb) {
	int size = a.size() - 1;
	int best = numeric_limits<int>::max();
	int sum_a, sum_b, ia, ib;
	sum_a = sum_b = 0;

	if (ka == size || kb == size) {
		return sum(a, ka, size)*sum(b, kb, size);
	}

	if (elem(a, ka) <= elem(b, kb) || true) {
		for (ib = kb + 1; ib < size && elem(a, ka) < elem(b, ib); ++ib) {}
		sum_a = sum(b, kb, ib);
		best = min(best,
				elem(a, ka)*sum(b, kb, ib) + remove_array(a, b, ka + 1, ib));
	}

	if (elem(b, kb) <= elem(a, ka) || true) {
		for (ia = ka + 1; ia < size && elem(b, kb) < elem(a, ia); ++ia) {}
		sum_b = sum(a, ka, ia);
		best = min(best,
				elem(b, kb)*sum(a, ka, ia) + remove_array(a, b, ia, kb + 1));
	}

	if (sum_a >= sum_b) {
	}
	if (sum_b >= sum_a) {
	}

	best = min(best,
			sum(a, ka, size)*sum(b, kb, size));

	return best;
}

int main() {
	int n;
	cin >> n;

	vector<int> a = vector<int>(n);
	vector<int> b = vector<int>(n);

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}
	
	partial_sum(a.begin(), a.end(), a.begin());
	partial_sum(b.begin(), b.end(), b.begin());

	cout << remove_array(a, b, 0, 0) << endl;
}
