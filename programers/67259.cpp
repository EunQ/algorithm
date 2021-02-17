#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int di[4] = {0,0,1,-1};
int dj[4] = {1,-1,0,0};
int answer = 0;

//이런 문제를 풀때는 dfs, bfs를 각각 확인한 후.
//만약 DP를 적용시킬 려면 bfs방법을 고려한다.

bool isNext(int i, int j, vector<vector<int>> &board){
    if(0<= i && i < board.size() && 0<= j && j < board.size()){
        if(board[i][j] == 0) return true;
    }
    return false;

}
#define LIMIT 123456789

struct Pos{
    int i,j,dir;
    int cost;
};

int bfs(vector<vector<int>> &board){
    vector<vector<int>> mem(board.size(), vector<int> (board.size(), LIMIT));
    mem[0][0] = 0;
    queue<Pos> q;
    for(int d=0;d<4;d++){
        int nextI = di[d];
        int nextJ = dj[d];
        if(isNext(nextI, nextJ, board)) q.push({nextI, nextJ, d,100});
    }
    answer = LIMIT;
    while(!q.empty()){
        int size = q.size();
        for(int i=0;i<size;i++){
            auto curPos = q.front();
            q.pop();
            if(curPos.cost >= answer) continue;
            for(int dir=0;dir<4;dir++){
                int nextI = curPos.i + di[dir];
                int nextJ = curPos.j + dj[dir];
                if(isNext(nextI, nextJ, board)){
                    int nextCost = curPos.cost + 100;
                    if(curPos.dir != dir) nextCost += 500;
                    if(nextI == board.size()-1 && nextJ = board.size()-1){
                        answer = min(answer, nextCost);
                    }
                    if(nextCost <= mem[nextI][nextJ]){
                        mem[nextI][nextJ] = nextCost;
                        q.push({nextI, nextJ, dir, nextCost});
                    }
                }
            }
        }
    }
    return answer;
}

int solution(vector<vector<int>> board) {
    answer = LIMIT;

    bfs(board);
    return answer;
}