#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int T, n, k;
int a[MAXN];

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
        for(int i = 0; i < n; ++i) read(a[i]);

        int now_level = a[k - 1];
        sort(a, a + n);
        
        int water_level = 0;
        bool flag = true;
        for(int i = 0; i < n; ++i) {
            if(a[i] >= now_level) {
                if(a[i] - now_level > now_level - water_level) {
                    flag = false;
                    break;
                }
                else {
                    water_level += a[i] - now_level;
                    now_level = a[i];
                }
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}