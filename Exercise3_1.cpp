#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct edge {
    int u, v, w;
};
int n, m;
vector<vector<pair<int, int>>>adj;
vector<bool>used;
vector<int>parent;
vector<int>d;

void prim(int u) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>heap;
    vector<edge>mst;
    int res = 0;
    heap.push({ 0, u });
    while (!heap.empty()) {
        auto top = heap.top();
        heap.pop();

        if (used[top.second]) continue;
        res += top.first;
        used[top.second] = true;
        if (u != top.second) {
            mst.push_back({ top.second, parent[top.second], top.first });
        }
        for (auto it : adj[top.second]) {
            int y = it.first, w = it.second;
            if (!used[y] && w < d[y]) {
                heap.push({ w, y });
                d[y] = w;
                parent[y] = top.second;
            }
        }
    }
    cout << "MST: " << res << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << mst[i].u << " " << mst[i].v << " " << mst[i].w << endl;
    }
}

int main()
{
    cin >> n >> m;
    adj.resize(n + 1);
    used.resize(n + 1, false);
    parent.resize(n + 1);
    d.resize(n + 1, INT_MAX);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
    prim(1);
    return 0;
}
//6 9
//1 2 9
//1 3 4
//2 3 1
//2 4 6
//3 5 2
//4 5 3
//4 6 10
//5 6 8
//2 5 3