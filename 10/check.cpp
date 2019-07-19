#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<int> memo;

int check(const vector<int>& coins, int a) {

	if (a < 0) {
		// not possible
		return -1;
	} else if (a == 0) {
		return 0;
	}

	if (memo[a] != 0) {
		return memo[a];
	}

	int best = numeric_limits<int>::max();
	int count = coins.size();
	bool possible = false;

	for (int i = 0; i < count; ++i) {
		int ret = check(coins, a - coins[i]);
		if (ret != -1) {
			best = min(best, ret + 1);
			possible = true;
		}
	}

	if (!possible) {
		best = -1;
	}

	memo[a] = best;

	return best;
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int c, m;

		// reset memonization:
		memo = vector<int>(10000);

		cin >> c;
		cin >> m;

		vector<int> coins = vector<int>(c);

		for (int k = 0; k < c; ++k) {
			cin >> coins[k];
		}

		for (int k = 0; k < m; ++k) {
			int a;
			cin >> a;
			int b = check(coins, a);
			if (b != -1) {
				cout << b << endl;
			} else {
				cout << "not possible" << endl;
			}
		}
	}
}
