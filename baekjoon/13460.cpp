#include<iostream>
#include<queue>
using namespace std;

int N, M;
char mem[10][10];
int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};

struct ObjectPos{
    int redI;
    int redJ;
    int blueI;
    int blueJ;
    int preD;
};

bool isBound(int i, int j){
    if(1<=i && i <N-1 && 1<= j && j < M-1) return true;
    return false;
}

void moveUpdate(int ch, int &i, int &j, int oI, int oJ, int d){
    if(i == -1 && j == -1) return;
    while(true){
        int nextI = i + di[d];
        int nextJ = j + dj[d];
        if(isBound(nextI, nextJ) && !(nextI == oI && nextJ == oJ)){
            if(mem[nextI][nextJ] == '.'){
                i = nextI;
                j = nextJ;
            }
            else if(mem[nextI][nextJ] == 'O'){
                i = -1;
                j = -1;
            }
            else{
                break;
            }
        }
        else{
            break;
        }
    }
}

int bfs(int redI, int redJ, int blueI, int blueJ){
    queue<ObjectPos> q;
    q.push({redI, redJ, blueI, blueJ, -1});
    int ret = 1;
    while(!q.empty()){
        if(ret > 10) return -1; 
        int size = q.size();
        for(int s=0; s<size;s++){
            auto curObjectPos = q.front();
            q.pop();
            int curRedI = curObjectPos.redI;
            int curRedJ = curObjectPos.redJ;
            int curBlueI = curObjectPos.blueI;
            int curBlueJ = curObjectPos.blueJ;
            for(int d=0;d<4;d++){
                if(d == curObjectPos.preD) continue;
                int nextRedI = curRedI;
                int nextRedJ = curRedJ;
                int nextBlueI = curBlueI;
                int nextBlueJ = curBlueJ; 
                
                moveUpdate('B', nextBlueI, nextBlueJ, nextRedI, nextRedJ, d);
                moveUpdate('R', nextRedI, nextRedJ, nextBlueI, nextBlueJ ,d);
                moveUpdate('B', nextBlueI, nextBlueJ, nextRedI, nextRedJ, d);
                if(nextRedI == curRedI && nextRedJ == curRedJ){
                    if(nextBlueI == curBlueI && nextBlueJ == curBlueJ){
                        continue;
                    }
                }
                if(nextBlueI == -1 && nextBlueJ == -1) continue;
                if(nextRedI == -1 && nextRedI == -1) return ret;
                q.push({nextRedI, nextRedJ, nextBlueI, nextBlueJ, d});
            }
        }
        ret++;
    }
    return -1;
}

int main(){
    cin >> N >> M;
    int redI, redJ;
    int blueI, blueJ;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            char ch;
            cin >> ch;
            if(ch == 'R'){
                redI = i;
                redJ = j;
                mem[i][j] = '.';
                continue;
            }
            if(ch == 'B'){
                blueI = i;
                blueJ = j;
                mem[i][j] = '.';
                continue;
            }
            mem[i][j] = ch;
            
        }
    }

    int ans = bfs(redI, redJ, blueI, blueJ);
    cout << ans << endl;
    return 0;
}