#include<iostream>
#include<vector>
using namespace std;

//실패.

int greenMap[6][4];
int blueMap[4][6];

int N;
int di[] = {1,0};
int dj[] = {0,1};


int pushBlueMap(int t, int x, int y){
    vector<pair<int, int>> pos;
    int ret = 0;
    if(t == 1){
        pos.push_back({x,0});
    }
    else if(t == 2){
        pos.push_back({x,1});
        pos.push_back({x,0});
    }
    else{
        pos.push_back({x+1,0});
        pos.push_back({x  ,0});
    }

    bool isNext = true;
    for(int j=0;j<6;j++){
        for(int idx=0;idx<pos.size();idx++){
            int nextI = pos[idx].first  + di[1];
            int nextJ = pos[idx].second + dj[1];
            if(nextJ >= 6 || blueMap[nextI][nextJ] != 0){
                isNext = false;
                break;
            }
        }
        if(!isNext) break;
        for(int idx=0;idx<pos.size();idx++){
            pos[idx].first  += di[1];
            pos[idx].second += dj[1];
        }
    }
    for(auto curPos : pos){
        blueMap[curPos.first][curPos.second] = 1;
    }
    for(int j=5;j>=0;j--){
        int cnt = 0;
        for(int i=0;i<4;i++){
            if(blueMap[i][j]) cnt++;
        }
        if(cnt == 4){
            ret++;
            for(int i=0;i<4;i++){
                blueMap[i][j] = 0;
            }
            for(int nextJ = j-1;nextJ>=0;nextJ--){
                for(int i=0;i<4;i++){
                    blueMap[i][nextJ+1] = blueMap[i][nextJ];
                    blueMap[i][nextJ] = 0;
                }
            }
            j +=1;
        }
    }

    int deleteCol = 0;
    for(int j=0;j<2;j++){
        for(int i=0;i<4;i++){
            if(blueMap[i][j]){
                deleteCol++;
                break;
            }
        }    
    }

    if(deleteCol){
        int nextJ = 5;
        for(int j=5-deleteCol;j>=0;j--){
            for(int i=0;i<4;i++){
                blueMap[i][nextJ] = blueMap[i][j];
                blueMap[i][j] = 0;
            }
            nextJ--;
        }
    }
    return ret;
}

int pushGreenMap(int t, int x, int y){
    vector<pair<int, int>> pos;
    int ret = 0;
    if(t == 1){
        pos.push_back({0,y});
    }
    else if(t == 2){
        pos.push_back({0,y});
        pos.push_back({0,y+1});
    }
    else{
        pos.push_back({1,y});
        pos.push_back({0,y});
    }

    bool isNext = true;
    for(int i=0;i<6;i++){
        for(int idx=0;idx<pos.size();idx++){
            int nextI = pos[idx].first  + di[0];
            int nextJ = pos[idx].second + dj[0];
            if(nextI >= 6 || greenMap[nextI][nextJ] != 0){
                isNext = false;
                break;
            }
        }
        if(!isNext) break;
        for(int idx=0;idx<pos.size();idx++){
            pos[idx].first  += di[0];
            pos[idx].second += dj[0];
        }
    }
    for(auto curPos : pos){
        greenMap[curPos.first][curPos.second] = 1;
    }
    for(int i=5;i>=0;i--){
        int cnt = 0;
        for(int j=0;j<4;j++){
            if(greenMap[i][j]) cnt++;
        }
        if(cnt == 4){
            ret++;
            for(int j=0;j<4;j++){
                greenMap[i][j] = 0;
            }
            for(int nextI = i-1;nextI>=0;nextI--){
                for(int j=0;j<4;j++){
                    greenMap[nextI+1][j] = greenMap[nextI][j];
                    greenMap[nextI][j] = 0;
                }
            }
            i+=1;
        }
    }

    int deleteRow = 0;
    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            if(greenMap[i][j]) {
                deleteRow++;
                break;
            }
        }    
    }

    if(deleteRow){
        int nextI = 5;
        for(int i=5-deleteRow;i>=0;i--){
            for(int j=0;j<4;j++){
                greenMap[nextI][j] = greenMap[i][j];
                greenMap[i][j] = 0;
            }
            nextI--;
        }
    }
    return ret;
}

int main(){
    cin >> N;
    int ans = 0;
    for(int n=0;n<N;n++){
        int t,x,y;
        cin >> t >> x >> y;
        ans += pushGreenMap(t,x,y);
        ans += pushBlueMap(t,x,y);
    }
    int cnt = 0;
    for(int i=2;i<6;i++){
        for(int j=0;j<4;j++){
            cnt += greenMap[i][j];
            cnt += blueMap[j][i];
        }
    }
    cout << ans << endl;
    cout << cnt << endl;

}
