#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

int solution(vector<int> a) {
    int answer = 0;
    vector<pair<int , int>> mem(a.size());
    //큰걸 터트릴 수 있음.
    int size = a.size();
    mem[0].first = a[0]+1;
    mem[size-1].second = a[size-1]+1;
    int tmp = a[0];
    for(int i=1;i<size;i++){
        tmp = min(tmp, a[i-1]);
        mem[i].first = tmp;
    }
    tmp = a[size-1];
    for(int i=size-2;i>=0;i--){
        tmp = min(tmp, a[i+1]);
        mem[i].second = tmp;
    }

    for(int i=0;i<size;i++){
        if ( a[i] < mem[i].first || a[i] < mem[i].second ) answer++;
    }
    return answer;
}