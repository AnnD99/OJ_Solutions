#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
const int MAXN = 500010;
const float alpha = 0.333;
const ll MAXLEN = 1e18;

int q, l, r, cnt;
ll pos;

int rt[MAXN];
int L[MAXN << 5], R[MAXN << 5];
ll sz[MAXN << 5];

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

bool check_size(ll l_sz, ll r_sz) {
    return l_sz < alpha * (l_sz + r_sz);
}

int join(int l, int r) {
    ++cnt;
    L[cnt] = l;
    R[cnt] = r;
    sz[cnt] = min(MAXLEN, sz[l] + sz[r]);
    return cnt;
}

int merge(int l, int r) {
    if(sz[l] == MAXLEN) return l;
    if(check_size(sz[l], sz[r])) {
        int x = L[r], y = R[r];
        if(check_size(sz[y], sz[l] + sz[x])){
            int a = L[x], b = R[x];
            return merge(merge(l, a), merge(b, y));
        }
        else return merge(merge(l, x), y);
    }
    if(check_size(sz[r], sz[l])) {
        int x = L[l], y = R[l];
        if(check_size(sz[x], sz[y] + sz[r])) {
            int a = L[y], b = R[y];
            return merge(merge(x, a), merge(b, r));
        }
        else return merge(x, merge(y, r));
    }
    return join(l, r);
}

void query(int root, ll pos) {
    if(root == 1) { putchar('1'); printf("\n"); return;}
    if(root == 0) { putchar('0'); printf("\n"); return;}

    int x = L[root], y = R[root];
    if(pos > sz[x]) query(y, pos - sz[x]);
    else query(x, pos);
}

int main() {
    read(q);
    sz[0] = sz[1] = 1;
    rt[0] = 0; rt[1] = 1;
    cnt = 1;

    for(int i = 2; i <= q + 1; ++i) {
        read(l); read(r); read(pos);
        rt[i] = merge(rt[l], rt[r]);
        query(rt[i], pos);
    }
    return 0;
}