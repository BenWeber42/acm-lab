#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long int num;

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}
};

num dist(Point p1, Point p2) {
	return (p1.x - p2.x)*(num) (p1.x - p2.x)
		+ (p1.y - p2.y)*(num) (p1.y - p2.y);
}

num minimal_distance(const vector<Point>& points) {

	int count = points.size();
	num best = numeric_limits<num>::max();
	for (int i = 0; i < count; ++i) {
		for (int k = 0; k < i; ++k) {
			best = min(best, dist(points[i], points[k]));
		}
	}

	return best;
}

int main() {
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i) {
		int N;
		cin >> N;

		vector<Point> points(N);

		for (int k = 0; k < N; ++k) {
			int x, y;
			cin >> x;
			cin >> y;
			
			points[k] = Point(x, y);
		}

		cout << minimal_distance(points) << endl;
	}
}
