#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getTotalMin(string tmp){
    int hour = 0;
    hour += tmp[0] - '0';
    hour *= 10;
    hour += tmp[1] - '0';
    int min = 0;
    min += tmp[3] - '0';
    min *= 10;
    min += tmp[4] - '0';
    return hour*60+min;
}

string getAns(int totalMin){
    int hour = totalMin / 60;
    int min = totalMin % 60;
    char tmpAns[6] = {0};
    sprintf(tmpAns, "%02d:%02d", hour,min);
    return string(tmpAns);
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    int ansTotalMin = 0;
    int startMin = 9*60;
    vector<int> timeVec;
    for(string tmp : timetable){
        timeVec.push_back(getTotalMin(tmp));
    }
    sort(timeVec.begin(), timeVec.end());
    int timeVecIdx = 0;
    for(int i=0;i<n;i++){
        int cnt = 0;
        for(;timeVecIdx<timeVec.size();timeVecIdx++){
            if(timeVec[timeVecIdx] > startMin) break;
            cnt++;
            if(cnt == m) break;
        }
        if(cnt < m) ansTotalMin = max(startMin, ansTotalMin);
        else {
            ansTotalMin = max(ansTotalMin, timeVec[timeVecIdx]-1);
            timeVecIdx++;
        }
        startMin += t;
    }
    answer = getAns(ansTotalMin);
    return answer;
}
