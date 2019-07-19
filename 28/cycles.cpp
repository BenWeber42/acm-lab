#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void remove(vector<int>& vec, int c) {

    for (int i = 0; i < (int) vec.size(); ++i) {
        if (vec[i] == c) {
            vec[i] = vec.back();
            vec.pop_back();
            return;
        }
    }

    assert(false);
}

/**
 * Removes leaf u and newly created leafs and returns the number
 * of removed edges
 */
int remove_edges(vector<vector<int> >& edges, int u) {
    assert(edges[u].size() <= 1);

    if (edges[u].size() == 0) {
        return 0;
    }

    int neighbour = edges[u].front();
    edges[u].clear();
    remove(edges[neighbour], u);

    if (edges[neighbour].size() <= 1) {
        return 1 + remove_edges(edges, neighbour);
    }

    return 1;
}

bool contains(const vector<int>& vec, int c) {
    for (int i = 0; i < (int) vec.size(); ++i) {
        if (vec[i] == c)
            return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;

        vector<vector<int> > edges(n, vector<int>());
        vector<int> counts(n, 0);

        for (int i = 0; i < n; ++i) {
            int u, v;
            cin >> u >> v;

            assert(!contains(edges[u], v));
            assert(!contains(edges[v], u));

            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        vector<int> leafs;

        for (int i = 0; i < n; ++i) {
            if (edges[i].size() <= 1) {
                leafs.push_back(i);
            }
        }

        for (int i = 0; i < (int) leafs.size(); ++i) {
            n -= remove_edges(edges, leafs[i]);
        }

        cout << n << endl;
    }
}
