#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;

class edge {
public:
    edge(int v1, int v2) : _v1(v1), _v2(v2) {
        if (_v1 > _v2)
            swap(_v1, _v2);
    }

    int v1() const {
        return _v1;
    }

    int v2() const {
        return _v2;
    }

    bool operator<(const edge& other) const {
        return v1() < other.v1() || (v1() == other.v1() && v2() < other.v2());
    }
private:
    int _v1, _v2;
};

void dfs(const vector<vector<int> >& bridges, vector<int>& preorder, vector<int>& st,
        vector<int>& visited, int prev, int node) {

    assert(st[node] == -1);
    assert(!visited[node]);

    preorder.push_back(node);
    st[node] = prev;
    visited[node] = 1;

    for (int i = 0; i < bridges[node].size(); ++i) {
        if (visited[bridges[node][i]])
            continue;

        dfs(bridges, preorder, st, visited, node, bridges[node][i]);
    }
}

void build_chain(const vector<int>& st, vector<int>& visited, set<edge>& critical,
        int prev, int node) {

    critical.erase(edge(prev, node));

    if (visited[node])
        return;

    visited[node] = 1;

    if (st[node] == -1)
        // reached top of spanning tree
        return;

    build_chain(st, visited, critical, node, st[node]);
}

void chain_decomposition(const vector<vector<int> >& bridges, vector<int>& visited,
        set<edge>& critical, const vector<int>& st, int node) {

    // find backedges:
    for (int i = 0; i < bridges[node].size(); ++i) {
        if (st[node] == bridges[node][i] || st[bridges[node][i]] == node)
            continue;
        visited[node] = 1;
        build_chain(st, visited, critical, node, bridges[node][i]);
    }
}

int main() {

    cout.sync_with_stdio(false);
    cin.sync_with_stdio(false);

    int testcases;
    cin >> testcases;

    for (int test = 0; test < testcases; ++test) {
        int n, m;
        cin >> n;
        cin >> m;

        vector<vector<int> > bridges(n);
        set<edge> critical;

        for (int i = 0; i < m; ++i) {
            int v1, v2;
            cin >> v1;
            cin >> v2;
            bridges[v1 - 1].push_back(v2 - 1);
            bridges[v2 - 1].push_back(v1 - 1);
            critical.insert(edge(v1 - 1, v2 - 1));
        }

        // create spanning tree
        vector<int> st(n, -1); // spanning tree
        vector<int> visited(n);
        vector<int> preorder;

        for (int edge = 0; edge < n; ++edge) {
            if (visited[edge])
                continue;

            dfs(bridges, preorder, st, visited, -1, edge);
        }

        visited = vector<int>(n);
        for (int i = 0; i < preorder.size(); ++i) {
            chain_decomposition(bridges, visited, critical, st, preorder[i]);
        }

        cout << critical.size() << endl;
        for (set<edge>::iterator it = critical.begin();
                it != critical.end(); ++it) {

            cout << it->v1() + 1 << ' ' << it->v2() + 1 << endl;
        }
    }

}
