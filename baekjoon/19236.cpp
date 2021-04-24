#include<iostream>
#include<cstring>
#include <vector>
#include <algorithm>

//실패, 다시 풀기.

using namespace std;

int mem[17][4][4];
struct Fish{
    bool alive;
    int curI, curJ, curD;
};
int di[] = {-1,-1,0,1,1,1,0,-1};
int dj[] = {0,-1,-1,-1,0,1,1,1};
Fish fishMem[17][17];
bool isBound(int i, int j){
    if(0<=i && i < 4 && 0<= j && j < 4) return true;
    return false;
}
void updateFish(int sI, int sJ, vector<Fish> &fishList, vector<vector<int>>& curMap){
    for(int idx = 1;idx<=16;idx++){
        Fish& fish = fishList[idx];
        int next = 0;
        if(fish.alive){
            next = 1;
            int nextI = 0;
            int nextJ = 0;
            int curD = 0;
            for(int d=fish.curD;d<fish.curD+8;d++){
                int idx = curMap[fish.curI][fish.curJ];
                curD = d%8;
                nextI = fish.curI + di[curD];
                //여기서 에러가 발생, curD로 해야되는데 d로 했음.
                nextJ = fish.curJ + dj[curD];
                if(isBound(nextI, nextJ) && !(sI == nextI && sJ == nextJ)){
                    if(curMap[nextI][nextJ] == 0){
                        curMap[fish.curI][fish.curJ] = 0;
                        curMap[nextI][nextJ] = idx;
                    }
                    else if(curMap[nextI][nextJ] < 0){
                        cout << endl;
                    }
                    else{
                        int otherIdx = curMap[nextI][nextJ];
                        curMap[nextI][nextJ] = idx;
                        curMap[fish.curI][fish.curJ] = otherIdx;
                        fishList[otherIdx].curI = fish.curI;
                        fishList[otherIdx].curJ = fish.curJ;
                    }

                    fish.curI = nextI;
                    fish.curJ = nextJ;
                    fish.curD = curD;
                    next += -1;
                    break;
                }
            }

        }
    }
}
int ans;
void dfs(int sI, int sJ, int sD, vector<Fish> &FishList, vector<vector<int>> &curMap, int calIdx){
    
    ans = max(ans, calIdx);
    vector<vector<int>> afterMap(4, vector<int>(4));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) afterMap[i][j] = curMap[i][j];
    }
    vector<Fish> afterFishList(17);
    for(int idx=1;idx<=16;idx++){
        afterFishList[idx] = FishList[idx];
    }

    updateFish(sI, sJ, afterFishList, afterMap);

    for(int len=1;len<4;len++){
        int nextI = sI + di[sD] * len;
        int nextJ = sJ + dj[sD] * len;
        if(isBound(nextI, nextJ) && afterMap[nextI][nextJ] >= 1){
            //cout << afterMap[nextI][nextJ] << endl;
            int fishIdx = afterMap[nextI][nextJ];
            afterMap[nextI][nextJ] = -1;
            afterMap[sI][sJ] = 0;
            afterFishList[fishIdx].alive = false;
            dfs(nextI, nextJ, afterFishList[fishIdx].curD, afterFishList, afterMap, calIdx + fishIdx);
            afterFishList[fishIdx].alive = true;
            afterMap[nextI][nextJ] = fishIdx;
            afterMap[sI][sJ] = -1;
        }
    }

}
int main(){
    vector<vector<int>> curMap(4, vector<int>(4));
    vector<Fish> curFishList(17);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            int idx;
            int d;
            cin >> idx;
            cin >> d;
            d--;
            curMap[i][j] = idx;
            curFishList[idx] = {true, i, j, d};
        }
    }

    int firstFishIdx = curMap[0][0];
    curMap[0][0] = -1;
    curFishList[firstFishIdx].alive = false;

    dfs(0, 0, curFishList[firstFishIdx].curD, curFishList, curMap,firstFishIdx );

    cout << ans <<endl;

    return 0;
}

/*
void updateFish(int cnt, int ans){
    if(ans == 22){
        cout << endl;
    }
    for(int idx=1;idx<=16;idx++){
        if(fishMem[cnt][idx].alive){
            for(int curD=fishMem[cnt][idx].curD; curD<fishMem[cnt][idx].curD+8;curD++){
                int d = curD%8;
                int nextI = fishMem[cnt][idx].curI + di[d];
                int nextJ = fishMem[cnt][idx].curJ + dj[d];
                if(isBound(nextI, nextJ) && mem[cnt][nextI][nextJ] != -1){
                    if(mem[cnt][nextI][nextJ] == 0){
                        fishMem[cnt][idx].curI = nextI;
                        fishMem[cnt][idx].curJ = nextJ;

                        mem[cnt][nextI][nextJ] = idx;
                        mem[cnt][fishMem[cnt][idx].curI][fishMem[cnt][idx].curJ] = 0;
                    }
                    else{
                        int otherIdx = mem[cnt][nextI][nextJ];
                        fishMem[cnt][otherIdx].curI = fishMem[cnt][idx].curI ;
                        fishMem[cnt][otherIdx].curJ = fishMem[cnt][idx].curJ ;
                        mem[cnt][fishMem[cnt][idx].curI][fishMem[cnt][idx].curJ] = otherIdx;

                        mem[cnt][nextI][nextJ] = idx;
                        fishMem[cnt][idx].curI = nextI;
                        fishMem[cnt][idx].curJ = nextJ;
                    }
                    fishMem[cnt][idx].curD = d;
                    break;
                }
            }
        }
    }
    return;
}
int ret = 0;
void dfs(int sharkI, int sharkJ, int sharkD, int cnt, int ans){
    updateFish(cnt, ans);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            mem[cnt+1][i][j] = mem[cnt][i][j];
        }
    }
    for(int i=1;i<=16;i++)
        fishMem[cnt+1][i] = fishMem[cnt][i];

    int len = 0;
    for(len = 1;len<4;len++){
        int nextI = sharkI + di[sharkD] * len; 
        int nextJ = sharkJ + dj[sharkD] * len;
        if(isBound(nextI, nextJ) && mem[cnt][nextI][nextJ] >= 1){
            int idx = mem[cnt][nextI][nextJ];
            mem[cnt+1][sharkI][sharkJ] = 0;
            mem[cnt+1][nextI][nextJ] = -1;
            fishMem[cnt+1][idx].alive = false;
            dfs(nextI, nextJ, fishMem[cnt][idx].curD, cnt+1, ans + idx);
            fishMem[cnt+1][idx].alive = true;
            mem[cnt+1][nextI][nextJ] = idx;
            mem[cnt+1][sharkI][sharkJ] = -1;
        }
        else{
            break;
        }
        
    }
    ret = max(ans, ret);
    return;
}

*/