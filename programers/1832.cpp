#include <vector>

using namespace std;

int MOD = 20170805;


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    
    vector<vector<int>> mem_h(m+1, vector<int>(n+1, 0));
    vector<vector<int>> mem_v(m+1, vector<int>(n+1, 0));

    mem_v[1][1] = mem_h[1][1] = 1;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(city_map[i-1][j-1] == 0){
                mem_v[i][j] += mem_v[i-1][j] + mem_h[i][j-1];
                mem_v[i][j] %= MOD;
                mem_h[i][j] += mem_v[i-1][j] + mem_h[i][j-1];
                mem_h[i][j] %= MOD;
            }
            else if(city_map[i-1][j-1] == 2){
                mem_v[i][j] = mem_v[i-1][j];
                mem_h[i][j] = mem_h[i][j-1];
            }
            else{
                mem_v[i][j] = mem_h[i][j] = 0;
            }
        }
    }
    answer = mem_h[m][n];
    return answer;
}
