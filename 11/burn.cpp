#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> memo;

int get_index(int left, int right) {
	return right*(right + 1)/2 + left;
}


int burn(const vector<int>& coins, int left, int right) {
	// game finished
	if (left == right) {
		return coins[left];
	} else if (left > right) {
		return 0;
	}

	if (memo[get_index(left, right)] != -1) {
		return memo[get_index(left, right)];
	}

	int left_win, right_win;

	// try taking from left
	left_win = coins[left] +
		min(burn(coins, left + 2, right), burn(coins, left + 1, right - 1));

	// try taking form right
	right_win = coins[right] +
		min(burn(coins, left + 1, right - 1), burn(coins, left, right - 2));

	memo[get_index(left, right)] = max(left_win, right_win);

	return memo[get_index(left, right)];

}

int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; ++i) {
		int n;
		cin >> n;

		vector<int> coins = vector<int>(n);

		for (int k = 0; k < n; ++k) {
			cin >> coins[k];
		}

		memo = vector<int>(n*(n + 1)/2, -1);

		cout << burn(coins, 0, n - 1) << endl;
	}
}
