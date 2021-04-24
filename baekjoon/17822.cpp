#include<iostream>
#include<vector>
#include<deque>
#include<queue>
//원판돌리기, 시간초과, 문제실패.

using namespace std;

int N, M, T;
deque<int> circle[51];
int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};
int bfs_check(int i, int j){
    if(circle[i][j] == -1) return 1;
    vector<vector<int>> visited (N+1, vector<int>(M));
    queue<pair<int, int>> q;
    int checkNum = circle[i][j];
    q.push({i,j});
    visited[i][j] = true;
    circle[i][j] = -1;
    int cnt = 0;
    while(!q.empty()){
        int size = q.size();
        for(int s=0;s<size;s++){
            auto curPos = q.front();
            q.pop();
            for(int d=0;d<4;d++){
                int nextI = curPos.first + di[d];
                int nextJ = (curPos.second + dj[d] + M) % M;
                if(1<= nextI && nextI <= N && !visited[nextI][nextJ] && circle[nextI][nextJ] == checkNum) {
                    visited[nextI][nextJ] = true;
                    circle[nextI][nextJ] = -1;
                    q.push({nextI, nextJ});
                }
            }
        }
        cnt++;
    }
    if(cnt == 1){
        circle[i][j] = checkNum;
    }
    return cnt;
}

int main(){
    cin >> N >> M >> T;
    int ans = 0;
    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++){
            int tmp = 0;
            cin >> tmp;
            circle[i].push_back(tmp);
        }
    }
    for(int t=1;t<=T;t++){
        int x,d,k;
        cin >> x >> d >> k;
        for(int i=x;i<=N;i+=x){
            if(d == 1){
                //시계방향
                for(int j=0;j<k;j++){
                    int tmp = circle[i].front();
                    circle[i].pop_front();
                    circle[i].push_back(tmp);
                }
            }
            else{
                //반시계
                for(int j=0;j<k;j++){
                    int tmp = circle[i].back();
                    circle[i].pop_back();
                    circle[i].push_front(tmp);
                }
            }
        }
        bool downUpCnt = true;
        for(int i=1;i<=N;i++){
            for(int j=0;j<M;j++){
                int cnt = bfs_check(i, j);
                if(cnt >= 2){
                    downUpCnt = false;
                }
            }
        }
        if(downUpCnt){
            double avg = 0;
            int cnt = 0;
            for(int i=1;i<=N;i++){
                for(int j=0;j<M;j++){
                    if(circle[i][j] == -1) continue;
                    avg += (double)circle[i][j];
                    cnt++;
                }
            }
            avg /= cnt;
            for(int i=1;i<=N;i++){
                for(int j=0;j<M;j++){
                    if(circle[i][j] == -1) continue;
                    if(circle[i][j] > avg) circle[i][j]--;
                    else if(circle[i][j] < avg) circle[i][j]++;
                }
            }
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=0;j<M;j++){
            if(circle[i][j] == -1) continue;
            ans += circle[i][j];
        }
    }
    cout << ans <<endl;

    return 0;
}