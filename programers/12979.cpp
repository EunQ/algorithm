#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int prePos = 1;
    int div = w*2+1;
    int last = stations[stations.size()-1];
    stations.push_back(last + w + 1);
    for(int stationPos : stations){
        int part = stationPos - w - prePos ;
        if (part > 0){
            answer += part / div;
            if(part % div) answer++;
        }
        prePos = stationPos + w + 1;
        if(prePos >= n) break;
    }
    

    return answer;
}
