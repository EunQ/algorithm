#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};
int N, L, R;
int visited[50][50];
int mem[50][50];
bool isBound(int i, int j){
    if(0<=i && i < N && 0<= j && j < N) return true;
    return false;
}
int diff(int a, int b){
    if (b > a) return b - a;
    return a - b;
}

bool bfs(int i, int j){
    if(visited[i][j]) return false;
    queue<pair<int, int>> q;
    vector<pair<int, int>> unionList;
    q.push({i, j});
    visited[i][j] = true;
    unionList.push_back({i, j});
    int sum = mem[i][j];
    int cnt = 1;
    while(!q.empty()){
        int size = q.size();
        for(int s = 0;s<size;s++){
            auto curPos = q.front();
            q.pop();
            int curI = curPos.first;
            int curJ = curPos.second;
            for(int d=0;d<4;d++){
                int nextI = curI + di[d];
                int nextJ = curJ + dj[d];
                if(isBound(nextI, nextJ) && !visited[nextI][nextJ]){
                    int nextVal = mem[nextI][nextJ];
                    int curVal = mem[curI][curJ];
                    int diffVal = diff(curVal, nextVal);
                    if(L <= diffVal && diffVal <= R){
                        visited[nextI][nextJ] = true;
                        cnt++;
                        q.push({nextI, nextJ});
                        unionList.push_back({nextI, nextJ});
                        sum += nextVal;
                    }
                }
            }
        }
    }
    if(unionList.size() == 1) return false;
    int avg = sum / cnt;
    for(auto curPos : unionList){
        mem[curPos.first][curPos.second] = avg;
    }

    return true;
}
int main(){
    int ans = 0;
    cin >> N >> L >> R;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> mem[i][j];
        }
    }

    while(true){
        int cnt = 0;
        memset(visited, 0, sizeof(visited));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                int isMoved = bfs(i, j);
                if(isMoved) cnt++;
            }
        }
        if(cnt == 0) break;
        ans++;
    }

    cout << ans << endl;
    return 0;
}