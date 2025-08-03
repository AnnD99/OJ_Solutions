#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
int n, m;
int a[MAXN], b[MAXN];

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
    read(n); read(m);
    for(int i = 0; i < n; ++i) read(a[i]);
    for(int i = 0; i < m; ++i) read(b[i]);

    sort(b, b + m);
    int now = 0;
    for(int i = 0; i < n; ++i) {
        while(now < m){
            if(b[now] == a[i]){
                ++now;
                a[i] = -1;
            } 
            else if(b[now] > a[i]) break;
            else ++now;
        }
    }

    for(int i = 0; i < n; ++i){
        if(a[i] != -1)printf("%d ", a[i]);
    }printf("\n");
    return 0;
}


