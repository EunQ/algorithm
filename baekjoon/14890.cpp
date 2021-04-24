#include<iostream>

using namespace std;
int N,L;
struct block{
    int h;
    int isAdd;
};
block mem[100][100];
int diff(int a, int b){
    if (a > b) return a - b;
    return b - a;
}
int main(){

    cin >> N >> L;
    int ans = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> mem[i][j].h;
        }
    }

    for(int i=0;i<N;i++){
        //행에 대해서 확인.
        int pre = mem[i][0].h;
        bool isCnt = true;
        for(int j=1;j<N;j++){
            int cur = mem[i][j].h;
            if(cur == pre) continue;
            if(diff(pre, cur) >= 2){
                isCnt = false;
                break;
            }
            if(pre < cur){
                for(int cnt=0;cnt<L;cnt++){
                    if(j-1-cnt < 0 || mem[i][j-1-cnt].h != pre || mem[i][j-1-cnt].isAdd){
                        isCnt = false;
                        break;
                    }
                    mem[i][j-1-cnt].isAdd = true;
                }
            }
            else{
                for(int cnt=0;cnt<L;cnt++){
                    if(j+cnt >= N || mem[i][j+cnt].h != cur || mem[i][j+cnt].isAdd){
                        isCnt = false;
                        break;
                    }
                    mem[i][j+cnt].isAdd = true;
                }
            }
            if(!isCnt) break;
            pre = cur;
        }
        if(isCnt) ans++;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            mem[i][j].isAdd = false;
        }
    }

    for(int j=0;j<N;j++){
        //열에 대해서 확인.
        int pre = mem[0][j].h;
        bool isCnt = true;
        for(int i=1;i<N;i++){
            int cur = mem[i][j].h;
            if(cur == pre) continue;
            if(diff(pre, cur) >= 2){
                isCnt = false;
                break;
            }
            if(pre < cur){
                for(int cnt=0;cnt<L;cnt++){
                    if(i-1-cnt < 0 || mem[i-1-cnt][j].h != pre || mem[i-1-cnt][j].isAdd){
                        isCnt = false;
                        break;
                    }
                    mem[i-1-cnt][j].isAdd = true;
                }
            }
            else{
                for(int cnt=0;cnt<L;cnt++){
                    if(i+cnt >= N || mem[i+cnt][j].h != cur || mem[i+cnt][j].isAdd){
                        isCnt = false;
                        break;
                    }
                    mem[i+cnt][j].isAdd = true;
                }
            }
            if(!isCnt) break;
            pre = cur;
        }
        if(isCnt) ans++;
    }

    cout << ans << endl;
    return 0;
}