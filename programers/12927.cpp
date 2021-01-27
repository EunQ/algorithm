#include <string>
#include <vector>
#include <queue>
using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> pq;
    int size = works.size();
    for(int i=0;i<size;i++){
        pq.push(works[i]);
    }

    for(int i=0;i<n;i++){
        if(works.size() == 0){
            break;
        }
        int top = pq.top();
        pq.pop();
        if(top-1 >= 1)
            pq.push(top-1);
    }

    size = pq.size();
    for(int i=0;i<size; i++){
        long long tmp = pq.top();
        pq.pop();
        tmp = tmp * tmp;
        answer += tmp;
    }

    return answer;
}

using namespace std;

int main(){

    priority_queue<int> a;
    a.push(1);
    a.push(2);

    cout << a.top() << endl;

    return 0;
}