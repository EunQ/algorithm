#include<iostream>
#include<vector>
#include<queue>


using namespace std;

int di[] = {-1,-1,0,1,1,1,0,-1};
int dj[] = {0,1,1,1,0,-1,-1,-1};
struct FireBall{
    int curI;
    int curJ;
    int m; //질량
    int s; //속력  칸 만큼 이동.
    int d; //방향  방향으로
};

int N,M,K;
int main(){

    cin >> N >> M >> K;
    queue<FireBall> fireballs;
    for(int i=0;i<M;i++){
        int r,c,m,s,d;
        cin >> r >> c >> m >> s >> d;
        fireballs.push({r-1,c-1,m,s,d});
    }
    for(int time=1;time<=K;time++){
        vector<vector<vector<int>>> visitedMap(N+1, vector<vector<int>> (N+1));
        vector<FireBall> list;
        int size = fireballs.size();
        if(size){
            for(int idx=1;idx<=size;idx++){
                FireBall curObject = fireballs.front();
                fireballs.pop();
                int nextI = (curObject.curI + di[curObject.d] * curObject.s  ) % N ;
                int nextJ = (curObject.curJ + dj[curObject.d] * curObject.s  ) % N ;
                while(nextI < 0) nextI += N;
                while(nextJ < 0) nextJ += N;
                curObject.curI = nextI;
                curObject.curJ = nextJ;

                //이동이 끝남.
                list.push_back(curObject);
                visitedMap[nextI][nextJ].push_back(list.size()-1);
            }

            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(visitedMap[i][j].size() == 1){
                        FireBall tmpObject = list[visitedMap[i][j][0]];
                        fireballs.push(tmpObject);
                    }
                    else if(visitedMap[i][j].size() >= 2){
                        FireBall sumObject = {0};
                        int oddNum = 0;
                        int evenNum  =0;
                        int sumCnt = visitedMap[i][j].size();
                        for(auto tmp : visitedMap[i][j]){
                            FireBall tmpObject = list[tmp];
                            sumObject.curI = tmpObject.curI;
                            sumObject.curJ = tmpObject.curJ;
                            sumObject.m += tmpObject.m;
                            sumObject.s += tmpObject.s;
                            sumObject.d += tmpObject.d;
                            if(tmpObject.d % 2 == 0) evenNum++;
                            else oddNum++;
                        }
                        sumObject.m /= 5;
                        sumObject.s /= visitedMap[i][j].size();
                        sumObject.d  = 1;
                        if(evenNum == sumCnt || oddNum == sumCnt){
                            sumObject.d  = 0;
                        }
                        if(sumObject.m != 0){
                            for(int nextD =sumObject.d; nextD < 8; nextD+=2){
                                fireballs.push({sumObject.curI, sumObject.curJ,
                                sumObject.m, sumObject.s, nextD});
                            }

                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    int size = fireballs.size();
    for(int idx = 0;idx< size; idx++){
        auto tmp = fireballs.front();
        fireballs.pop();
        ans += tmp.m;
    }
    cout << ans << endl;
    return 0;
}