#include <string>
#include <vector>

using namespace std;

int di[] = {0,0,1,-1,1,1,-1,-1};
int dj[] = {1,-1,0,0,1,-1,1,-1};

bool isBound(int n, int i, int j){
    if(0<=i && i<n && 0<=j && j<n) return true;
    return false;
}

bool isCorrect(int n, int i, int j, vector<vector<int>> &map){
    for(int d=0;d<8;d++){
        for(int c=1;c<=n;c++){
            int nextI = i + c*di[d];
            int nextJ = j + c*dj[d];
            if(isBound(n, nextI, nextJ)){
                if(map[nextI][nextJ] == 1) return false;
            } 
        }
    }
    return true;
}

int dfs(int n, int rowCnt, vector<vector<int>>& map){
    if(rowCnt == n){
        return 1;
    }
    int res = 0;
    for(int j=0;j<n;j++){
        if(isCorrect(n, rowCnt, j, map)){
            map[rowCnt][j] = 1;
            res +=  dfs(n, rowCnt+1, map);
            map[rowCnt][j] = 0;
        }
    }
    return res;
}

int solution(int n) {
    int answer = 0;
    vector<vector<int>> map(n, vector<int>(n));

    answer = dfs(n, 0, map);

    return answer;
}