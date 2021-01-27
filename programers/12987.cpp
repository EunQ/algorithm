#include <string>
#include <vector>
#include <algorithm>


using namespace std;

int solution(vector<int> A, vector<int> B) {
    int aIdx = 0;
    int bIdx = 0;
    int answer = 0;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    while(bIdx < B.size() ){
        if(A[aIdx] < B[bIdx]){
            answer++;
            aIdx++;
            bIdx++;
        }
        else{
            bIdx++;
        }
    }
    return answer;
}