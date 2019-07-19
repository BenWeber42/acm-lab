#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Sum {
public:
    int prev_num, sum, pluses;
    Sum(int prev_num, int sum, int pluses)
        : prev_num(prev_num), sum(sum), pluses(pluses) {}

    bool operator<(const Sum& other) const {
        return sum < other.sum || (sum == other.sum && prev_num < other.prev_num) ||
            (prev_num == other.prev_num && sum == other.sum && pluses < other.pluses);
    }
    int total() const {
        return prev_num + sum;
    }
};

int pluses(const vector<int>& digits, int K) {

    vector<Sum> sums;
    sums.push_back(Sum(digits[0], 0, 0));
    vector<Sum> next;

    for (int index = 1; index < (int) digits.size(); ++index) {

        // use plus
        for (vector<Sum>::iterator it = sums.begin();
                it != sums.end(); ++it) {

            if (it->sum + it->prev_num + digits[index] <= K)
                next.push_back(
                    Sum(digits[index], it->sum + it->prev_num, it->pluses + 1));
        }

        // don't use plus
        for (vector<Sum>::iterator it = sums.begin();
                it != sums.end(); ++it) {

            if (it->sum + it->prev_num*10 + digits[index] <= K)
                next.push_back(
                    Sum(it->prev_num*10 + digits[index], it->sum, it->pluses));
        }

        if (next.empty()) {
            return -1;
        }

        // remove doubles:
        sort(next.begin(), next.end());

        sums.clear();
        sums.push_back(next.front());

        for (vector<Sum>::iterator it = ++next.begin();
                it != next.end(); ++it) {

            if (it->sum == sums.back().sum && it->prev_num == sums.back().prev_num) {
                sums.back().pluses = min(it->pluses, sums.back().pluses);
            } else {
                sums.push_back(*it);
            }
        }

        next.clear();
    }

    int min_pluses = numeric_limits<int>::max();

    for (vector<Sum>::iterator it = sums.begin();
            it != sums.end(); ++it) {

        if (it->total() == K)
            min_pluses = min(min_pluses, it->pluses);
    }

    return min_pluses == numeric_limits<int>::max() ? -1 : min_pluses;
}

int main () {

    ios_base::sync_with_stdio(false);

    int tests;
    cin >> tests;

    while (tests--) {
        int n, K;
        cin >> n >> K;

        vector<int> digits(n);

        for (int i = 0; i < n; ++i) {
            cin >> digits[i];
        }

        cout << pluses(digits, K) << endl;
    }
}
