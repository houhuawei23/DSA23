/*
- 题目描述
给出一个 n 个, m 条边的无向图，求图的割点。

- 输入格式
第一行输入两个正整数 n,m。
下面 m 行每行输入两个正整数 x,y 表示 x 到 y 有一条边。

- 输出格式
第一行输出割点个数。
第二行按照节点编号从小到大输出节点，用空格隔开。

- 输入输出样例
输入
6 7
1 2
1 3
1 4
2 5
3 5
4 5
5 6
输出
1
5

- 数据规模
全部数据：1 ≤ n ≤ 2e4, 1 ≤ m ≤ 1e5
*/
#include <bits/stdc++.h>

using namespace std;

int cut_num = 0;
int deep = 1;

void tarjan(int cur, int parent, vector<int>& adj, int dfn[], int low[], bool visited[]) {
    int child_num = 0;
    visited[cur] = true;
    dfn[cur] = low[cur] = deep;
    deep++;
    for (auto adj_node : adj[cur]){
        if (!visited[adj_node]) {
            child_num ++;
            tarjan(adj_node, cur, adj, dfn, low, visited);
            low[cur] = min(low[cur], low[adj_node]);
            if (parent != -1 && low[adj_node] >= dfn[cur]) {
                cut_num ++;
            }
        }
    }
}


int main() {
    int n, m; cin >> n >> m;
    vector<int> adj[n];
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int dfn[n], low[n];
    bool visited[n];
    memset(visited, false, sizeof(visited));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));

}