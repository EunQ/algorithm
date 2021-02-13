#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define INIT 9999

int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    int answer = 0;
    vector<vector<int>> dp (k+1, vector<int>(n+1, INIT));
    vector<vector<int>> map(n+1);
    dp[0][gps_log[0]] = 0;
    
    for(int i=1;i<=n;i++){
        map[i].push_back(i);
    }
    
    for(auto edge : edge_list){
        int a = edge[0];
        int b = edge[1];
        map[a].push_back(b);
        map[b].push_back(a);
    }

    for(int i=1;i<k;i++){
        for(int j=1;j<=n;j++){
            for(int next : map[j]){
                int tmp = gps_log[i] == next ? 0 : 1;
                dp[i][next] = min(dp[i][next], dp[i-1][j] + tmp) ;
            }
        }
    }
    answer = dp[k-1][gps_log[gps_log.size()-1]];
    if (answer >= INIT) answer = -1;
    return answer;
}