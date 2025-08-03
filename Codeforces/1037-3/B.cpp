#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

int T, n, k;
int weather_now;

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
        int ans = 0;
        int sum_weather = 0;
        for(int i = 0; i < n; ++i) {
            read(weather_now);
            if(weather_now) sum_weather = 0;
            else {
                sum_weather++;
                if(sum_weather == k) {
                    sum_weather = -1;
                    ans++;
                }
            }
        }        
        printf("%d\n", ans);
    }
    return 0;
}