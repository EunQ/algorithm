#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

int N, Q;
int mapSize = 1;
int mem[64][64];
int minusMap[64][64];
bool visited[64][64];
int L;
int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};


bool isBound(int i, int j){
    if(0<=i && i < mapSize && 0<=j && j < mapSize) return true;
    return false;
}

int bfs(int i, int j){
    visited[i][j] = true;
    queue<pair<int, int>> q;
    q.push({i, j});
    int ret = 1;
    while(!q.empty()){
        int size = q.size();
        for(int s=0;s<size;s++){
            auto curPos = q.front(); q.pop();
            for(int d=0;d<4;d++){
                int nextI = curPos.first + di[d];
                int nextJ = curPos.second + dj[d];
                if(isBound(nextI, nextJ) && !visited[nextI][nextJ] && mem[nextI][nextJ] > 0){
                    visited[nextI][nextJ] = true;
                    ret++;
                    q.push({nextI, nextJ});
                }
            }
        }
    }
    return ret;
}

void rodateMap(int curI, int curJ, int l){
    if(l == 0) return;
    int copyMap[64][64];
    memcpy(copyMap, mem, sizeof(mem) );
    //update;
    int moveLen = l;
    
    int endJ = curJ + moveLen - 1;
    int endI = curI + moveLen - 1;

    for(int len = 0;len<moveLen-1;len++){
        for(int j= curJ ; j<=curJ + moveLen-2 ; j++){
            copyMap[curI][j+1] = mem[curI][j];
        }

        for(int i = curI;i <= curI + moveLen - 2; i++){
            copyMap[i+1][endJ] = mem[i][endJ];
        }

        for(int j=curJ ; j<=curJ + moveLen-2;j++){
            copyMap[endI][j] = mem[endI][j+1];
        }

        for(int i = curI;i <= curI + moveLen - 2; i++){
            copyMap[i][curJ] = mem[i+1][curJ];
        }
        
        memcpy(mem, copyMap, sizeof(mem) );

    }

    rodateMap(curI+1, curJ+1, l-2);
}
int main(){

    cin >> N >> Q;
    for(int i=0;i<N;i++){
        mapSize *= 2;
    }

    for(int i=0;i < mapSize; i++){
        for(int j=0;j<mapSize;j++){
            int tmp ;
            cin >> tmp;
            mem[i][j] = tmp;
        }
    }

    for(int q=0;q<Q;q++){
        cin >> L;

        int k = 1;
        int tmpN = 1;
        for(int i=0;i<N-L;i++){
            tmpN *= 2;
        }

        if(L != 0){
            for(int i=0;i<tmpN;i++){
                for(int j=0;j<tmpN;j++){
                    rodateMap(i * mapSize/tmpN, j * mapSize/tmpN, mapSize/tmpN);
                }
            }
        }

        
        for(int i=0;i<mapSize;i++){
            for(int j=0;j<mapSize;j++){
                int cnt = 0;
                if(mem[i][j] == 0) continue;
                for(int d=0;d<4;d++){
                    int nextI = i + di[d];
                    int nextJ = j + dj[d];
                    if(isBound(nextI, nextJ) && mem[nextI][nextJ] > 0){
                        cnt++;
                    }
                }
                if(cnt < 3){
                    minusMap[i][j] = 1;
                }
            }
        }

        for(int i=0;i<mapSize;i++){
            for(int j=0;j<mapSize;j++){
                if(minusMap[i][j] == 1){
                    minusMap[i][j] = 0;
                    mem[i][j]--;
                }
            }
        }
        
        
        
    }
    int ansCnt = 0;
    int ansSum = 0;
    for(int i=0;i<mapSize;i++){
        for(int j=0;j<mapSize;j++){
            if(mem[i][j] == 0) continue;
            ansSum += mem[i][j];
            if(!visited[i][j]){
                int tmpCnt = bfs(i, j);
                ansCnt = tmpCnt > ansCnt ? tmpCnt : ansCnt;
            }
        }
    }

    cout << ansSum << endl;
    cout << ansCnt << endl;
    
    return 0;
}