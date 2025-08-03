#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct {
    int l, r;
    int value;
}a[MAXN];

int T, n, k;

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

int main() {
    read(T);
    while(T--) {
        read(n); read(k);
        for(int i = 0; i < n; ++i) {
            read(a[i].l); read(a[i].r); read(a[i].value);
        }

        sort(a, a + n, [](const auto &x, const auto &y) {
            if(x.l == y.l) return x.value < y.value;
            return x.l < y.l;
        });

        int ans = k;
        for(int i = 0; i < n; ++i) {
           if(ans >= a[i].l && ans <= a[i].r) ans = max(ans, a[i].value);
        }
        printf("%d\n", ans);
    }
    return 0;
}