#include <string>
#include <vector>
#include <cstdio>
using namespace std;

struct Video{
    int startSec;
    int runningSec;
};

int getSec(int hour, int min, int sec){
    return hour*60*60 + min * 60 + sec;
}

int parseString(string a){
    // "xx:xx:xx" 형식으로 되어 있는 경우.
    int hour = 0;
    int min = 0;
    int sec = 0;
    sscanf(a.c_str(),"%d:%d:%d", &hour, &min, &sec);
    int totalSec = getSec(hour, min, sec);
    return totalSec;
}

string parseSec(int totalSec){
    int hour = totalSec / 3600;
    int tmp = totalSec % 3600;
    int min = tmp / 60;
    int sec = tmp % 60;
    char resBuf[10] = {0};
    sprintf(resBuf, "%02d:%02d:%02d", hour, min, sec);
    string res(resBuf);
    return res;
}
#include <iostream>
string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    vector<int> timeDB(60*60*100, 0);
    int playTime = parseString(play_time);
    int advTime = parseString(adv_time);
    for(auto log : logs){
        string start = log.substr(0, 8);
        string end = log.substr(9);
        int startSec = parseString(start);
        int endSec = parseString(end);
        for(int i=startSec;i<endSec;i++){
            timeDB[i]++;
        }
    }
    long long ans = 0;
    for(int i=0;i<advTime;i++){
        ans += timeDB[i];
    }
    answer = parseSec(0);
    long long curSum = ans;
    for(int i=1;i<=playTime-advTime;i++){
        curSum -= timeDB[i-1];
        curSum += timeDB[i+advTime-1];
        if (curSum > ans){
            answer = parseSec(i);
            ans = curSum;
        }
    }
    return answer;
}
