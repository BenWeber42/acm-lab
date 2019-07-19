#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * Calculate all primes within [0, bound] using a trivial prime sieve
 */
vector<int> primes(const int bound) {
    vector<int> ps(bound + 1, 1);
    ps[0] = 0;
    ps[1] = 0;

    int prime = 2;
    while (prime < bound + 1) {
        // remove non-primes
        for (int i = 2*prime; i < bound + 1; i += prime) {
            ps[i] = 0;
        }
        // get next prime:
        for (++prime; prime < bound + 1 && !ps[prime]; ++prime) {}

        if (prime == bound + 1)
            break;
    }

    vector<int> ret;

    for (int i = 0; i < bound + 1; ++i) {
        if (ps[i])
            ret.push_back(i);
    }

    return ret;
}

vector<int> memo;

/**
 * Calculates the next in the graph
 */
int next(const vector<int>& ps, int c) {

    assert(0 < c && c < memo.size());

    if (memo[c] != -1) {
        return memo[c];
    }

    for (int i = 0; i < ps.size() && ps[i]*ps[i] <= c; ++i) {
        if (c % ps[i] == 0) {
            memo[c] = c / ps[i];
            return c / ps[i];
        }
    }

    // it's a prime
    memo[c] = 1;
    return 1;
}

int main() {

    ios_base::sync_with_stdio(false);

    memo = vector<int>(10000000, -1);

    // build primes
    // sqrt(10'000'000) = 3162.28
    vector<int> p = primes(3163);

    int testcases;
    cin >> testcases;

    for (int test = 0; test < testcases; ++test) {
        int n, c;
        cin >> n >> c;

        for (int i = 0; i < c; ++i) {
            int v1, v2;
            cin >> v1 >> v2;

            assert(v1 > 0 && v2 > 0);

            // start with the bigger, it might go past smaller:
            int steps = 0;
            while (v1 != v2) {
                ++steps;
                if (v2 < v1) {
                    v1 = next(p, v1);
                } else {
                    v2 = next(p, v2);
                }
            }

            cout << steps << endl;
        }
    }

}
