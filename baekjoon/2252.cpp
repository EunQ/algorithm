#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Node{
    vector<int> nextNodes;
    int refCnt;
};
Node nodes[32001];

int N, M;

int main(){
    cin >> N >> M;
    for(int m=0;m<M;m++){
        int a,b;
        cin >> a >> b;
        nodes[a].nextNodes.push_back(b);
        nodes[b].refCnt++;
    }
    queue<int> q;
    for(int i=1;i<=N;i++){
        if(nodes[i].refCnt == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int size = q.size();
        for(int s=0;s<size;s++){
            auto curIdx =q.front();
            q.pop();
            cout << curIdx << " ";
            for(auto nextIdx : nodes[curIdx].nextNodes){
                nodes[nextIdx].refCnt--;
                if(nodes[nextIdx].refCnt == 0){
                    q.push({nextIdx});
                }
            }
        }
    }
    cout << endl;
    return 0;
}