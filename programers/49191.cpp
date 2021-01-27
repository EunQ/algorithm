#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

struct node{
    vector<int> nextList;
    int preCnt;
    bool operator< (node other) const{
        return preCnt > other.preCnt;
    }
};

#define LIMIT_MAX 987654321

int solution(int n, vector<vector<int>> results){
    int answer = 0;
    int size = results.size();
    vector<vector<int>> adj(n+1, vector<int>(n+1, LIMIT_MAX));
    for(int i=0;i<size;i++){
        int A = results[i][0];
        int B = results[i][1];
        adj[A][B] = 1;
        adj[B][A] = -1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(adj[i][j] == LIMIT_MAX){
                    if(adj[i][k] == adj[k][j] && adj[j][k] != LIMIT_MAX){
                        adj[i][j] = adj[k][j];
                    }
                    
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        bool hasMax = false;
        for(int j=1;j<=n;j++){
            if(i != j && adj[i][j] == LIMIT_MAX){
                hasMax = true;
                break;
            }
        }
        if(!hasMax) answer++;
    }
    return answer;
}

int main(){
    int a = 10;
    //정확하게 순위를 매길 수 있는 선수의 수. 리턴.
    //1명이상 100명 이하.
    //경기수 1개 이상, 4,500개 이하.
    //result의미 [A,B] A선수가 B를 이겼다.
    
    
    //cout << solution(100, { {4,3} }) << endl;;
    cout << solution(5, { {4,3}, {4,2}, {3,2}, {1,2}, {2,5}}) << endl;
    return 0;
}