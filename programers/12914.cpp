#include<iostream>

#include <string>
#include <vector>

using namespace std;

long long solution(int n) {
    long long answer = 0;
    vector<long long> dist(n+1);
    int DIV = 1234567;
    dist[0] = 1;
    dist[1] = 1;
    for(int i=2;i<=n;i++){
        dist[i] = dist[i-1] + dist[i-2];
        dist[i] %= DIV;
    }
    answer = dist[n];
    return answer;
}