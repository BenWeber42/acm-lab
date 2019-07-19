#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

class Union {
public:
    Union(int n) : map(n), sizes(n, 1) {
        for (int i = 0; i < n; ++i) {
            map[i] = i;
        }
    }

    void add(int n1, int n2) {
        int r1, r2;

        r1 = find(n1);
        r2 = find(n2);

        int s1 = sizes[r1];
        int s2 = sizes[r2];

        if (s1 < s2) {
            map[r1] = r2;
            sizes[r2] = s1 + s2;
        } else {
            map[r2] = r1;
            sizes[r1] = s1 + s2;
        }
    }

    int find(int node) {
        int root = _find(node);
        collapse(node, root);
        return root;
    }
private:
    int _find(int node) {
        if (map[node] == node)
            return node;
        return _find(map[node]);
    }

    void collapse(int node, int root) {
        if (node == root) {
            assert(map[node] == root);
            return;
        }
        int next = map[node];
        map[node] = root;
        collapse(next, root);
    }
    vector<int> map;
    vector<int> sizes;
};

class Link {
public:
    Link() : start(-1), end(-1), cost(-1) {}
    Link(int start, int end, int cost) : start(start), end(end), cost(cost) {}
    int start, end, cost;
};

bool byCost(const Link& l1, const Link& l2) {
    return l1.cost < l2.cost;
}

int main() {
    ios_base::sync_with_stdio(false);

    int testcases;
    cin >> testcases;

    for (int test = 0; test < testcases; ++test) {
        int n, m;
        cin >> n >> m;

        vector<Link> links(m);

        for (int i = 0; i < m; ++i) {
            int start, end, cost;
            cin >> start >> end >> cost;

            links[i] = Link(start, end, cost);
        }

        sort(links.begin(), links.end(), byCost);

        map<int, int> costs;
        Union components(n);

        for (int i = 0; i < m; ++i) {
            Link link = links[i];

            int r1 = components.find(link.start);
            int r2 = components.find(link.end);
            if (r1 != r2) {
                int cost = 0;
                if (costs.find(r1) != costs.end()) {
                    cost += costs[r1];
                    costs.erase(r1);
                }
                if (costs.find(r2) != costs.end()) {
                    cost += costs[r2];
                    costs.erase(r2);
                }
                cost += link.cost;
                components.add(r1, r2);
                costs[components.find(r1)] = cost;
            }
        }

        int total = 0;
        int first = numeric_limits<int>::max();
        for (map<int, int>::iterator it = costs.begin();
                it != costs.end(); ++it) {

            if (it->second <= 1000000)
                ++total;
            first = min(first, it->second);
        }

        cout << total << ' ' << first << endl;
    }
}
