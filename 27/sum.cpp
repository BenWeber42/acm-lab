#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

vector<int> memo;

/**
 * Returns whether the sum from index to the end can be generated
 * to equal K
 */
int pluses(const vector<int>& digits, int index, int sum, const int K) {

    int& mem = memo[index*(K + 1) + sum];

    if (mem != -2)
        return mem;

    // calculate mem
    mem = numeric_limits<int>::max();

    int prev_num = 0;
    for (; index < (int) digits.size(); ++index) {
        prev_num = prev_num*10 + digits[index];

        if (prev_num > sum)
            break;

        if (index + 1 == (int) digits.size()) {
            if (prev_num == sum)
                mem = 0;
            break;
        }

        int p = pluses(digits, index + 1, sum - prev_num, K);

        if (p != -1)
            mem = min(mem, p + 1);
    }

    if (mem == numeric_limits<int>::max())
        mem = -1;

    return mem;
}

int main () {

    ios_base::sync_with_stdio(false);

    int tests;
    cin >> tests;

    while (tests--) {
        int n, K;
        cin >> n >> K;

        vector<int> digits(n);

        memo = vector<int>(n*(K + 1), -2);

        for (int i = 0; i < n; ++i) {
            cin >> digits[i];
        }

        cout << pluses(digits, 0, K, K) << endl;
    }
}
