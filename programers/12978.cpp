#include<algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int idx;
    int cost;

    bool operator<  (const Node& a) const{
        return cost > a.cost;
    }
};


int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    int LIMIT = 200*10000 + 1;
    vector<vector<int>> db(N+1, vector<int>(N+1, LIMIT));
    vector<int> mem(N+1, LIMIT);
    mem[1] = 0;

    for(int i=0;i<road.size();i++){
        int a,b,c;
        a = road[i][0];
        b = road[i][1];
        c = road[i][2];
        db[a][b] = min(db[a][b],c);
        db[b][a] = min(db[b][a],c);
    }

    priority_queue<Node> pq;
    vector<bool> visited(N+1, 0);
    pq.push({1, 0});
    while(!pq.empty()){
        auto curNode = pq.top();
        pq.pop();
        int curIdx = curNode.idx;
        visited[curIdx] = 1;
        cout << curIdx << endl;
        for(int i=1;i<=N;i++){
            if(db[curIdx][i] != 0 && !visited[i]){
                if(mem[i] > db[curIdx][i] + curNode.cost){
                    mem[i] = db[curIdx][i] + curNode.cost;
                    pq.push({i, mem[i]});
                }
            }
        }
    }

    for(int i=1;i<=N;i++){
        if(mem[i] <= K) answer++;
    }

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    //cout << "Hello Cpp" << endl;

    return answer;
}

int main(){

    int ans = solution(5, {{1,2,1},{2,3,3},{5,2,2},{1,4,2},{5,3,1},{5,4,2}}, 3);
    return 0;

}