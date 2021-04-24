#include<iostream>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int map[21][21];
bool visited[21][21];
int di[] = {0,0,-1,1};
int dj[] = {-1,1,0,0};

int N, M, C;
struct Pos{
    bool visited;
    int startI, startJ;
    int endI, endJ;
};

bool isBounded(int i, int j, int n){
    if(0<= i && i < N && 0 <= j && j < N) return true;
    return false;
}

int getCost(int startI, int startJ, int endI, int endJ, int limitCost){
    if(startI == endI && startJ == endJ) return 0;
    memset(visited, 0, sizeof(visited));
    queue< pair<int, int >> q;
    q.push({startI, startJ});
    int cnt = 0;
    visited[startI][startJ] = true;
    while(!q.empty()){
        int size = q.size();
        if(cnt > limitCost) break;
        for(int s=0;s<size;s++){
            auto curPos = q.front();
            q.pop();
            if(curPos.first == endI && curPos.second == endJ){
                return cnt;
            }
            for(int d=0;d<4;d++){
                int nextI = curPos.first + di[d];
                int nextJ = curPos.second + dj[d];
                if(isBounded(nextI, nextJ, N) && !visited[nextI][nextJ] && map[nextI][nextJ] != -1){
                    visited[nextI][nextJ] = true;
                    q.push({nextI, nextJ});
                }
            }
        }
        cnt++;
    }
    return -1;
}

int getTargetObject(int startI, int startJ, int limitCost, vector<Pos> &posList){
    memset(visited, 0, sizeof(visited));
    queue< pair<int, int >> q;
    q.push({startI, startJ});
    int cnt = 0;
    visited[startI][startJ] = true;
    bool isAns = false;
    int ret = -1;
    int maxI = N+1;
    int maxJ = N+1;
    while(!q.empty()){
        int size = q.size();
        if(cnt >= limitCost) break;
        for(int s=0;s<size;s++){
            auto curPos = q.front();
            q.pop();
            int mapIdx = map[curPos.first][curPos.second];
            if( !posList[mapIdx].visited && mapIdx > 0 ){
                isAns = true;
                if(curPos.first < maxI){
                    maxI = curPos.first;
                    maxJ = curPos.second;
                    ret = mapIdx;
                }
                else if(curPos.first == maxI && curPos.second < maxJ){
                    maxJ = curPos.second;
                    ret = mapIdx;
                }
            }
            for(int d=0;d<4;d++){
                int nextI = curPos.first + di[d];
                int nextJ = curPos.second + dj[d];
                if(isBounded(nextI, nextJ, N) && !visited[nextI][nextJ] && map[nextI][nextJ] != -1){
                    visited[nextI][nextJ] = true;
                    q.push({nextI, nextJ});
                }
            }
        }
        if(isAns) break;
        cnt++;
    }
    if(!isAns) return -1;
    return ret;

}
int main(){

    cin >> N >> M >> C;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> map[i][j];
            if(map[i][j] == 1) map[i][j] = -1;
        }
    }
    int curI, curJ;
    cin >> curI >> curJ;
    curI--; curJ--;
    vector<Pos> targetList(M+1);
    for(int i=1;i<=M;i++){
        int startI, startJ, endI, endJ;
        cin >> startI >> startJ >> endI >> endJ;
        startI--;startJ--;endI--;endJ--;
        map[startI][startJ] = i;
        targetList[i].visited = false;
        targetList[i].startI = startI;
        targetList[i].startJ = startJ;
        targetList[i].endI = endI;
        targetList[i].endJ = endJ;
    }

    for(int m=0;m<M;m++){
        int targetIdx = getTargetObject(curI, curJ, C, targetList);
        if(targetIdx == -1){
            C = -1;
            break;
        }
        targetList[targetIdx].visited = true;
        auto curTarget = targetList[targetIdx];
        int startCost = getCost(curI, curJ, curTarget.startI, curTarget.startJ, C);
        if(startCost == -1 || C <= startCost){
            C = -1;
            break;
        }
        C -= startCost;
        int endCost = getCost(curTarget.startI, curTarget.startJ, curTarget.endI, curTarget.endJ, C);
        if(endCost == -1 || C < endCost){
            C = -1;
            break;
        }
        curI = curTarget.endI;
        curJ = curTarget.endJ;
        C += endCost;
    }
    cout << C << endl;
    return 0;
}