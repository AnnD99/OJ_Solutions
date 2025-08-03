#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 200010;
int n;
int a[MAXN], cnt[MAXN];

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
    read(n);
    for(int i = 1; i <= n; ++i) read(a[i]);
    LL ans = 0;
    for(int j = 1; j <= n; ++j) {
        int cur = j - a[j];
        if(cur > 0) ans += cnt[cur];
        cur = j + a[j];
        if(cur <= n) cnt[cur]++;
    }
    printf("%lld\n", ans);
    return 0;
}