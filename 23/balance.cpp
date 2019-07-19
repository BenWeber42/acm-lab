#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int testcases;
    cin >> testcases;
    for (int test = 0; test < testcases; ++test) {
        int n;
        cin >>n;

        vector<int> xs(n);

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            sum += x;
            xs[i] = x;
        }

        vector<int> sums(sum/2 + 1, 0);
        sums[0] = 1;

        for (int i = 0; i < n; ++i) {
            int x = xs[i];
            for (int k = sum/2; k >= 0; --k) {
                if (sums[k]) {
                    if (k + x <= sum/2) {
                        sums[k + x] = 1;
                    }
                }
            }
        }

        int smaller = 0;
        for (int k = sum/2; k >= 0; --k) {
            if (sums[k]) {
                smaller = k;
                break;
            }
        }

        cout << sum - 2*smaller << endl;
    }
}
