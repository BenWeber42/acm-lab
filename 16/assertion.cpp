#include <cassert>
#include <iostream>

using namespace std;

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int X, Y;
		cin >> X;
		cin >> Y;

		int x1, x2, y1, y2;
		cin >> x1; // start x
		cin >> y1; // start y
		cin >> x2; // end x
		cin >> y2; // end y

		int P;
		cin >> P;

		for (int i = 0; i < P; ++i) {
			int x1, x2, y1, y2;
			cin >> x1;
			cin >> y1;
			cin >> x2;
			cin >> y2;
			assert(0 <= x1 && x1 <= x2 && x2 < X);
			assert(0 <= y1 && y1 <= y2 && y2 < Y);
		}
	}
}
