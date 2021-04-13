#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int dj[] = {1,0,-1,0};
int di[] = {0,1,0,-1};
int N,M;
int map[8][8];
int cntMap[8][8];
int ans = 0;
bool isValid(int i, int j){
    if(0<= i && i < N){
        if(0<=j && j < M){
            return true;
        }
    }
    return false;
}
void dfs(vector<pair<int, int>> &pos, int idx, int maxIdx){
    if(idx == maxIdx){
        int cnt = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(map[i][j] == 0 &&cntMap[i][j] == 0){
                    cnt++;
                }
            }
        }
        ans = min(cnt, ans);
        return ;
    }

    int curI = pos[idx].first;
    int curJ = pos[idx].second;
    int add = 0;
    for(int d=0;d<4;d++){
        if(map[curI][curJ] == 1){   
            for(int c=1;c<8;c++){
                int nextI = curI + c * di[d];
                int nextJ = curJ + c * dj[d];
                if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                //조건문 다시 보기.
                if(map[nextI][nextJ] == 0){
                    cntMap[nextI][nextJ]++;
                }
            }
        }
        else if(map[curI][curJ] == 2){
            for(int td=0;td<3;td+=2){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(map[nextI][nextJ] == 0){
                        cntMap[nextI][nextJ]++;
                    }
                }
            }
        }
        else if(map[curI][curJ] == 3){
            for(int td=0;td<2;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(map[nextI][nextJ] == 0){
                        cntMap[nextI][nextJ]++;
                    }
                }
            }
        }
        else if(map[curI][curJ] == 4){
            for(int td=0;td<3;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(map[nextI][nextJ] == 0){
                        cntMap[nextI][nextJ]++;
                    }
                }
            }
        }
        else {
            for(int td=0;td<4;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(map[nextI][nextJ] == 0){
                        cntMap[nextI][nextJ]++;
                    }
                }
            }
        }
        dfs(pos, idx+1, maxIdx);
        if(map[curI][curJ] == 1){   
            for(int c=1;c<8;c++){
                int nextI = curI + c * di[d];
                int nextJ = curJ + c * dj[d];
                if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                if(cntMap[nextI][nextJ] != 0){
                    cntMap[nextI][nextJ]--;
                }
            }
        }
        else if(map[curI][curJ] == 2){
            for(int td=0;td<3;td+=2){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(cntMap[nextI][nextJ] != 0){
                        cntMap[nextI][nextJ]--;
                    }
                }
            }
        }
        else if(map[curI][curJ] == 3){
            for(int td=0;td<2;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(cntMap[nextI][nextJ] != 0){
                        cntMap[nextI][nextJ]--;
                    }
                }
            }
        }
        else if(map[curI][curJ] == 4){
            for(int td=0;td<3;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(cntMap[nextI][nextJ] != 0){
                        cntMap[nextI][nextJ]--;
                    }
                }
            }
        }
        else{
            for(int td=0;td<4;td++){
                int curD = (d + td) % 4;
                for(int c=1;c<8;c++){
                    int nextI = curI + c * di[curD];
                    int nextJ = curJ + c * dj[curD];
                    if(!isValid(nextI, nextJ) || map[nextI][nextJ] == 6) break;
                    if(cntMap[nextI][nextJ] != 0){
                        cntMap[nextI][nextJ]--;
                    }
                }
            }
        }
    }
}
int main(){
    
    cin >> N >> M;
    vector<pair<int, int>> pos;
    ans = N*M;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int tmp ;
            cin >> tmp;
            map[i][j] = tmp;
            if(tmp >= 1 && tmp < 6){
                pos.push_back({i, j});
            }
        }
    }
    dfs(pos, 0, pos.size());
    cout << ans << endl;
    return 0;
}