#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

int gcd(int a, int b) {
	int c;
	while (b) {
		c = b;
		b = a%b;
		a = c;
	}
	return a;
}

int main() {

	int testcases;
	cin >> testcases;

	for (int i = 0; i < testcases; ++i) {
		// we will work with a*m + b*n -> l, maximizing b
		int best_a, best_b, best_diff, a, b, stop;

		int l, m, n;
		cin >> l >> m >> n;

		best_b = b = (int) floor(l/n);
		best_a = a = 0;
		best_diff = numeric_limits<int>::max();

		stop = max(b - m/gcd(m, n), 0);

		// choose b:
		for (; b >= stop; --b) {
			// find a suitable a:
			a = (int) floor((l - b*n)/(double) m);

			if (best_diff > l - (a*m + b*n)) {
				best_a = a;
				best_b = b;
				best_diff = l - (a*m + b*n);

				if (!best_diff) {
					break;
				}
			}
		}

		cout << best_a << " " << best_b << " " << best_diff << endl;

	}
}
