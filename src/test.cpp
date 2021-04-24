#include<iostream>

using namespace std;

int visited[6];
int ans = 0;
void permu(int cnt){
    if(cnt == 3){
        ans++;
        for(int i=1;i<=5;i++){
            if(visited[i]){
                cout << i << ",  ";
            }
        }
        cout << endl;
        return;
    }
    for(int i=1;i<=5;i++){
        if(!visited[i]){

            visited[i] = true;
            permu(cnt+1);
            visited[i] = false;
        }
    }
    return;
}

void combi(int cnt, int idx){
    if(cnt == 3){
        ans++;
        for(int i=1;i<=5;i++){
            if(visited[i]){
                cout << i << ",  ";
            }
        }
        cout << endl;
        return;
    }
    for(int i=idx;i<=5;i++){
        visited[i] = true;
        combi(cnt+1, i+1);
        visited[i] = false;
    }
}

int main(){
    permu(0);
    cout << ans << endl;
    ans = 0;
    combi(0, 1);
    cout << ans << endl;
    return 0;
}