#include <cassert>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

template<typename T>
class Pos {
public:
	Pos() {}
	Pos(T x, T y) : x(x), y(y) {}
	T x, y;
};

template<typename T>
class State : public Pos<T> {
public:
	State() {}
	State(T x, T y, T v, T u) : Pos<T>(x, y), v(v), u(u) {}
	T v, u;
	bool operator< (const State& other) const {
		return this->x < other.x || (this->x == other.x && this->y < other.y)
			|| (this->x == other.x && this->y == other.y && v < other.v)
			|| (this->x == other.x && this->y == other.y && v == other.v && u < other.u);
	}
};

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

	T operator()(int x, int y) const {
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

int bsf(const Pos<int>& start, const Pos<int>& end, const Matrix<int>& obs) {
	int hops = 0;
	vector<State<int> > current, next;
	current.push_back(State<int>(start.x, start.y, 0, 0));

	set<State<int> > visited;
	visited.insert(State<int>(start.x, start.y, 0, 0));

	while (!current.empty()) {

		for (vector<State<int> >::iterator it = current.begin();
				it != current.end(); ++it) {
		
			if (it->x == end.x && it->y == end.y) {
				return hops;
			}

			for (int dv = -1; dv <= 1; ++dv) {
				if (!(-3 <= it->v + dv && it->v + dv <= 3)) {
					continue;
				}

				for (int du = -1; du <= 1; ++du) {
					if (!(-3 <= it->u + du && it->u + du <= 3)) {
						continue;
					}
					State<int> c(it->x + it->v + dv,
									it->y + it->u + du,
									it->v + dv,
									it->u + du);

					if (!obs.inBounds(c.x, c.y)
							|| obs(c.x, c.y)
							|| visited.find(c) != visited.end()) {
						continue;
					}

					visited.insert(c);
					next.push_back(c);
				}
			}
		}

		current.clear();
		swap(current, next);
		++hops;
	}

	return -1;
}

int main() {
	int testcases;
	cin >> testcases;

	for (int test = 0; test < testcases; ++test) {
		int X, Y;
		cin >> X;
		cin >> Y;

		int x1, x2, y1, y2;
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		Pos<int> start(x1, y1);
		Pos<int> end(x2, y2);

		int P;
		cin >> P;
		Matrix<int> obs(X, Y);
		for (int i = 0; i < P; ++i) {
			int x1, x2, y1, y2;
			cin >> x1;
			cin >> y1;
			cin >> x2;
			cin >> y2;
			for (int x = x1; x <= x2; ++x) {
				for (int y = y1; y <= y2; ++y) {
					obs(x, y) = 1;
				}
			}
		}

		int hops = bsf(start, end, obs);
		if (hops == -1) {
			cout << "No solution." << endl;
		} else {
			cout << "Optimal solution takes " << hops << " hops." << endl;
		}
	}
}
