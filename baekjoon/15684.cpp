#include<iostream>
#include<vector>
#include <algorithm>
#include <queue>
using namespace std;
int buf[31][11];
int N,M,H;
int ans = 4;
int limit;
bool goDown(int start){
    int col = start;
    for(int r=1;r<=H;r++){
        if(buf[r][col]){
            col+=1;
        }
        else if( col >= 2 && buf[r][col-1]){
            col-=1;
        }
    }
    if(start == col) return true;
    return false;
}
bool isAns(){
    for(int col = 1;col <= N;col++){
        if(!goDown(col)){
            return false;
        }
    }
    return true;
}
void dfs(int cnt, int idx){
    if(cnt >= ans) return;
    if(isAns()){
        ans = min(ans, cnt);
    }
    if(idx >= limit) return;
    for(int nextIdx = idx;nextIdx <= limit;nextIdx++){
        int curRow = (nextIdx - 1) / N + 1;
        int curCol = (nextIdx - 1) % N + 1;
        if(buf[curRow][curCol] == 0){
            if(curCol >= 2 && buf[curRow][curCol - 1]) continue;
            if(curCol + 1 <= N && buf[curRow][curCol + 1]) continue;
            buf[curRow][curCol]++;
            dfs(cnt+1, nextIdx+2);
            buf[curRow][curCol]--;
        }
    }
    return;
}
int main(){
    
    cin >> N >> M >> H;
    for(int i=0;i<M;i++){
        int a,b;
        cin >> a >> b;
        buf[a][b] = 1;
    }
    limit = N * H;
    dfs(0, 1);
    if(ans >= 4) ans = -1;
    cout << ans << endl;
    
    return 0;
}