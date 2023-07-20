// tarjan 算法求无向图的桥
/*
    SIZE —— 节点的个数，可以基于实际的节点个数增加一些冗余度
    关于 head / Next / ver 变量的介绍，可以参阅下面的动画配合理解
    假设场景，有一个节点 u，以及其直接相连的若干节点 v1，v2，v3
    head[u] 代表节点 u 直接相邻的第一个节点 v1 的序号（tot1）
    Next[tot1] 代表节点 u 直接相邻的下一个节点的序号（tot2）
    ver[tot1] 代表序号为 tot1 的节点的值（v1）
    dfn[x] 代表节点 x 对应的时间戳，low[x] 代表节点 x 的追溯值
    n 与 m 代表程序的标准输入的参数，n 代表节点的个数，m 代表边的个数
    tot 代表每一个节点的序号
    num 代表每一个节点的时间戳
    bridge[tot] 代表序号为 tot 的边是否为桥
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 100010;

int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE];
int n, m, tot, num;
bool bridge[SIZE * 2];

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++num;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x])
                bridge[i] = bridge[i ^ 1] = true;
        }
        else if (i != (in_edge ^ 1))
            low[x] = min(low[x], dfn[y]);
    }
}

int main() {
    // [[0,1],[1,2],[2,0],[1,3]]
    cin >> n >> m;
    tot = 1;
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
    for (int i = 2; i < tot; i += 2)
        if (bridge[i])
            printf("%d %d\n", ver[i ^ 1], ver[i]);
}