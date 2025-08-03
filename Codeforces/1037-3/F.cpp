#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
 
typedef long long LL;
const int MAXN = 200010;
 
int T, n, q;
int c[MAXN];

int u, v, w;
int fa[MAXN], weight_fa[MAXN];
map<int, LL> c_num[MAXN];
 
int cnt, h[MAXN];
int nxt[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

void add_edge(int u, int v, int w) {
    nxt[++cnt] = h[u];
    h[u] = cnt;
    to[cnt] = v;
    weight[cnt] = w;
}

 
LL DFS(int root) {
    LL ans = 0;
    for(int i = h[root]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == fa[root]) continue;
        fa[v] = root; weight_fa[v] = weight[i];
        ans += DFS(v);
        if(c[root] != c[v]) ans += weight[i];
        c_num[root][c[v]] += weight[i];
    }
    return ans;
}
 
int main(){
    read(T);
    while(T--) {
        read(n); read(q);
        for(int i = 1; i <= n; ++i) read(c[i]);
        
        cnt = 0;
        for(int i = 1; i <= n; ++i) fa[i] = h[i] = - 1;
        for(int i = 1; i <= n; ++i) c_num[i].clear();
 
        for(int i = 1; i < n; ++i) {
            read(u); read(v); read(w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        LL ans = DFS(1);
        for(int i = 1; i <= q; ++i) {
            read(u); read(w);

            ans += c_num[u][c[u]];
            ans -= c_num[u][w];

            if(fa[u] != -1) {
                if(c[fa[u]] == c[u]) ans += weight_fa[u];
                if(c[fa[u]] == w) ans -= weight_fa[u];
                c_num[fa[u]][c[u]] -= weight_fa[u];
                c_num[fa[u]][w] += weight_fa[u];
            }
            c[u] = w;
            printf("%lld\n", ans);
        }
    }
    return 0;
}