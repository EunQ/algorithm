#include<iostream>
using namespace std;

int di[] = {0,1,1,1,0,-1,-1,-1};
int dj[] = {-1,-1,0,1,1,1,0,-1};
int mem[50][50];
int main(){

    int N;
    int d = 0;
    cin >> N;
    int len = 1;
    int curI, curJ;
    curI = N/2;
    curJ = N/2;
    while(true){
        cout << "--------------" << endl;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(curI == i && curJ == j){
                    cout << "*" << " ";
                }
                else
                cout << mem[i][j] << " ";
            }
            cout << endl;
        }
        if(curI == 0 && curJ == 0)
            break;
        for(int i=0;i<len;i++){
            curI += di[d];
            curJ += dj[d];
        }
        d += 2;
        d %= 8;
        if(d == 0 || d == 4){
            len++;
        }
    }
    return 0;
}