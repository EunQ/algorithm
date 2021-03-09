#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<queue>

using namespace std;

#define POS vector<pair<int, int>> 
#define MAP vector<vector<int>> 
#define HOR 0
#define VER 1

int di[] = {0,-1,0,1};
int dj[] = {-1,0,1,0};

int getCurShape(POS& cur){
    if(cur[0].first == cur[0].first){
        //y축이 같은 경우.
        return HOR;
    }
    return VER;
}

bool isNext(int i, int j, MAP& board){
    int N = board.size();
    if(0<=i && i <N && 0<=j && j < N){
        if(board[i][j] == 0) return true;
    }
    return false;
}


vector<POS> getRotationPosVec(pair<int,int> center, pair<int, int> other, MAP& board){
    vector<POS> res;
    //여기에 후보군들을 전부.
    int cenY = center.first;
    int otherY = other.first;
    if(cenY == otherY ){
        for(int addNext = -1;addNext <=1;addNext+=2){
            if(  isNext(center.first + addNext , center.second, board) && 
                isNext(other.first +addNext , other.second , board)){
                
                if(addNext == 1){
                    res.push_back({center, {other.first+1, other.second-1}});
                    res.push_back({other, {center.first+1, center.second+1}});
                }
                else{
                    res.push_back({{other.first-1, other.second-1  }, center});
                    res.push_back({{center.first-1, center.second+1  }, other}); 
                }
            }
        }
    }
    else{
        for(int addNext = -1;addNext <=1;addNext+=2){
            if(  isNext(center.first , center.second+addNext , board) && 
                isNext(other.first , other.second +addNext , board)){
                
                if(addNext == 1){
                    res.push_back({center, {other.first-1, other.second+1}});
                    res.push_back({other, {center.first+1, center.second+1}});
                }
                else{
                    res.push_back({{other.first-1, other.second-1  }, center});
                    res.push_back({{center.first+1, center.second-1  }, other}); 
                }
            }
        }
    }

    return res;
}


bool isAns(POS& cur, int N){
    if(cur[0].first == N-1 && cur[0].second == N-1) return true;
    if(cur[1].first == N-1 && cur[1].second == N-1) return true;
    return false;
}

int bfs(MAP board){
    int ans = 1;
    map<POS, int> visited;
    queue<POS> q;
    q.push({{0,0},{0,1}});
    visited[{{0,0},{0,1}}] = 1;
    while(!q.empty()){
        int size = q.size();
        for(int i=0;i<size;i++){
            auto curPos = q.front();
            if(isAns(curPos, board.size())) {
                return ans-1;
            }
            q.pop();
            for(int d=0;d<4;d++){
                pair<int, int> pos1 = {curPos[0].first + di[d], curPos[0].second + dj[d]};
                pair<int, int> pos2 = {curPos[1].first + di[d], curPos[1].second + dj[d]};
                if(isNext(pos1.first, pos1.second, board) &&
                    isNext(pos2.first, pos2.second, board)){
                        if(visited[{pos1, pos2}] == 0){
                            visited[{pos1, pos2}] = ans;
                            q.push({pos1, pos2});
                        }
                    }
                
            }
            for( auto nextPOS : getRotationPosVec(curPos[0], curPos[1], board) ){
                if(visited[nextPOS] == 0){
                    visited[nextPOS] = ans;
                    q.push(nextPOS);
                }
            }

        }
        ans++;
    }
    return ans-1;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    return answer = bfs(board);
}

int main(){
    solution( { {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0} });
    return 0;
}