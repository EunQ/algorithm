#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int R,C,T;
int curMap[50][50];
int nextMap[50][50];
int di[4] = {0,0,-1,1};
int dj[4] = {-1,1,0,0};

bool isBound(int i, int j){
    if(0<= i && i < R && 0<= j && j <C ) return true;
    return false;
}

int main(){
    cin >> R >> C >> T;
    vector<pair<int, int>> cleaner;    
    queue<pair<int, int>> q;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            int tmp;
            cin >> tmp;
            curMap[i][j] = tmp;
            if(tmp == -1){
                cleaner.push_back({i, j});
                //0은 위에 있는것,
                //1은 아래에 있는것.
            }
        }
    }

    for(int t=0;t<T;t++){
        memset(nextMap, 0, sizeof(nextMap));
        for(auto curPos : cleaner){
            nextMap[curPos.first][curPos.second] = -1;
        }
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                if(curMap[i][j] == 0 || curMap[i][j] == -1) continue;
                pair<int, int> curPos = {i, j};
                int cnt = 0;
                for(int d=0;d<4;d++){
                    int nextI = curPos.first + di[d];
                    int nextJ = curPos.second + dj[d];
                    if(isBound(nextI, nextJ) && curMap[nextI][nextJ] != -1){
                        nextMap[nextI][nextJ] += (curMap[curPos.first][curPos.second]) / 5;
                        cnt++;
                    }
                }
                int curDust = curMap[curPos.first][curPos.second];
                nextMap[curPos.first][curPos.second] += curDust - (curDust / 5) * cnt;
                
            }
        }

        int upI = cleaner[0].first;
        int upJ = cleaner[0].second;

        nextMap[upI-1][upJ] = 0;
        for(int i=upI-2;i>=0;i--){
            nextMap[i+1][0] = nextMap[i][0]; 
        }
        for(int j=1;j<C;j++){
            nextMap[0][j-1] = nextMap[0][j];
        }
        for(int i=1;i<=upI;i++){
            nextMap[i-1][C-1] = nextMap[i][C-1];
        }
        for(int j=C-2;j>=1;j--){
            nextMap[upI][j+1] = nextMap[upI][j];
        }
        nextMap[upI][1] = 0;

        int downI = cleaner[1].first;
        int downK = cleaner[1].second;

        nextMap[downI+1][0] = 0;
        for(int i=downI+2;i < R;i++){
            nextMap[i-1][0] = nextMap[i][0];
        }
        for(int j=1;j<C;j++){
            nextMap[R-1][j-1] = nextMap[R-1][j];
        }
        for(int i=R-2;i>=downI;i--){
            nextMap[i+1][C-1] = nextMap[i][C-1];
        }
        for(int j=C-2;j>=1;j--){
            nextMap[downI][j+1] = nextMap[downI][j];
        }
        nextMap[downI][1] = 0;

        //copy map;
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                curMap[i][j] = nextMap[i][j];
            }
        }
    }

    int ans = 0;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(curMap[i][j] == -1) continue;
            ans += curMap[i][j];
        }
    }

    cout << ans << endl;

    return 0;
}