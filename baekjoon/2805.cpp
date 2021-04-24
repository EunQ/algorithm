#include<iostream>
#include<algorithm>

using namespace std;
int N;
int M;
long long trees[1000000];
int ans;
void binary(int left, int right)
{
    if(left > right) return ;
    int height = (right + left) / 2;
    long long res = 0;
    for(int i=0;i<N;i++){
        if(trees[i] - height >= 0){
            res += trees[i] - height;
        }
    }
    if(res >= M){
        ans = max(ans, height);
        binary(height+1,right );
    }
    else{
        //height를 낮춘다.
        binary(left, height-1);
    }
}
int main(){
    cin >> N >> M;
    for(int i=0;i<N;i++){
        cin >> trees[i];
    }
    binary(0, 1000000000);

    cout << ans << endl;

    return 0;
}