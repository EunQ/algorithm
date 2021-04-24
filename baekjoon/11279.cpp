#include<iostream>
#include<queue>
using namespace std;
#define endl '\n'
struct Num{
    int val;
    bool operator< (const Num& other) const{
        return val < other.val;
    }
};

int main(){
    int N;
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    priority_queue<Num> pq;
    cin >> N;
    for(int n=0;n<N;n++){
        int cmd = 0;
        cin >> cmd;
        if(cmd == 0){
            if(pq.empty()){
                cout << "0" << endl;
            }
            else{
                int minVal = pq.top().val;
                pq.pop();
                cout << minVal << endl;
            }
        }
        else{
            pq.push({cmd});
        }
    }
    return 0;
}