#include<iostream>
#include<vector>

using namespace std;

int N,K;

int di[] = {0,0,-1,1};
int dj[] = {1,-1,0,0};

struct Pawn{
    int curI,curJ;
    int curDir;
    int upIdx;
    int downIdx;
    //if Up == -1 is null;
};

int changeDir(int dir){
    if(dir == 0) return 1;
    if(dir == 1) return 0;
    if(dir == 2) return 3;
    return 2;
}

int getTop(vector<Pawn> &pawns, int idx){
    if(pawns[idx].upIdx == -1) return idx;
    return getTop(pawns, pawns[idx].upIdx);
}

int updateRedZone(vector<Pawn> &pawns, int idx, int preIdx){
    // 1, 3, 2 ==> 2, 3, 1
    int tmpUpIdx = pawns[idx].upIdx;
    int bottom = idx;
    if(tmpUpIdx != -1){
        bottom = updateRedZone(pawns, tmpUpIdx, idx);
    }
    pawns[idx].upIdx = preIdx; 
    return bottom;
}

int main(){
    cin >> N >> K;
    vector<vector<pair<int, int>>> playMap(N, vector<pair<int, int>>(N));
    
    vector<Pawn> pawns(K);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int tmp;
            cin >> tmp;
            playMap[i][j].first = tmp;
            playMap[i][j].second = -1;
        }
    }

    for(int i=0;i<K;i++){
        int a,b,c;
        cin >> a >> b >> c;
        pawns[i].curI = a-1;
        pawns[i].curJ = b-1;
        pawns[i].curDir = c-1;
        pawns[i].upIdx = -1;
        pawns[i].isActive = true;
        playMap[a-1][b-1].second = i;
    }

    int turnCnt = 0;
    int del = 0;
    while(true){
        turnCnt++;
        
        for(int idx=0;idx<N;idx++){
            Pawn curPawn = pawns[idx];
            if(!pawns[idx].isActive) continue;
            int nextI = curPawn.curI + di[curPawn.curDir];
            int nextJ = curPawn.curJ + dj[curPawn.curDir];

            if (!(0<= nextI && nextI < N && 0<=nextJ && nextJ <N ) || playMap[nextI][nextJ].first == 2){
                pawns[idx].curDir = changeDir(curPawn.curDir);
                curPawn = pawns[idx];
                nextI = curPawn.curI + di[curPawn.curDir];
                nextJ = curPawn.curJ + dj[curPawn.curDir];
            }        

            if(!( 0<= nextI && nextI < N && 0<=nextJ && nextJ <N) || 
                playMap[nextI][nextJ].first == 2 ){
                pawns[idx].curDir = changeDir(curPawn.curDir);
            }
            else{ 
                int bottom = idx;
                int top = getTop(pawns, idx);
                if(playMap[nextI][nextJ].first == 1){
                    //빨강색
                    bottom = updateRedZone(pawns, idx, -1);
                }
                
                if(playMap[nextI][nextJ].second != -1){
                    pawns[playMap[nextI][nextJ].second].upIdx = bottom;
                    pawns[idx].isActive = false;
                    del++;
                }
                else{
                    pawns[bottom].curI = nextI;
                    pawns[bottom].curJ = nextJ;
                }
                playMap[curPawn.curI][curPawn.curJ].second = -1;
                playMap[nextI][nextJ].second = idx;
                
            }
        }

        if(del == 3){
            break;
        }

        if(turnCnt >= 1000) {
            turnCnt = -1;
            break;
        }
    }

    cout << turnCnt << endl;

    return 0;
}


