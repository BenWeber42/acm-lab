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

int remove_array(const vector<int>& a, const vector<int>& b, int ka, int kb) {
	int size = a.size() - 1;
	int best = numeric_limits<int>::max();

	for (int i = ka; i < size; ++i) {
		for (int o = kb; o < size; ++o) {
			best = min(best,
					sum(a, ka, i)*sum(b, kb, o) + remove_array(a, b, i + 1, o + 1));
		}
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
