#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
int T, n;
int a[MAXN], ind[MAXN];
int al[MAXN], ar[MAXN];    
int Stack[MAXN], top;
int Seg_min[MAXN << 2], Seg_max[MAXN << 2];
int Seg_add[MAXN << 2];

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
        Seg_min[node] = Seg_max[node] = L;
        Seg_add[node] = 0;
        return;
    }
    int mid = (L + R) >> 1;
    build(node << 1, L, mid);
    build(node << 1 | 1, mid + 1, R);
    Seg_max[node] = max(Seg_max[node << 1], Seg_max[node << 1 | 1]);
    Seg_min[node] = min(Seg_min[node << 1], Seg_min[node << 1 | 1]);
    Seg_add[node] = 0;
}

void push_down(int node) {
    Seg_min[node << 1] += Seg_add[node];
    Seg_max[node << 1] += Seg_add[node];
    Seg_add[node << 1] += Seg_add[node];

    Seg_min[node << 1 | 1] += Seg_add[node];
    Seg_max[node << 1 | 1] += Seg_add[node];
    Seg_add[node << 1 | 1] += Seg_add[node];
    
    Seg_add[node] = 0;
}

void add(int node, int L, int R, int l, int r, int val) {
    if(l <= L && R <= r) {
        Seg_min[node] += val;
        Seg_max[node] += val;
        Seg_add[node] += val;
        return;
    }
    int mid = (L + R) >> 1;
    if(Seg_add[node]) push_down(node);
    if(l <= mid) add(node << 1, L, mid, l, r, val);
    if(r > mid) add(node << 1 | 1, mid + 1, R, l, r, val);
    Seg_max[node] = max(Seg_max[node << 1], Seg_max[node << 1 | 1]);
    Seg_min[node] = min(Seg_min[node << 1], Seg_min[node << 1 | 1]);
}

int ask_max(int node, int L, int R, int l, int r) {
    if(l > R || r < L) return -1e9;
    if(l <= L && R <= r) return Seg_max[node];
    int mid = (L + R) >> 1;
    if(Seg_add[node]) push_down(node);
    return max(ask_max(node << 1, L, mid, l, r), ask_max(node << 1 | 1, mid + 1, R, l, r));
}

int ask_min(int node, int L, int R, int l, int r) {
    if(l > R || r < L) return 1e9; 
    if(l <= L && R <= r) return Seg_min[node];
    int mid = (L + R) >> 1;
    if(Seg_add[node]) push_down(node);
    return min(ask_min(node << 1, L, mid, l, r), ask_min(node << 1 | 1, mid + 1, R, l, r));
}

void print_seg(int node, int L, int R) {
    if(L == R) {
        printf("%d ", Seg_min[node]);
        return;
    }
    int mid = (L + R) >> 1;
    print_seg(node << 1, L, mid);
    print_seg(node << 1 | 1, mid + 1, R);
}

int main() {
    read(T);
    while(T--) {
        read(n);
        for(int i = 1; i <= n; ++i) {
            ind[i] = i;
            read(a[i]);
        }

        top = 0;
        for(int i = 1; i <= n; ++i) {
            while(top && a[i] <= a[Stack[top]]) --top;
            if(top) al[i] = Stack[top];
            else al[i] = 0;
            Stack[++top] = i;
        }

        top = 0;
        for(int i = n; i >= 1; --i) {
            while(top && a[i] <= a[Stack[top]]) --top;
            if(top) ar[i] = Stack[top];
            else ar[i] = n + 1;
            Stack[++top] = i;
        }

        sort(ind + 1, ind + n + 1, [](int x, int y) { return a[x] < a[y]; });
        build(1, 1, n); 

        int ans = 0;
        int mid_pos = 1, r_max, l_min;
        for(int i = 1; i <= n; ++i) {
            int cur = ind[i];
            while(mid_pos <= n) {
                r_max = ask_max(1, 1, n, cur, ar[cur] - 1);
                l_min = min(0, ask_min(1, 1, n, al[cur], cur - 1));

                if(r_max - l_min >= 0) {
                    add(1, 1, n, ind[mid_pos], n, -2);
                    mid_pos++;
                }
                else break;
            }
            ans = max(ans, a[ind[mid_pos - 1]] - a[ind[i]]);
        }  
        printf("%d\n", ans);
    }
    return 0;
}