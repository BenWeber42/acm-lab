#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> memo;

int mp(const string& str, int i, int j) {

    if (i == j)
        return 0;

    if (i + 1 == j) {
        if (str[i] == str[j]) {
            return 0;
        } else {
            return 1;
        }
    }

    int& mem = memo[i*str.size() + j];

    if (mem != -1)
        return mem;

    if (str[i] == str[j]) {
        return mem = mp(str, i + 1, j - 1);
    } else {
        return mem = min(
                mp(str, i + 1, j) + 1,
                mp(str, i, j - 1) + 1
                );
    }
}

int main() {
    int T;
    cin >> T;

    for (int test = 0; test < T; ++test) {
        string str;
        cin >> str;

        memo = vector<int>(str.size()*str.size(), -1);
        cout << mp(str, 0, str.size() - 1) << endl;
    }
}
