#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    if(n > s){
        answer.push_back(-1);
        return answer;
    }

    int div = s/n;
    if ( div * n == s){
        for(int i=0;i<n;i++){
            answer.push_back(div);
        }
        return answer;
    }
    else{
        int diff = s - div*n;
        for(int i=0;i<n-diff;i++){
            answer.push_back(div);
        }
        for(int i=0;i<diff;i++){
            answer.push_back(div+1);
        }
    }
    return answer;
}