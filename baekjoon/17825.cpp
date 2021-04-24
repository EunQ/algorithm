#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

//틀린 이유, 맵을 정확히 설정하지 않아서.
//visited[] 할 때 올바르게 설정을 하지 못해서.

vector<int> dices;
int ans;

struct Path
{
    int cost;
    int nextPath;
};

#define START 0
#define END 33

Path path[34];
bool visited[34];
vector<int> objects;

int getNextIdx(int curIdx, bool isStart){
    if(isStart){
        if(curIdx == 5){
            return 21;
        }
        if(curIdx == 10){
            return 24;
        }
        if(curIdx == 15){
            return 26;
        }
    }
    return path[curIdx].nextPath;
}


void dfs(int diceIdx, int sum){
    ans = max(ans, sum);
    if(diceIdx == 10){
        return;
    }
    int diceVal = dices[diceIdx];

    for(auto& cur : objects){
        if(cur == END) {
            continue;
        }
        auto pre = cur;
        for(int cnt=0;cnt<diceVal;cnt++){
            int nextIdx = getNextIdx(cur, cnt == 0);
            cur = nextIdx;
            if(cur == END) break;
        }
        if(!visited[cur] || cur == END){
            visited[pre] = false;
            visited[cur] = true;
            dfs(diceIdx+1, sum + path[cur].cost);
            visited[cur] = false;
            visited[pre] = true;
        }
        cur = pre;
    }
}

int main(){
    
    for(int i=0;i<=20;i++){
        path[i].cost = i*2;
        path[i].nextPath = i+1;
    }
    path[20].nextPath = END;

    path[END].cost = 0;
    path[END].nextPath = -1;

    path[21].nextPath = 22;
    path[21].cost = 13;
    path[22].nextPath = 23;
    path[22].cost = 16;
    path[23].nextPath = 29;
    path[23].cost = 19;

    path[24].nextPath = 25;
    path[24].cost = 22;
    path[25].nextPath = 29;
    path[25].cost = 24;

    path[26].nextPath = 27;
    path[26].cost = 28;
    path[27].nextPath = 28;
    path[27].cost = 27;
    path[28].nextPath = 29;
    path[28].cost = 26;

    path[29].nextPath = 30;
    path[29].cost = 25;
    path[30].nextPath = 31;
    path[30].cost = 30;
    path[31].nextPath = 20;
    path[31].cost = 35;

    for(int i=0;i<4;i++){
        objects.push_back({0});
    }

    for(int i=0;i<10;i++){
        int tmp;
        cin >> tmp;
        dices.push_back(tmp);
    }

    dfs(0, 0);

    cout << ans << endl;
}