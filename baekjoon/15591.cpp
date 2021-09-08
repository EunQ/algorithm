#include<iostream>
#include<vector>
#include <algorithm>
#include <queue>
using namespace std;

int N, Q;

int bfs(vector<vector<pair<int, int>>> &adj, int idx, int cost){
    int res = 0;
    queue<pair<int, int>> q;
    vector<bool> visited(N);
    q.push({idx, 100000000 });
    while(!q.empty()){
        int curIdx = q.front().first;
        int curCost = q.front().second;
        visited[curIdx] = true;
        q.pop();

        for(auto nextInfo : adj[curIdx]){
            int nextIdx = nextInfo.first;
            int nextCost = nextInfo.second;
            if(visited[nextIdx]) continue;
            nextCost = min(nextCost, curCost);
            if(nextCost < cost) continue;
            res++;
            q.push({nextIdx, nextCost});
        }

    }

    return res;
}

int main(){

    cin >> N >> Q;

    vector<vector<pair<int, int>>> adj(N);

    for(int i=0;i<N-1;i++){
        int a,b,c;
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }

    for(int j=0;j<Q;j++){
        int k,v;
        cin >> k >> v;
        int tmpAns = bfs(adj, v-1, k);
        cout << tmpAns << endl;        
    }

    return 0;
}