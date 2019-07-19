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

bool xcomp(const Point p1, const Point p2) {
	return p1.x < p2.x;
}

bool ycomp(const Point p1, const Point p2) {
	return p1.y < p2.y;
}

num dist(Point p1, Point p2) {
	return (p1.x - p2.x)*(num) (p1.x - p2.x)
		+ (p1.y - p2.y)*(num) (p1.y - p2.y);
}

num hdist(Point p, int h) {
	return (p.x - h)*(num) (p.x - h);
}

num vdist(Point p, int v) {
	return (p.y - v)*(num) (p.y - v);
}

// a line where all X coordinates are equal
num closest_pair_line(vector<Point> points) {
	int n = points.size() - 1;

	num best = numeric_limits<num>::max();
	for (int i = 0; i < n; ++i) {
		best = min(best, dist(points[i], points[i + 1]));
	}
	return best;
}

num closest_pair(vector<Point> pointsX, vector<Point> pointsY) {

	int n = pointsX.size();

	if (n <= 1) {
		return numeric_limits<num>::max();
	} else if (n == 2) {
		return dist(pointsX[0], pointsX[1]);
	}

	int midX = pointsX[n/2].x;

	vector<Point> pointsXLeft = vector<Point>(0);
	vector<Point> pointsYLeft = vector<Point>(0);
	vector<Point> pointsXRight = vector<Point>(0);
	vector<Point> pointsYRight = vector<Point>(0);

	for (int i = 0; i < n; ++i) {
		if (pointsX[i].x <= midX) {
			pointsXLeft.push_back(pointsX[i]);
		} else {
			pointsXRight.push_back(pointsX[i]);
		}

		if (pointsY[i].x <= midX) {
			pointsYLeft.push_back(pointsY[i]);
		} else {
			pointsYRight.push_back(pointsY[i]);
		}
	}

	if (pointsXLeft.size() == n) {
		// FIXME: here it's not guaranteed that they're actually on a line.
		// see tets_hard.in
		return closest_pair_line(pointsY);
	}

	num dLeft = closest_pair(pointsXLeft, pointsYLeft);
	num dRight = closest_pair(pointsXRight, pointsYRight);

	num d = min(dLeft, dRight);

	vector<Point> verticalBar = vector<Point>(0);

	for (int i = 0; i < n; ++i) {
		if (hdist(pointsY[i], midX) <= d) {
			verticalBar.push_back(pointsY[i]);
		}
	}

	int vsize = verticalBar.size();

	for (int i = 0; i < vsize; ++i) {
		int size7 = min(i + 8, vsize);
		for (int k = i + 1; k < size7; ++k) {
			d = min(d, dist(verticalBar[i], verticalBar[k]));
		}
	}

	return d;
}

int main() {
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i) {
		int N;
		cin >> N;

		vector<Point> pointsX(N);
		vector<Point> pointsY(N);

		for (int k = 0; k < N; ++k) {
			int x, y;
			cin >> x;
			cin >> y;
			
			pointsX[k] = Point(x, y);
			pointsY[k] = Point(x, y);
		}

		sort(pointsX.begin(), pointsX.end(), xcomp);
		sort(pointsY.begin(), pointsY.end(), ycomp);

		cout << closest_pair(pointsX, pointsY) << endl;
	}
}
