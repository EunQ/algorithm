#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int visited[201];
int weakVisited[201];
int answer = 0;
int mod = 1;
void dfs(int weakCnt, int ansCnt, int idx, vector<int>& weak, vector<int>& dist){
    if(weakCnt == weak.size()){
        answer = min(answer, ansCnt);
        return;
    }
    if(idx < 0){
        return;
    }
    if(answer <= ansCnt) return ;

    for(int curPos : weak){
        int tmpWeakCnt = 0;
        if(visited[curPos]) continue;
        for(int cnt = 0;cnt <= dist[idx];cnt++){
            int next = (curPos + cnt) % mod;
            visited[next]++;
            if(weakVisited[next] == -2){
                //0도 idx에 포함됨
                weakVisited[next] = idx;
                tmpWeakCnt++;
            }
        }
        dfs(weakCnt + tmpWeakCnt, ansCnt + 1, idx-1, weak, dist);
        for(int cnt = 0;cnt <= dist[idx];cnt++){
            int next = (curPos + cnt) % mod;
            visited[next]--;
            if(weakVisited[next] == idx)
                weakVisited[next] = -2;
            
        }
    }
    
}

int solution(int n, vector<int> weak, vector<int> dist) {
    answer = dist.size()+1;
    //visited 변수 사용시 주의할 문제
    for(int i=0;i<=n;i++){
        visited[i] = 0;
        weakVisited[i] = -1;
    }
    for(int i : weak){
        weakVisited[i] = -2;
        //이 변수 사용할 때 주의
    }
    mod = n;
    sort(dist.begin(), dist.end());
    dfs(0, 0, dist.size()-1, weak, dist );
    if (answer == dist.size() + 1) answer = -1;
    return answer;
}
