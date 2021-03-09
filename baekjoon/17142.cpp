#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <cstring>
using namespace std;

//연구소3

vector<pair<int, int>> virusPos;
vector<bool> visited;
int oriLabMap[50][50];
int labMap[50][50];
int N;
int M;
int di[4] = {0,0,-1,1};
int dj[4] = {-1,1,0,0};
#define MAX_ANS 2500
int answer = MAX_ANS;
bool isVaild(int i, int j){
    if( 0<=i && i < N ){
        if(0<=j && j < N) return true;
    }
    return false;
}
bool isFullfillMap(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(labMap[i][j] == 0)
                return false;
        }
    }
    return true;
}
void bfs(){
    int tmpAns = 0;
    memcpy(labMap, oriLabMap, sizeof(oriLabMap));
    int blankCnt = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(labMap[i][j] == 0) blankCnt++;
        }
    }
    //활성화 바이러스를 3라고 표시한다.
    queue<pair<int, int>> q;
    for(int i=0;i<virusPos.size();i++){
        if(visited[i]){
            q.push(virusPos[i]);
            labMap[virusPos[i].first][virusPos[i].second] = 3;
        }
    }

    int tmpBlankCnt = 0;
    while(!q.empty()){
        int size = q.size();
        int nextCnt = 0;
        for(int i=0;i<size;i++){
            auto curPos = q.front();
            q.pop();
            for(int d=0;d<4;d++){
                int nextI = curPos.first + di[d];
                int nextJ = curPos.second + dj[d];
                if(isVaild(nextI, nextJ) &&
                 labMap[nextI][nextJ] != 1 && labMap[nextI][nextJ] != 3){
                    q.push({nextI, nextJ});
                    if(labMap[nextI][nextJ] == 0){
                        tmpBlankCnt++;
                        nextCnt = 1;
                    }
                    labMap[nextI][nextJ] = 3;
                }
            }
        }

        if(tmpBlankCnt == blankCnt) {
            tmpAns += nextCnt;
            break;
        }
        tmpAns++;
    }
    
    if(isFullfillMap()){
        answer = min(answer, tmpAns);

    }
}
void pickUp(int idx, int size){
    if(size == M){
        bfs();
        return ;
    }
    for(int i=idx;i<virusPos.size();i++){
        visited[i] = true;
        pickUp(i+1, size+1);
        visited[i] = false;
    }
}

int main(){
    cin >> N >> M;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> oriLabMap[i][j];
            if(oriLabMap[i][j] == 2){
                virusPos.push_back({i,j});
            }
        }
    }
    visited = vector<bool>(virusPos.size());
    pickUp(0,0);
    if(answer == MAX_ANS) answer = -1;
    cout << answer << endl;
    return 0;
}
