#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer(2);
    answer[0] = 1;
    answer[1] = gems.size();
    int ans_len = gems.size();
 
    map<string, int> gem_map;
    int max_count = 0;
    int size = gems.size();
    for(int i=0;i<size;i++){
        if(gem_map[gems[i]] == 0){
            max_count++;
            gem_map[gems[i]] = 1;
        }
    }
    gem_map.clear();

    int count = 0;
    int start = 0, end = 0;
    while(start < size){
        if(count == max_count || end == size){
            if(count == max_count){
                //결과가 같은 경우.
                if(end - start < ans_len){
                    ans_len = end - start;
                    answer[0] = start+1;
                    answer[1] = end;
                }
                else if(  ((end - start) == ans_len) &&
                    (start+1 < answer[0]) ){
                        answer[0] = start+1;
                        answer[1] = end;
                    }
            }
            gem_map[gems[start]]--;
            if(gem_map[gems[start]] == 0){
                count--;
            }
            start++;
        }
        else{
            gem_map[gems[end]]++;
            if(gem_map[gems[end]] == 1){
                count++;
            }
            end++;
        }
    }

    return answer;
}