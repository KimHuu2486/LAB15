#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int dest;
    int weight;
    Edge(int d, int w): dest(d), weight(w){}
};
class Graph {
private:
    int V;
    vector<vector<Edge>>adjList;
public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(Edge(dest, weight));
        adjList[dest].push_back(Edge(src, weight));
    }
    void primMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
        vector<int>key(V, INT_MAX);
        vector<int>parent(V, -1);
        vector<bool>inMST(V, false);
        key[0] = 0;
        pq.push({ 0, 0 });
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (inMST[u]) continue;
            inMST[u] = true;
            for (auto cur : adjList[u]) {
                if (!inMST[cur.dest] && cur.weight < key[cur.dest]) {
                    key[cur.dest] = cur.weight;
                    parent[cur.dest] = u;
                    pq.push({ cur.weight, cur.dest });
                }
            }
        }
        printMST(parent);
    }
    void printMST(const vector<int>& parent) {
        cout << "Edge \tWeight\n";
        int totalWeight = 0;
        for (int i = 0; i < V; i++) {
            if (parent[i] != -1) {
                for (auto cur : adjList[i]) {
                    if (cur.dest == parent[i]) {
                        cout << parent[i] << " - " << i << "\t" << cur.weight << endl;
                        totalWeight += cur.weight;
                        break;
                    }
                }
            }
        }
        cout << "Total MST weight: " << totalWeight << endl;
    }
};

int main()
{
    Graph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 9);
    g.addEdge(1, 2, 8);
    g.addEdge(0, 1, 4);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    cout << "Mininum Spanning Tree using optimized Prim's algorithm: " << endl;
    g.primMST();
    return 0;
}
//#include <iostream>
//#include <vector>
//#include <queue>
//#include <utility>  // for pair
//#include <functional>  // for greater
//using namespace std;
//
//const int MAXN = 1000;
//vector<pair<int, int>> adj[MAXN]; // adj[u] = {v, weight}
//vector<bool> visited;
//vector<tuple<int, int, int>> mstEdges; // lưu các cạnh trong MST: {u, v, weight}
//typedef pair<int, int> Edge; // {weight, to}
//
//// Hàm thêm cạnh vào đồ thị
//void addEdge(int u, int v, int w) {
//    adj[u].push_back({ v, w });
//    adj[v].push_back({ u, w }); // vì là đồ thị vô hướng
//}
//
//// Lazy Prim's Algorithm có lưu cạnh
//int lazyPrim(int start, int n) {
//    visited.assign(n, false);
//    mstEdges.clear();
//    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
//    int mst_weight = 0;
//
//    visited[start] = true;
//    for (auto [v, w] : adj[start]) {
//        pq.push({ w, start, v }); // push cạnh (w, from, to)
//    }
//
//    while (!pq.empty()) {
//        auto [w, from, to] = pq.top(); pq.pop();
//        if (visited[to]) continue;
//
//        // Đánh dấu và thêm cạnh vào MST
//        visited[to] = true;
//        mst_weight += w;
//        mstEdges.push_back({ from, to, w });
//
//        // Push các cạnh mới từ 'to'
//        for (auto [v, weight] : adj[to]) {
//            if (!visited[v]) {
//                pq.push({ weight, to, v });
//            }
//        }
//    }
//
//    return mst_weight;
//}
//
//int main() {
//    int n = 5;
//    addEdge(0, 1, 2);
//    addEdge(0, 3, 6);
//    addEdge(1, 2, 3);
//    addEdge(1, 3, 8);
//    addEdge(1, 4, 5);
//    addEdge(2, 4, 7);
//    addEdge(3, 4, 9);
//
//    int totalWeight = lazyPrim(0, n);
//    cout << "Total weight of MST: " << totalWeight << endl;
//    cout << "Edges in MST:\n";
//    for (auto [u, v, w] : mstEdges) {
//        cout << u << " - " << v << " (weight = " << w << ")\n";
//    }
//
//    return 0;
//}
