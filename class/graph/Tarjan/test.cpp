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

tarjan图不一定联通。
*/
#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
    int id;
    int dfn;
    int low;
    int parent;
    int visited;
    int child_num;
    bool is_cut;
    vector<Node*> adj;
    Node(){};
    // Node(int id): id(id), dfn(-1), low(-1), parent(-1), visited(false), child_num(0), is_cut(false){};
    void init(int id){
        this->id = id;
        this->dfn = -1;
        this->low = -1;
        this->parent = -1;
        this->visited = false;
        this->child_num = 0;
        this->is_cut = false;
    };
};

int cut_num = 0;
int deep = 1;

void tarjan(Node* cur_node_p){
    cur_node_p->visited = true;
    cur_node_p->dfn = deep;
    cur_node_p->low = deep;
    deep++;
    for (auto adj_node_p: cur_node_p->adj){
        if (!adj_node_p->visited) {
            cur_node_p->child_num ++;
            adj_node_p->parent = cur_node_p->id;
            tarjan(adj_node_p);
            cur_node_p->low = min(cur_node_p->low, adj_node_p->low);
            if (cur_node_p->parent != -1 && adj_node_p->low >= cur_node_p->dfn) {
                cut_num ++;
                cur_node_p->is_cut = true;
            }
        }
        else if (adj_node_p->id != cur_node_p->parent)
            cur_node_p->low = min(cur_node_p->low, adj_node_p->dfn);
    }

    if (cur_node_p->parent == -1 && cur_node_p->child_num > 1){
        cur_node_p->is_cut = true;
        cut_num ++;
    }
}

int main(){
    cout << "Hello World!" << endl;
    Node *nodes;
    int n, m; cin >> n >> m;
    nodes = new Node[n];
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        nodes[x].adj.push_back(&nodes[y]);
        nodes[y].adj.push_back(&nodes[x]);
        nodes[x].init(x);
        nodes[y].init(y);
    }
    cout << "input done" << endl;
    for (int i = 0; i < n; i++) {
        if (!nodes[i].visited) {
            tarjan(&nodes[i]);
        }
    }
    cout << cut_num << endl;
    for (int i = 0; i < n; i++) {
        if (nodes[i].is_cut)
            cout << nodes[i].id << " ";
    }
}