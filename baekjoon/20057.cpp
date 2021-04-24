#include<iostream>

using namespace std;

int di[] = {0,1,1,1,0,-1,-1,-1};
int dj[] = {-1,-1,0,1,1,1,0,-1};

int N;
int mem[500][500];
bool isBound(int i, int j){
    if(0<=i && i < N && 0<=j && j < N) return true;
    return false;
}
int ans = 0;
void addSand(int nextI, int nextJ, int sand){
    if(sand == 0) return;
    if(isBound(nextI, nextJ)){
        mem[nextI][nextJ] += sand;
    }
    else{
        ans += sand;
    }
}
int main(){    
    cin >> N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int tmp;
            cin >> mem[i][j];
        }
    }

    int curI, curJ, curD;
    curI = N/2;
    curJ = N/2;
    curD = 0;
    int curLen = 1;
    while(true){
        
        if(curI == 0 && curJ == 0) break;
        for(int i=0;i<curLen;i++){
            int nextI = curI + di[curD];
            int nextJ = curJ + dj[curD];
            
            curI = nextI;
            curJ = nextJ;
            if(mem[nextI][nextJ] == 0) {
                continue;
            }
            int res = mem[nextI][nextJ];

            for(int d=-3;d<=3;d++){
                int sandD = (curD + d + 8) % 8;
                int sandI, sandJ;
                int cal = 0;
                sandI = nextI + di[sandD];
                sandJ = nextJ + dj[sandD];
                if(d == -2 || d == 0 || d == 2){
                    for(int cnt=1;cnt<=2;cnt++){
                        sandI = nextI + di[sandD]*cnt;
                        sandJ = nextJ + dj[sandD]*cnt;
                        if(d == -2 || d == 2){
                            if(cnt == 1){
                                cal = mem[nextI][nextJ] * 7 / 100;
                            }
                            else if(cnt == 2){
                                cal = mem[nextI][nextJ] * 2 / 100;
                            }
                            addSand(sandI, sandJ, cal);
                        }
                        else if(d == 0 && cnt == 2){
                            cal = mem[nextI][nextJ] * 5 / 100;
                            addSand(sandI, sandJ, cal);
                        }
                        res -= cal;
                    }
                    continue;
                }
                if(d == -3){
                    cal = mem[nextI][nextJ] / 100;
                }
                else if(d == 3){
                    cal = mem[nextI][nextJ] / 100;
                }
                else if(d == -1){
                    cal = mem[nextI][nextJ] / 10;
                }
                else if(d == 1){
                    cal = mem[nextI][nextJ] / 10;
                }
                res -= cal;
                addSand(sandI, sandJ, cal);
            }

            int destI = nextI + di[curD];
            int destJ = nextJ + dj[curD];
            addSand(destI, destJ, res);
            mem[nextI][nextJ] = 0;
            
        }

        curD+=2;
        curD %= 8;
        if(curD == 0 || curD == 4){
            curLen++;
            curLen = min(curLen, N-1);
        }
    }

    cout << ans <<endl;
    return 0;
}