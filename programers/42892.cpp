#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct pos{
    int x,y;
    int leftIdx, rightIdx;
    int rightMax;
    int idx;
    bool operator<(const pos& b){
        if ( y == b.y){
            return x < b.x;
        }
        return y > b.y;
    }
};

void inOrder(const pos& curPos, vector<pos> &posVec ,vector<int> &ans){
    ans.push_back(curPos.idx);
    if(curPos.leftIdx != -1) inOrder(posVec[curPos.leftIdx], posVec, ans);
    if(curPos.rightIdx != -1) inOrder(posVec[curPos.rightIdx], posVec, ans);
}   

void postOrder(const pos& curPos, vector<pos> &posVec ,vector<int> &ans){
    if(curPos.leftIdx != -1) postOrder(posVec[curPos.leftIdx], posVec, ans);
    if(curPos.rightIdx != -1) postOrder(posVec[curPos.rightIdx], posVec, ans);
    ans.push_back(curPos.idx);
}  

//더 효율적인 방법을 찾아보자.
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<pos> posVec;
    int curIdx = 1;
    for(auto curPos : nodeinfo){
        int x = curPos[0];
        int y = curPos[1];
        posVec.push_back({x,y,-1,-1, 100000, curIdx});
        curIdx++;
    }
    sort(posVec.begin(), posVec.end());
    queue<int> q;
    q.push(0);
    int height = -1;
    int cnt = 0;
    for(int i=1;i<posVec.size();i += cnt){
        height = posVec[i].y;
        for(cnt = 1;cnt + i < posVec.size();cnt++){
            if(posVec[i+cnt].y != height) break;
        }
        int size = q.size();
        int curVecPos = 0;
        for(int j=0;j<size;j++){
            bool isPush = false;
            int standByPosIdx = q.front();
            pos& standByPos = posVec[standByPosIdx];
            q.pop();
            if(curVecPos <cnt && standByPos.leftIdx == -1 && posVec[i+curVecPos].x < standByPos.x){
                standByPos.leftIdx = i + curVecPos;
                posVec[i+curVecPos].rightMax = standByPos.x - 1;
                q.push(i+curVecPos);
                curVecPos++;
            }
            else{
                isPush = true;
                q.push(standByPosIdx);
            }
            if(curVecPos < cnt && standByPos.rightIdx == -1 && posVec[i+curVecPos].x <= standByPos.rightMax){
                standByPos.rightIdx = i + curVecPos;
                posVec[i+curVecPos].rightMax = standByPos.rightMax;
                q.push(i+curVecPos);
                curVecPos++;
            }
            else if(!isPush){
                q.push(standByPosIdx);
            }
        }
    }

    vector<int> ans1; 
    inOrder(posVec[0], posVec, ans1);
    vector<int> ans2; 
    postOrder(posVec[0], posVec, ans2);
    answer.push_back(ans1);
    answer.push_back(ans2);
    return answer;
}

int main(){


    auto ans = solution({{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}});
}