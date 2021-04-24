#include<iostream>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

int r,c,k;
int A[102][101][101];
int ans = 101;
struct Num{
    int num;
    int cnt;
    bool operator< (Num& another){
        if(cnt == another.cnt){
            return num < another.num;
        }
        return cnt < another.cnt;
    }
};

void dfs(int cnt, int row, int col){
    if(cnt >= 101){
        return;
    }
    if(A[cnt][r][c] == k){
        ans = min(ans, cnt);
        return;
    }

    /*
    for(int i=1;i<=max(row,col);i++){
        for(int j=1;j<=max(row,col);j++){
            cout << A[cnt][i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */

    if(row >= col){
        int maxCol = 0;
        for(int i=1;i<=row;i++){
            map<int, int> cntMap;
            vector<Num> sortedList;
            for(int j=1;j<=row;j++){
                if(A[cnt][i][j]){
                    cntMap[A[cnt][i][j]] += 1;
                }
            }
            for(auto tmp : cntMap){
                sortedList.push_back({tmp.first, tmp.second});
            }
            sort(sortedList.begin(), sortedList.end());
            int size = sortedList.size();
            int minCol = min(100, size*2);
            maxCol = max(minCol, maxCol);
            int nextIdx = 0;
            for(int j=1;j<=minCol;j+=2){
                A[cnt+1][i][j] = sortedList[nextIdx].num;
                A[cnt+1][i][j+1] = sortedList[nextIdx].cnt;
                nextIdx++;
            }
        }
        dfs(cnt+1, row, maxCol);
    }
    else{
        int maxRow = 0;
        for(int j=1;j<=col;j++){
            map<int, int> cntMap;
            vector<Num> sortedList;
            for(int i=1;i<=col;i++){
                if(A[cnt][i][j]){
                    cntMap[A[cnt][i][j]] += 1;
                }
            }
            for(auto tmp : cntMap){
                sortedList.push_back({tmp.first, tmp.second});
            }
            sort(sortedList.begin(), sortedList.end());
            int size = sortedList.size();
            int minRow = min(100, size*2);
            maxRow = max(minRow, maxRow);
            int nextIdx = 0;
            for(int i=1;i<=minRow;i+=2){
                A[cnt+1][i][j] = sortedList[nextIdx].num;
                A[cnt+1][i+1][j] = sortedList[nextIdx].cnt;
                nextIdx++;
            }
        }
        dfs(cnt+1, maxRow, col);
    }

}

int main(){

    cin >> r >> c >> k;

    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cin >> A[0][i][j];
        }
    }
    

    dfs(0, 3, 3);
    if(ans >= 101) ans = -1;
    cout << ans << endl;
    return 0;
}