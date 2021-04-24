#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N;
int A[21][21];
int ans = 40000;
int main(){
    cin >> N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            int tmp;
            cin >> tmp;
            A[i][j] = tmp;
        }
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            //pick x,y;

            for(int d1=1;d1<=N;d1++){
                //pick d1;
                for(int d2=1;d2<=N;d2++){
                    //pick d2;
                    if( !(i + d1 <= N && j - d1 >= 1)) continue;
                    if( !(i + d2 <= N && j + d2 <= N)) continue;
                    if( !(i + d1 + d2 <= N && j - d1 + d2)) continue;
                    if( !(i + d2 + d1 <= N && j + d2 - d1)) continue;
                    vector<vector<int>> idxMap(N+1, vector<int>(N+1));
                    for(int cnt = 0;cnt <= d1;cnt++){
                        idxMap[i+cnt][j-cnt] = 5;
                    }
                    for(int cnt = 0;cnt <= d2;cnt++){
                        idxMap[i+cnt][j+cnt] = 5;
                    }
                    for(int cnt = 0;cnt <= d2;cnt++){
                        idxMap[i+d1+cnt][j-d1+cnt] = 5;
                    }
                    for(int cnt = 0;cnt <= d1;cnt++){
                        idxMap[i+d2+cnt][j+d2-cnt] = 5;
                    }
                    vector<int> cntList(6);
                    
                    for(int curRow=1;curRow<=N;curRow++){
                        vector<int> idxList;
                        for(int curCol = 1;curCol <=N;curCol++){
                            if(idxMap[curRow][curCol] == 5){
                                idxList.push_back(curCol);
                            }
                        }
                        if(idxList.size() >= 2){
                            for(int curCol = idxList[0];curCol <=idxList[1];curCol++){
                                idxMap[curRow][curCol] = 5;
                            }
                        }
                    }
                    
                    for(int curRow=1;curRow<=N;curRow++){
                        for(int curCol = 1;curCol <=N;curCol++){
                            if(idxMap[curRow][curCol] == 5){
                                cntList[5] += A[curRow][curCol];
                                idxMap[curRow][curCol] = 5;
                                continue;
                            }
                            if(1<= curRow && curRow <  i + d1 && 1<= curCol && curCol <= j ) {
                                cntList[1] += A[curRow][curCol];
                                idxMap[curRow][curCol] = 1;
                            }
                            else if(1<= curRow && curRow <= i + d2 && j<  curCol && curCol <= N ) {
                                cntList[2] += A[curRow][curCol];
                                idxMap[curRow][curCol] = 2;
                            }
                            else if(i+d1<= curRow && curRow <=  N && 1<= curCol && curCol < j-d1+d2 ) {
                                cntList[3] += A[curRow][curCol];
                                idxMap[curRow][curCol] = 3;
                            }
                            else {
                                cntList[4] += A[curRow][curCol];
                                idxMap[curRow][curCol] = 4;
                            }
                        }
                    }
                    /*
                    for(int curRow=1;curRow<=N;curRow++){
                        for(int curCol = 1;curCol <=N;curCol++){
                            cout << idxMap[curRow][curCol] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    */
                    sort(cntList.begin(), cntList.end());
                    int tmpAns = cntList[5] - cntList[1];
                    ans = min(ans, tmpAns); 
                }
            }
        }
    }

    cout << ans << endl;
}