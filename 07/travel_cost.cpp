#include <iostream>
#include <iomanip>
#include <vector>

#define LIMIT 1000

using namespace std;

int main() {

	int testcases;
	cin >> testcases;
	for (int k = 0; k < testcases; ++k) {
		int D, N;
		cin >> D; // total distance
		cin >> N; // number of stations

		// read distances & costs
		vector<int> distances = vector<int>(N);
		vector<int> costs = vector<int>(N);
		for (int i = 0; i < N; ++i) {
			cin >> distances[i];
			cin >> costs[i];
		}

		int fuel = LIMIT;
		int cost = 0;
		int prev_distance = 0;
		bool possible = true;
		for (int i = 0; i < N; ++i) {
			fuel -= distances[i] - prev_distance;
			prev_distance = distances[i];

			if (fuel < 0) {
				possible = false;
				break;
			}

			// decide how much fuel to buy:
			// we will buy exactly as much needed until we get to a gas station
			// where we can buy cheaper fuel or we will fill the tank completely
			bool cheaper = false; // wheather we've found a cheaper gas station
			for (int l = i; l < N; ++l) {
				// can we still reach it?
				if (distances[l] - distances[i] > 1000) {
					break;
				}
				// found a cheaper one
				if (costs[i] > costs[l]) {
					// buy fuel until here
					int required_fuel = distances[l] - distances[i] - fuel;
					if (required_fuel > 0) {
						cost += required_fuel*costs[i];
						fuel += required_fuel;
					}
					cheaper = true;
					break;
				}
			}

			if (!cheaper) {
				// we haven't found a cheaper gas station
				// fill the tank as much as necessary
				int required_distance = min(1000, D - distances[i]);
				int required_fuel = required_distance - fuel;
				if (required_fuel > 0) {
					cost += required_fuel*costs[i];
					fuel += required_fuel;
				}
			}
		}

		// can we reach the final destination with the last tank fill?
		if (fuel < D - distances.back()) {
			possible = false;
		}

		if (!possible) {
			cout << "impossible" << endl;;
			continue;
		} else {
			cout << setprecision (1) << fixed << (double) cost/10 << endl;;
		}
	}
}
