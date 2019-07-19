#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

enum direction {
    right = 0x00,
    up = 0x01
};

class Constraint {
public:
    Constraint(int x, int y, int dir) : x(x), y(y), dir(direction(dir)) {}
    Constraint(int x, int y, direction dir) : x(x), y(y), dir(dir) {}
    int nextX() const {
        if (dir == ::right)
            return x + 1;
        return x;
    }
    int nextY() const {
        if (dir == up)
            return y + 1;
        return y;
    }
    bool operator<(const Constraint& other) const {
        return nextX() <= other.x && nextY() <= other.y;
    }
    int x, y;
    direction dir;
};

typedef unsigned long long int Int;

vector<Int> memo;

Int binomial(int n, int k) {

    assert(n >= k);

    if (n - k < k)
        return binomial(n, n - k);

    if (n == k || k == 0)
        return 1;

    Int& mem = memo[n*31 + k];

    if (mem)
        return mem;

    return mem = binomial(n - 1, k - 1) + binomial(n - 1, k);
}

int main() {
    ios_base::sync_with_stdio(false);

    memo = vector<Int>(31*31);

    int tests;
    cin >> tests;
    while(tests--) {
        int w, h, n;
        cin >> w >> h >> n;

        assert(0 <= w && w <= 30);
        assert(0 <= h && h <= 30);
        assert(0 <= n && n <= 30);

        if (n == 0) {
            cout << binomial(w + h, h) << endl;
            continue;
        }

        vector<Constraint> cs;

        while (n--) {
            int x, y, dir;
            cin >> x >> y >> dir;
            cs.push_back(Constraint(x, y, dir));
            assert(0 <= cs.back().x && cs.back().nextX() <= w);
            assert(0 <= cs.back().y && cs.back().nextY() <= h);
            assert(0 == dir || 1 == dir);
        }

        sort(cs.begin(), cs.end());

        // check whether the sorting was successful:
        bool ok = true;
        for (int i = 1; i < (int) cs.size(); ++i) {
            if (!(cs[i - 1] < cs[i])) {
                cout << 0 << endl;
                ok = false;
                break;
            }
        }

        if (!ok)
            continue;

        Int paths = binomial(cs.front().x + cs.front().y, cs.front().x);

        for (int i = 1; i < (int) cs.size(); ++i)
            paths *= binomial(cs[i].x - cs[i - 1].nextX() + cs[i].y - cs[i - 1].nextY(),
                    cs[i].x - cs[i - 1].nextX());

        paths *= binomial(w - cs.back().nextX() + h - cs.back().nextY(), w - cs.back().nextX());

        cout << paths << endl;
    }
}
