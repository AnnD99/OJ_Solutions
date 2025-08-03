#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 100010;
int T, n;
int p[MAXN], s[MAXN];

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

int gcd(int x, int y) {
    while(y) {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

LL gcd_ll(LL x, LL y) {
    while(y) {
        LL t = x % y;
        x = y;
        y = t;
    }
    return x;
}



int main() {
    read(T);
    while(T--) {
        read(n);
        for(int i = 0; i < n; ++i) read(p[i]);
        for(int i = 0; i < n; ++i) read(s[i]);

        bool flag = true;
        for(int i = 0; i < n; ++i) {
            int now_gcd = gcd(p[i], s[i]);
            LL now = 1LL * p[i] * s[i] / now_gcd;
            if(i > 0){
                if(gcd_ll(now, 1LL*p[i - 1]) != p[i]) {flag = false; break;}
            }
            else if(now != p[i]) {flag = false; break;}
            if(i < n - 1) {
                if(gcd_ll(now, 1LL*s[i + 1]) != s[i]) {flag = false; break;}
            }
            else if(now != s[i]) {flag = false; break;}
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
