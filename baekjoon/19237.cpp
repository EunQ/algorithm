#include<vector>
#include<queue>
#include<iostream>

using namespace std;
//1시간 10분.
int N, M, k;

int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};
struct Shark{
    int id;
    int curI;
    int curJ;
    int curD;
    vector<int> dirOrder[4];
    bool alive;
};
int map[21][21];
int smellMap[21][21][2];

bool isBounded(int i, int j, int n){
    if(0<=i && i < n && 0<= j && j < n) return true;
    return false;
}

bool goProcess(int preI, int preJ ,int i, int j, int d, int idx, vector<Shark> &sharks){
    map[preI][preJ] = 0;
    if(map[i][j] != 0){
        if(map[i][j] < idx){
            sharks[idx].alive = false;
            return false;
        }
        sharks[map[i][j]].alive = false;
        map[i][j] = idx;
    }
    map[i][j] = idx;

    sharks[idx].curI = i;
    sharks[idx].curJ = j;
    sharks[idx].curD = d;
    return true;
}
int main(){

    cin >> N >> M >> k;
    //k는 냄새가 사라지는 시간.
    vector<Shark> sharks(M+1);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int tmp = 0;
            cin >> tmp;
            if(tmp > 0){
                sharks[tmp].id = tmp;
                sharks[tmp].curI = i;
                sharks[tmp].curJ = j;
                smellMap[i][j][0] = tmp;
                smellMap[i][j][1] = k;
                sharks[tmp].alive = true;
            }
            map[i][j] = tmp;
        }
    }
    for(int m=1;m<=M;m++){
        int tmp;
        cin >> tmp;
        sharks[m].curD = (tmp-1);
    }
    for(int m=1;m<=M;m++){
        for(int d=0;d<4;d++){
            for(int i = 0;i<4;i++){
                int tmp;
                cin >> tmp;
                sharks[m].dirOrder[d].push_back(tmp-1);
            }
        }
    }

    queue<Shark> q;
    for(auto shark : sharks){
        if(shark.alive){
            q.push(shark);
        }
    }
    int ans = 0;
    while(!q.empty()){
        if(ans > 1000){
            ans = -1;
            break;
        }
        if(q.size() == 1) break; 
        
        int size = q.size();

        for(int s = 0; s<size;s++){
            auto curShark = q.front();
            q.pop();
            if(!curShark.alive) continue;
            int curD = curShark.curD;
            bool isGo = false;
            for(auto nextD : curShark.dirOrder[curD]){
                int nextI = curShark.curI + di[nextD];
                int nextJ = curShark.curJ + dj[nextD];
                if(isBounded(nextI, nextJ, N) && smellMap[nextI][nextJ][1] == 0){
                    //냄새가 없는 곳을 우선으로.
                    isGo = true;
                    goProcess(curShark.curI, curShark.curJ, nextI, nextJ, nextD , curShark.id, sharks);
                    break;
                }
            }
            if(!isGo){
                //자신의 냄새로 이동해야 된다.
                for(auto nextD : curShark.dirOrder[curD]){
                    int nextI = curShark.curI + di[nextD];
                    int nextJ = curShark.curJ + dj[nextD];
                    if(isBounded(nextI, nextJ, N) && smellMap[nextI][nextJ][0] == curShark.id){
                        goProcess(curShark.curI, curShark.curJ, nextI, nextJ, nextD , curShark.id, sharks);
                        break;
                    }
                }
            }
        }

        /*
        cout << endl;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout << '(' << smellMap[i][j][0] << ", " << smellMap[i][j][1] << ')' << " ";
            }
            cout << endl;
        }
        */

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(smellMap[i][j][1] > 0) smellMap[i][j][1]--;
                if(smellMap[i][j][1] == 0) smellMap[i][j][0] = 0;
            }
        }
        for(auto shark : sharks){
            if(shark.alive){
                smellMap[shark.curI][shark.curJ][0] = shark.id;
                smellMap[shark.curI][shark.curJ][1] = k;
                q.push(shark);
            }
        }
        ans++;
    }

    cout << ans << endl;
    return 0;
}