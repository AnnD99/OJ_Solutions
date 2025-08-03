#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200010;
const int MOD = 998244353;

int n, m, l, r;
int a[MAXN];
int Seg_sum[MAXN << 2], Seg_tag[MAXN << 2];
int inv[MAXN];

void read(int &x) {
    char ch = getchar();
    while(ch < '!') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

void build(int node, int L, int R) {
    if(L == R) {
        Seg_sum[node] = a[L];
        Seg_tag[node] = -1;
        return;
    }
    int mid = (L + R) >> 1;
    build(node << 1, L, mid);
    build(node << 1 | 1, mid + 1, R);
    Seg_sum[node] = (Seg_sum[node << 1] + Seg_sum[node << 1 | 1]) % MOD;
    Seg_tag[node] = -1;
}

void push_down(int node, int L, int R) {
    if(L != R) {
        int mid = (L + R) >> 1;
        Seg_sum[node << 1] = (1LL * Seg_tag[node] * (mid - L + 1)) % MOD;
        Seg_tag[node << 1] = Seg_tag[node];

        Seg_sum[node << 1 | 1] = (1LL * Seg_tag[node] * (R - mid)) % MOD;
        Seg_tag[node << 1 | 1] = Seg_tag[node];
    }
    Seg_tag[node] = -1;
}

int ask_sum(int node, int L, int R, int l, int r) {
    if(l > r) return 0;
    if(l <= L && R <= r) {
        return Seg_sum[node];
    }

    if(Seg_tag[node] != -1) push_down(node, L, R);
    int mid = (L + R) >> 1;
    int sum_left = ask_sum(node << 1, L, mid, l, min(r, mid));
    int sum_right = ask_sum(node << 1 | 1, mid + 1, R, max(l, mid + 1), r);
    return (sum_left + sum_right) % MOD;
}

void modify(int node, int L, int R, int l, int r, int val) {
    if(l > r) return;

    if(l <= L && R <= r) {
        Seg_tag[node] = val;
        Seg_sum[node] = (1LL * val * (R - L + 1)) % MOD;
        return;
    }

    if(Seg_tag[node] != -1) push_down(node, L, R);
    int mid = (L + R) >> 1;
    modify(node << 1, L, mid, l, min(r, mid), val);
    modify(node << 1 | 1, mid + 1, R, max(l, mid + 1), r, val);
    Seg_sum[node] = (Seg_sum[node << 1] + Seg_sum[node << 1 | 1]) % MOD;
}

void print(int node, int L, int R) {
    if(Seg_tag[node] != -1) push_down(node, L, R);
    if(L == R) {
        printf("%d ", Seg_sum[node]);
        return;
    }
    int mid = (L + R) >> 1;
    print(node << 1, L, mid);
    print(node << 1 | 1, mid + 1, R);
}

int main() {
    read(n); read(m);
    for(int i = 1; i <= n; ++i) read(a[i]);

    build(1, 1, n);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;

    while(m--) {
        read(l); read(r);
        int sum = ask_sum(1, 1, n, l, r);

        sum = 1LL * sum * inv[r - l + 1] % MOD;
        modify(1, 1, n, l, r, sum);
    }

    print(1, 1, n); printf("\n");
    return 0;
}