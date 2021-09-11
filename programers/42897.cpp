#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> money) {

    //mem[0][0] 0번째를 훔침., mem[0][1] 0번째를 안훔침.
    vector<int> mem(money.size(), 0);
    int size = money.size();
    int answer = 0;
    mem[0] = money[0];
    mem[1] = max(money[0], money[1]);
    for(int i=2;i<size-1;i++){
        mem[i] = max(mem[i-1], mem[i-2] + money[i]);
    }
    answer = mem[size-2];

    fill_n(mem.begin(), money.size(), 0);
    mem[0] = 0;
    mem[1] = money[1];
    for(int i=2;i<size;i++){
        mem[i] = max(mem[i-1], mem[i-2] + money[i]);
    }
    answer = max(answer, mem[size-1]);

    return answer;
}

int main(){

    solution({1,2,3,1});
}