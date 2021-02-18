#include <string>
#include <vector>

using namespace std;

void hanoi(vector<vector<int>> &answer, int n, int start, int mid, int end){
    if(n == 1) {
        answer.push_back({start, end});
        return;
    }
    hanoi(answer, n-1, start, end, mid);
    answer.push_back({start, end});
    hanoi(answer, n-1, mid, start, end);
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    hanoi(answer, n, 1,2,3);
    return answer;
}