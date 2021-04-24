#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N,K;
int upIdx;
int downIdx;
int main(){
    cin >> N >> K;
    vector<int> belt(N*2);
    for(int i=0;i<N*2;i++){
        int tmp;
        cin >> tmp;
        belt[i] = tmp;
    }
    queue<int> q;
    int zeroCnt = 0;
    upIdx = 0;
    downIdx = N-1;
    vector<int> visited(N*2);
    int ans = 1;
    while(true){
        
        upIdx = (upIdx - 1 + 2*N) % (2*N);
        downIdx = (downIdx - 1 + 2*N) % (2*N);
        if(!q.empty()){
            //
            int size = q.size();
            for(int i=0;i<size;i++){
                int pos = q.front();
                q.pop();
                if(pos == downIdx){
                    visited[pos] = 0;
                    continue;
                }    
                int nextPos = (pos + 1) % (2*N);
                if(visited[nextPos] == 0 && belt[nextPos] >= 1){
                    visited[nextPos] = 1;
                    belt[nextPos]--;
                    if(belt[nextPos] == 0) zeroCnt++;
                    visited[pos] = 0;

                    if(nextPos == downIdx){
                        visited[nextPos] = 0;
                        continue;
                    }
                    pos = nextPos;
                }
                q.push(pos);
            }
        }
        if(belt[upIdx]){
            q.push(upIdx);
            belt[upIdx]--;
            if(belt[upIdx] == 0) zeroCnt++;
            visited[upIdx] = 1;
        }
        if(zeroCnt >= K){
            break;
        }
        ans++;
    }
    cout << ans << endl;
    return 0;
}