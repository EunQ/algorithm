#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

struct Road{
    int next, cost;
};

struct Info{
    int curIdx, cost;
    int status;

    bool operator < (const Info& tmp) const{
        return cost > tmp.cost;
    }
};

int dijkstra(vector<vector<vector<Road>>>& graph, vector<int> traps, int start, int end){

    priority_queue<Info> pq;
    vector<vector<int>> mem (1 << traps.size(), vector<int>(1001, 1234567890));
    map<int, int> trapMap;

    int trapIdx = 1;
    for(auto& trap : traps){
        trapMap[trap] = trapIdx++;
    }

    pq.push({start, 0, 0});
    mem[0][start] = 0;
    while(!pq.empty()){
        auto curInfo = pq.top();
        pq.pop();
        int curCost = curInfo.cost;
        int curIdx = curInfo.curIdx;
        int curStatus = curInfo.status;
        if(curIdx == end) return curCost;
        for(auto& nextNode : graph[curStatus][curIdx]){
            int nextIdx = nextNode.next;
            int nextStatus = curStatus;
            int nextCost = curCost + nextNode.cost;
            if(trapMap[nextIdx]){
                nextStatus = curStatus ^ (1 << (trapMap[nextIdx] - 1));
            }
            if(mem[nextStatus][nextIdx] >= nextCost){
                pq.push({nextIdx, nextCost, nextStatus});
                mem[nextStatus][nextIdx] = nextCost;
            }
        }
    }
    return -1;
}


#include <iostream>
#include <map>
int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    int answer = 0;
    int trapSize = traps.size();
    vector<vector<vector<Road>>> graph(1 << trapSize);
    for(int i=0;i< (1<<trapSize); i++){
        map<int, int> visitedMap;
        vector<vector<Road>> newAdj (n+1);
        for(int j=0;j<trapSize;j++){
            if((1 << j) & i){
                visitedMap[traps[j]] += 1;
            }
        }

        for(auto& road : roads){
            int start = road[0];
            int end = road[1];
            int cost = road[2];

            if(visitedMap[start] == 1 ^ visitedMap[end] == 1){
                start = road[1];
                end = road[0];
            }
            newAdj[start].push_back({end, cost});
        }
        graph[i] = newAdj;
    }

    answer = dijkstra(graph, traps,  start,  end);
    return answer;
}

int main(){
    solution(3,1,3, {{1,2,2}, {3,2,3}}, {2});
}