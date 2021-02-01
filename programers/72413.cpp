#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int LIMIT = 200*100001;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = LIMIT * 2;
    // s는 start, a,b,는 각각의 도착점
    // n는 지점 개수.
    vector<vector<int>> mem(n+1, vector<int> (n+1, LIMIT));
    for(auto tmp : fares){
        int c = tmp[0];
        int d = tmp[1];
        int f = tmp[2];
        mem[c][d] = mem[d][c] = f;
    }
    for(int i=1;i<=n;i++){
        mem[i][i] = 0;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mem[i][j] > mem[i][k] + mem[k][j])
                    mem[i][j] = mem[i][k] + mem[k][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
        answer = min(answer, mem[s][i] + mem[i][a] + mem[i][b]);
    }
    return answer;
}