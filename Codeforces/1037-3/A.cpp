#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

int T, n;

char read(){
    char ans = '9';
    char ch = getchar();
    while(ch < '!')  ch = getchar();
    while(ch >= '0' && ch <= '9') {
        ans = min(ans, ch);
        ch = getchar();
    }
    return ans;
}



int main() {
    scanf("%d", &T);
    while(T--) putchar(read()), putchar('\n');
    return 0;
}