#include <iostream>
#include <vector>

using namespace std;

int main() {

	int numbers, pairs, border_pairs;
	pairs = border_pairs = 0;

	cin >> numbers;

	for (int i = 0; i < numbers; ++i) {
		int odd;
		cin >> odd;

		if (!odd) {
			++border_pairs;
		} else {
			border_pairs = i - border_pairs;
		}
		pairs += border_pairs;
	}

	cout << pairs << endl;

}
