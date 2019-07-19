#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

class P {
public:
    int x, y;
    P() : x(0), y(0) {}
    P(int x, int y) : x(x), y(y) {}
    bool operator==(const P& other) const {
        return x == other.x && y == other.y;
    }
};

bool lower_left(const P& p1, const P& p2) {
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

/**
 * p1 is the mid point, p2 & p3 are the end points
 */
bool cross(const P& p1, const P& p2, const P& p3) {
    return 0 < (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

class byAngle {
public:
    byAngle(P& p) : p(p) {}
    bool operator()(const P& p1, const P& p2) const {
        if (p1 == p)
            return true;
        if (p2 == p)
            return false;
        return cross(p, p1, p2);
    }
private:
    P p;
};

void output(double x) {
    cout << fixed << showpoint << setprecision(3) << round(x*1000.0)/1000.0 << endl;
}

double dist(P p1, P p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

int main() {
    int testcases;
    cin >> testcases;

    for (int test = 0; test < testcases; ++test) {
        /**
         * Using graham's scan algorithm (running time O( n log(n) ))
         */
        int T;
        cin >> T;

        P start(numeric_limits<int>::max(), numeric_limits<int>::max());
        vector<P> ps(T);
        for (int i = 0; i < T; ++i) {
            int x, y;
            cin >> x >> y;
            ps[i] = P(x, y);
            start = min(start, ps[i], lower_left);
        }

        if (0 == T || 1 == T) {
            output(0.0);
            continue;
        } else if (2 == T) {
            output(2.0*dist(ps[0], ps[1]));
            continue;
        }

        // sort by angle
        sort(ps.begin(), ps.end(), byAngle(start));

        // create hull
        vector<P> hull;
        hull.push_back(ps[0]);
        hull.push_back(ps[1]);

        for (int i = 2; i < T; ++i) {
            P p1 = *(hull.end() - 1);
            P p2 = *(hull.end() - 2);
            P p3 = ps[i];
            while (hull.size() >= 2 && cross(p1, p2, p3)) {
                hull.pop_back();
                p1 = *(hull.end() - 1);
                p2 = *(hull.end() - 2);
            }
            hull.push_back(p3);
        }

        hull.push_back(ps[0]);

        // calculate distance
        double total = 0.0;
        for (int i = 1; i < hull.size(); ++i) {
            total += dist(hull[i - 1], hull[i]);
        }

        output(total);
    }
}
