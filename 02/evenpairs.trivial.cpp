#include <iostream>
#include <vector>

using namespace std;

int main() {

	int numbers;
	cin >> numbers;

	vector<int> parity(numbers, 0);

	for (int i = 0; i < numbers; ++i) {
		cin >> parity[i];
	}

	vector<int> sums(numbers, 0);

	// special case
	sums[0] = parity[0];
	// general case
	for (int i = 1; i < numbers; ++i) {
		sums[i] += sums[i - 1] + parity[i];
	}

	int even_pairs = 0;

	// special case
	for (int i = 0; i < numbers; ++i) {
		if (sums[i] % 2 == 0) {
			++even_pairs;
		}
	}
	// general case
	for (int i = 1; i < numbers; ++i) {
		for (int j = i; j < numbers; ++j) {
			if ((sums[j] - sums[i - 1]) % 2 == 0) {
				++even_pairs;
			}
		}
	}

	cout << even_pairs << endl;
}
