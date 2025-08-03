#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 10010;
const int MAXP = 1010;
int n, q, init;
int p[MAXN], a[MAXN], b[MAXN];
int sum[MAXN];
int f[MAXN][1010];

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

void init_f() {
    for(int j = 0; j <= 1000; ++j) f[n + 1][j] = j;
    for(int i = n; i >= 1; --i) {
        for(int j = 0; j <= 1000; ++j) {
            if(p[i] >= j) f[i][j] = f[i + 1][j + a[i]];
            else f[i][j] = f[i + 1][max(0, j - b[i])];
        }
    }
}

int main() {
    read(n);
    for(int i = 1; i <= n; ++i) {
        read(p[i]); read(a[i]); read(b[i]);
    }
    sum[0] = 0;
    for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + b[i];
    init_f();
    
    read(q);
    while(q--) {
        read(init);
        int ans = 0;
        int p = lower_bound(sum, sum + n + 1, init - 500) - sum;
        if(p >= n) ans = init - sum[n];
        else ans = f[p + 1][init - sum[p]];
        printf("%d\n", ans);
    }
    return 0;
}