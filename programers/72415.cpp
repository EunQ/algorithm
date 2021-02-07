#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#define WIDTH  4
#define HEIGHT 4

int dir_y[4] = {0,-1,1,0};
int dir_x[4] = {-1,0,0,1};

bool isVaild(int y, int x){
    if (0<=y && y< HEIGHT)
        if (0<=x && x < WIDTH) return true;
    return false;
}

bool isEdge(int y, int x, int d){
    int next_y = y + dir_y[d];
    int next_x = x + dir_x[d];
    if(!isVaild(next_y, next_x)) return true;
    return false;
}

int ans = 0;

int startToEnd(vector<vector<int>>& board, pair<int, int> start, pair<int, int> end){
    vector<vector<int>> visitied(4, vector<int> (4, 0));
    visitied[start.first][start.second] = 1;
    queue<pair<int, int>> q;
    q.push(start);
    int step = 0;

    while(!q.empty()){
        int size = q.size();
        for(int i=0;i<size;i++){
            auto cur = q.front();
            q.pop();
            if(cur.first == end.first && cur.second == end.second){
                return step;
            }
            for(int d=0;d<4;d++){
                int next_y = cur.first + dir_y[d];
                int next_x = cur.second + dir_x[d];
                if(isVaild(next_y, next_x) && !visitied[next_y][next_x])
                {
                    visitied[next_y][next_x] = true;
                    q.push({next_y, next_x});
                }
                if(isVaild(next_y, next_x) && board[next_y][next_x]) continue;
                for(int plus=1;plus<4;plus++){
                    next_y += dir_y[d];
                    next_x += dir_x[d];
                    if(!isVaild(next_y, next_x)){
                        break;
                    }
                    if(visitied[next_y][next_x]) continue;
                    if(board[next_y][next_x]){
                        visitied[next_y][next_x] = true;
                        q.push({next_y, next_x});
                        break;
                    }
                    if(isEdge(next_y, next_x, d)){
                        visitied[next_y][next_x] = true;
                        q.push({next_y, next_x});
                        break;
                    }
                }
            }
        } 
        step++;
    }
    return step;
}   

void search(vector<vector<int>>& board, pair<int, int> start, int step){
    int res = 0;
    queue<pair<int, int>> startQ;
    for(int i=0;i<HEIGHT; i++){
        for(int j=0;j<WIDTH;j++){
            if(board[i][j] != 0) startQ.push({i, j});
        }
    }
    if (startQ.empty()) {
        ans = min(ans, step);
    }
    else{
        while(!startQ.empty()){
            int res = 0;
            auto cur = startQ.front();
            startQ.pop();
            pair<int, int> nextEnd;
            for(int i=0;i<HEIGHT;i++){
                for(int j=0;j<WIDTH;j++){
                    if(board[cur.first][cur.second] == board[i][j] &&  (cur.first != i || cur.second != j)){
                        //조건문 주의
                        nextEnd = {i, j};
                        break;
                    }
                }
            }
            res += startToEnd(board,start, cur);
            int pre = board[cur.first][cur.second];
            res++;
            res += startToEnd(board,cur, nextEnd);
            board[cur.first][cur.second] = 0;
            board[nextEnd.first][nextEnd.second] = 0;
            res++;
            if(ans > res)
                search(board, nextEnd, res + step);
            board[cur.first][cur.second] = pre;
            board[nextEnd.first][nextEnd.second] = pre;
        }
    }
}

int solution(vector<vector<int>> board, int r, int c) {
    
    ans = 9999;
    search(board, {r,c}, 0);
    return ans;
}
