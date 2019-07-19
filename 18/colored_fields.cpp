#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace std;

/**
 * Matrix class with column major
 */
template<typename T>
class Matrix {
public:
	Matrix(int width, int height):
		width(width), height(height), elem(width*height) {}

	T& operator()(int x, int y) {
		assert(inBounds(x, y));
		return elem[height*y + x];
	}

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

	int inBounds(int x, int y) const {
		return 0 <= x && x < height && 0 <= y && y < width;
	}

private:
	int width, height;
	vector<T> elem;
};

void bsf(Matrix<int>& dist, vector<pair<int, int> >& current) {
	vector<pair<int, int> > next;

	int distance = 0;

	while (!current.empty()) {

		// set distance
		for (vector<pair<int, int> >::iterator it = current.begin();
				it != current.end(); ++it) {
		
			dist(it->first, it->second) = distance;
		}

		// explore further
		for (vector<pair<int, int> >::iterator it = current.begin();
				it != current.end(); ++it) {
		
			if (dist.inBounds(it->first - 1, it->second)
					&& dist(it->first - 1, it->second) == -1) {
			
				next.push_back(pair<int, int>(it->first - 1, it->second));
			}

			if (dist.inBounds(it->first + 1, it->second)
					&& dist(it->first + 1, it->second) == -1) {
			
				next.push_back(pair<int, int>(it->first + 1, it->second));
			}

			if (dist.inBounds(it->first, it->second - 1)
					&& dist(it->first, it->second - 1) == -1) {
			
				next.push_back(pair<int, int>(it->first, it->second - 1));
			}

			if (dist.inBounds(it->first, it->second + 1)
					&& dist(it->first, it->second + 1) == -1) {
			
				next.push_back(pair<int, int>(it->first, it->second + 1));
			}
		}

		++distance;
		current.clear();
		swap(current, next);
	}
}

int compute(Matrix<int>& dist,
		const vector<pair<int, int> >& starts,
		vector<pair<int, int> >& ends) {

	bsf(dist, ends);

	int c = numeric_limits<int>::min();
	int size = starts.size();
	for (int i = 0; i < size; ++i) {
		c = max(c, dist(starts[i].first, starts[i].second));
	}

	return c;
}

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int M;
		cin >> M;

		Matrix<int> dist(M, M);
		// first is x, second is y
		vector<pair<int, int> > starts;
		vector<pair<int, int> > ends;

		for (int x = 0; x < M; ++x) {
			for (int y = 0; y < M; ++y) {
				char color;
				cin >> color;
				if (color == '3') {
					ends.push_back(pair<int, int>(x, y));
				} else if (color == '1') {
					starts.push_back(pair<int, int>(x, y));
				}
				dist(x, y) = -1;
			}
		}

		cout << compute(dist, starts, ends) << endl;
	}
}
