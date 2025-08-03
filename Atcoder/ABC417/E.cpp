#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1010;
const int MAXM = 100010;

int T;
int n, m, x, y, u, v;

vector<int> to[MAXN];
bool vis[MAXN];
int ans[MAXN], ans_cnt;

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

bool DFS(int u) {
    if(vis[u]) return false;
    vis[u] = true;

    ans[++ans_cnt] = u;
    if(u == y) return true;

    for(int v: to[u]) {
        if(DFS(v)) return true;
    }
    --ans_cnt;
    return false;
}

int main() {
    read(T); 
    while(T--) {
        read(n); read(m); read(x); read(y);
        for(int i = 1; i <= n; ++i) to[i].clear();
        for(int i = 1; i <= m; ++i) {
            read(u); read(v);
            to[u].push_back(v);
            to[v].push_back(u);
        }
        for(int i = 1; i <= n; ++i) sort(to[i].begin(), to[i].end());
        for(int i = 1; i <= n; ++i) vis[i] = false;
        ans_cnt = 0;
        DFS(x);
        for(int i = 1; i <= ans_cnt; ++i){
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}