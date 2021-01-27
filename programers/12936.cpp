#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, long long k) {
    vector<int> answer;
    vector<int> len(n);
    len[0] = 1;
    vector<int> visited(n+1);
    for(int i=1;i<n;i++){
        len[i] = i * len[i-1];
    }
    k--;
    for(int i=n;i>=1;i--){
        int cal = len[i-1];
        int div = k  / cal ;
        k = k%cal;
        int next = 0;
        for(int j=1;j<=n;j++){
            if(visited[j]) continue;
            if(next == div){
                visited[j] = i;
                answer.push_back(j);
                break;
            }
            next++;
        }
    }
    if(k == 1){
        for(int j=n;j>=1;j--){
            if(visited[j]) continue;
            visited[j] = 1;
            answer.push_back(j);
        }
    }
    else{
        for(int j=1;j<=n;j++){
                if(visited[j]) continue;
                    visited[j] = 1;
                    answer.push_back(j);
            }
    }
    return answer;
}

using namespace std;
#include<iostream>
int main(){
    
    auto a = solution(6, 1);
}