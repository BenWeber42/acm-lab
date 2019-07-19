#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Boat {
public:
	int dock, length;
	Boat(): dock(0), length(0) {}
	Boat(int dock, int length): dock(dock), length(length) {}
	friend bool operator<(const Boat& w1, const Boat& w2) {
		return w1.dock < w2.dock || (w1.dock == w2.dock && w1.length < w2.length);
	}
};

int main() {

	int testcases;

	cin >> testcases;
	
	for (int i = 0; i < testcases; ++i) {
		int N;

		cin >> N;

		vector<Boat> boats = vector<Boat>(N);

		for (int k = 0; k < N; ++k) {
			int dock, length;
			cin >> length;
			cin >> dock;
			boats[k] = Boat(dock, length);
		}

		sort(boats.begin(), boats.end());

		// calculate how many boats we can have tied at most
		// using greedy earliest finish first
		int count = 0;
		int lower_limit = numeric_limits<int>::min();
		int upper_limit = numeric_limits<int>::max();

		for (int k = 0; k < N;) {
			// skip all that have a dock behind the lower limit:
			while (boats[k].dock < lower_limit && k < N) {
				++k;
			}

			// couldn't find a dock above the lower limit
			if (k == N) {
				break;
			}

			// find the earliest finish of the possible candidates
			while (boats[k].dock < upper_limit && k < N) {
				int new_limit = max(lower_limit + boats[k].length,
						boats[k].dock);
				if (new_limit < upper_limit) {
					upper_limit = new_limit;
				}
				++k;
			}

			++count;
			lower_limit = upper_limit;
			upper_limit = numeric_limits<int>::max();
		}

		cout << count << endl;
	}
}
