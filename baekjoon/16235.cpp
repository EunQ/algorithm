#include<iostream>
#include<vector>
#include<algorithm>
//11:28 시작

using namespace std;
int N, M, K;
vector<int> trees[10][10];
int addFoods[10][10];
int resFoods[10][10];
int deadTree[10][10];

bool isBound(int i, int j){
    if(0<=i && i < N && 0<= j && j < N) return true;
    return false;
}

int di[] = {0,0,1,-1,-1,1,1,-1};
int dj[] = {1,-1,0,0,1,1,-1,-1};

int main(){

    cin >> N >> M >> K;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            resFoods[i][j] = 5;
            cin >> addFoods[i][j];
        }
    }

    for(int m=0;m<M;m++){
        int x,y,z;
        cin >> x >> y >> z;
        trees[x-1][y-1].push_back(z);
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            sort(trees[i][j].begin(), trees[i][j].end());
        }
    }

    for(int k=1;k<=K;k++){
        //봄
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                vector<int> newTrees;
                deadTree[i][j] = 0;
                int size = trees[i][j].size();
                for(int idx=0;idx<size;idx++){
                    int age = trees[i][j][idx];
                    if(resFoods[i][j] - age >= 0){
                        resFoods[i][j] -= age;
                        newTrees.push_back(age+1);
                    }
                    else{
                        deadTree[i][j] += (age/2);
                    }
                }
                trees[i][j] = newTrees;
            }
        }

        //여름
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                resFoods[i][j] += deadTree[i][j];
            }
        }

        //가을
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                int size = trees[i][j].size();
                for(int idx=0;idx<size;idx++){
                    int age = trees[i][j][idx];
                    if(age % 5 == 0){
                        for(int d=0;d<8;d++){
                            int nextI = i + di[d];
                            int nextJ = j + dj[d];
                            if(isBound(nextI, nextJ)){
                                trees[nextI][nextJ].push_back(1);
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                sort(trees[i][j].begin(), trees[i][j].end());
            }
        }

        //겨울
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                resFoods[i][j] += addFoods[i][j];
            }
        }
    }

    int ans = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            ans += trees[i][j].size();
        }
    }

    cout << ans << endl;

    return 0;
}