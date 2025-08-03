#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 22;
int n, a, b;
char s[MAXN];

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
    read(n); read(a); read(b);
    scanf("%s", s);
    for(int i = a; i < n - b; ++i) putchar(s[i]);
    printf("\n");
    return 0;
}