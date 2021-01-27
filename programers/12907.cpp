#include<iostream>
/* 최고의 집합 */

#include<string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> money) {
    int answer = 0;
    sort(money.begin(), money.end());
    vector<int> mem (n+1, 0);

    for(int i=0;i<=n;i += money[0])
        mem[i] = 1;
    
    for(int i = 1 ; i< money.size(); i++){
        for(int j=money[i];j<=n;j++){
            mem[j] += mem[j - money[i]];
        }
    }
        
    answer = mem[n];
    return answer;
}
int main(){

    auto a = solution(5, {1,2,5});

    return 0;
}