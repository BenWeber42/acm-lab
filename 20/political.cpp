#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Road {
public:
    Road(int param1, int param2, int start, int end) :
        param1(param1), param2(param2), start(start), end(end) {}
    int param1, param2, start, end;
    bool operator<(const Road& other) const {
        return other.param1 < param1;
    }
    bool equal(const Road& other) const {
        return start == other.start && end == other.end &&
            param1 == other.param2 && param2 == other.param1;
    }
};

bool byRoad(const Road& r1, const Road& r2) {
    return r1.start < r2.start || (r1.start == r2.start && r1.end < r2.end);
}

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

void spanning_tree(priority_queue<Road>& queue, vector<Road>& tree, const int size) {
    Union nodes(size);
    while (!queue.empty()) {
        assert(queue.size() >= 1);
        Road next = queue.top();
        queue.pop();

        if (nodes.find(next.start) != nodes.find(next.end)) {
            tree.push_back(next);
            nodes.add(next.start, next.end);
        }
    }
}

int main() {
    int islands;
    cin >> islands;

    for (int island = 0; island < islands; ++island) {
        int v, e;
        cin >> v;
        cin >> e;

        priority_queue<Road> costs;
        priority_queue<Road> times;

        for (int i = 0; i < e; ++i) {
            int start, end, time, cost;
            cin >> start;
            cin >> end;
            cin >> time;
            cin >> cost;
            costs.push(Road(cost, time, start, end));
            times.push(Road(time, cost, start, end));
        }

        // spanning trees:
        vector<Road> st_costs;
        vector<Road> st_times;

        spanning_tree(costs, st_costs, v);
        spanning_tree(times, st_times, v);

        sort(st_costs.begin(), st_costs.end(), byRoad);
        sort(st_times.begin(), st_times.end(), byRoad);

        assert(st_costs.size() == st_times.size());
        assert(st_costs.size() == v - 1);

        bool equal = true;
        for (int i = 0; i < v - 1; ++i) {
            assert(!i || byRoad(st_costs[i - 1], st_costs[i]));
            assert(!i || byRoad(st_times[i - 1], st_times[i]));
            if (!st_costs[i].equal(st_times[i])) {
                equal = false;
                break;
            }
        }

        cout << (equal ? "yes" : "no") << endl;
    }
}
