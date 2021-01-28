#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
struct Data
{
    int num;
    int count;

    bool operator < (const Data& b){
        return count > b.count;
    }
};
#include <map>

using namespace std;

int solution(std::vector<int> a) {
    int answer = -1;
    map<int, int> db;
    vector<Data> dataVector;
    for(int i=0;i<a.size();i++){
        auto& tmp = db[a[i]];
        if(tmp == 0){
            tmp = 1;
        }   
        else{
            tmp++;
        }
    }
    for(auto tmp : db){
        dataVector.push_back({tmp.first, tmp.second });
    }
    sort(dataVector.begin(), dataVector.end());

    answer = 0;
    for(auto tmp : dataVector){
        vector<bool> visitedVector(a.size(), 0);
        if(answer >= tmp.count){
            break;
        }
        int number = tmp.num;
        int curIdx = 0;
        int tmpAns = 0;
        while(curIdx < a.size()){
            if(a[curIdx] == number && visitedVector[curIdx] != 1){
                visitedVector[curIdx] = 1;
                if(curIdx -1 >= 0 && a[curIdx-1] != number && !visitedVector[curIdx-1]){
                    visitedVector[curIdx-1] = 1;
                    tmpAns+=2;
                }
                else if(curIdx + 1 < a.size() && a[curIdx+1] != number && !visitedVector[curIdx+1]){
                    visitedVector[curIdx+1] = 1;
                    tmpAns+=2;
                }
            }
            curIdx++;
        }
        answer = tmpAns > answer ? tmpAns : answer;
    }

    if(answer == 2) answer = 0;
    return answer;
}
