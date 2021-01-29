#include <string>
using namespace std;
bool isBounded(int x, int y){
    if(0<= x && x <= 10 ){
        if(0<=y && y<= 10){
            return true;
        }
    }
    return false;
}

int getDir(char c){
    if(c == 'L') return 0;
    if(c == 'R') return 1;
    if(c == 'D') return 2;
    if(c == 'U') return 3;
}
int getReverseDir(char c){
    if(c == 'L') return 1;
    if(c == 'R') return 0;
    if(c == 'D') return 3;
    if(c == 'U') return 2;
}

int solution(string dirs) {
    int answer = 0;
    int db[11][11][4] = {0};
    // -5 -4 -3 -2 -1 0 1 2 3 4 5 
    // 0  1   2  3  4 5 6 7 8 9 10
    int curX = 5;
    int curY = 5;
    for(char c : dirs){
        int nextX = curX;
        int nextY = curY;
        if (c == 'L'){
            // x == -1
            // y == 0
            nextX += -1;
        }
        else if(c == 'R'){
            // x == 1
            // y == 0;
            nextX += 1;
        }
        else if(c == 'D'){
            // x == 0;
            // y == -1;
            nextY += -1;
        }
        else{  
            // x == 0;
            // y == 1;
            nextY += 1;
        }
        if(isBounded(nextX, nextY)){
            db[curX][curY][getDir(c)] = 1;
            db[nextX][nextY][getReverseDir(c)] = 1;
            curX = nextX;
            curY = nextY;
        }
    }

    for(int i=0;i<=10;i++){
        for(int j=0;j<=10;j++){
            for(int d=0;d<4;d++){
                answer += db[i][j][d];
            }
        }
    }
    answer /= 2;
    return answer;
}