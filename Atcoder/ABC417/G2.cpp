#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
const int MAXN = 500010;
const ll MAXLEN = 1e18;

int q, l, r;
int L[MAXN], R[MAXN];
int son[MAXN][20];
ll p[MAXN][20];
ll sz[MAXN], pos;

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

void read(ll &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

int main() {
    read(q);
    sz[0] = sz[1] = 1;
    L[0] = R[0] = L[1] = R[1] = -1;
    for(int j = 0; j <= 19; ++j) son[0][j] = son[1][j] = -1;
    for(int i = 1; i <= q; ++i) {
        read(l); read(r); read(pos);
        sz[i + 1] = min(MAXLEN, sz[l] + sz[r]);
        L[i + 1] = l; R[i + 1] = r;
        if((sz[l] << 1) >= sz[i + 1]) {
            son[i + 1][0] = l;
            p[i + 1][0] = 0;
        }
        else {
            son[i + 1][0] = r;
            p[i + 1][0] = sz[l];
        }
        for(int j = 1; j <= 19; ++j) {
            int temp = son[i + 1][j - 1];
            if(temp != -1) {
                son[i + 1][j] = son[temp][j - 1];
                p[i + 1][j] = p[i + 1][j - 1] + p[temp][j - 1];
            }
            else son[i + 1][j] = -1;
        }

        int now = i + 1;
        while(now > 1) {
            for(int j = 19; j >= 0; --j) {
                if(son[now][j] == -1) continue;
                if(pos > p[now][j] && pos <= p[now][j] + sz[son[now][j]]) {
                    pos -= p[now][j];
                    now = son[now][j];
                }
            }
            if(L[now] != -1){
                if(pos > sz[L[now]]) {
                    pos -= sz[L[now]];
                    now = R[now];
                }
                else now = L[now];
            }
        }
        printf("%d\n", now);
    }
    return 0;
}