#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

void dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<int>&ans, int i) {
    visited[i] = true;
    for (int val : adj[i]) {
        if (!visited[val]) {
            dfs(adj, visited, ans, val);
        }
    }
    ans.push_back(i);
}
vector<int> sortTOPO(vector<vector<int>>& adj, int n) {
    vector<int>ans;
    vector<bool>visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(adj, visited, ans, i);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
vector<int> Kahn(vector<vector<int>>& adj, vector<int>& in, int n) {
    vector<int>ans;
    queue<int>q;
    vector<bool>visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        ans.push_back(cur);
        visited[cur] = true;
        q.pop();
        for (int val : adj[cur]) {
            in[val]--;
            if (in[val] == 0) {
                q.push(val);
            }
        }
    }
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>adj(n + 1);
    vector<int>in(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        in[y]++;
    }
    vector<int>ans = sortTOPO(adj, n);
    for (int val : ans) {
        cout << val << " ";
    }
    cout << endl;
    vector<int>kahn = Kahn(adj, in, n);
    for (int val : kahn) {
        cout << val << " ";
    }
    return 0;
}

//7 7
//1 2
//1 6
//2 3
//2 4
//3 5
//4 5
//7 6