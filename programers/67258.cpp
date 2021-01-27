#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer(2);
    int size = gems.size();
    answer[0] = 1; answer[1] = size;
    map<string, int> gem_map;
    int max_count = 0;
    for(int i=0;i<size;i++){
        gem_map[gems[i]] = 1;
    }
    max_count = gem_map.size();

    for(int start=0;start <size - max_count;start++){
        gem_map.clear();
        for(int mid = start;mid < max_count + start;mid++){
            gem_map[gems[mid]]++;
        }
        int count = gem_map.size();
        if(count == max_count){
            if(max_count < answer[1] - answer[0] ){
                answer[0] = start + 1;
                answer[1] = start + max_count;
                return answer;
            }
            break;
        }
        for(int end = max_count + start;end < size; end++){
            gem_map[gems[end]]++;
            if(gem_map.size() == max_count){
                if(end - start <= answer[1] - answer[0]){
                    if( (end-start < answer[1] - answer[0]) || 
                       (start + 1 < answer[0]) ){
                        answer[0] = start+1;
                        answer[1] = end + 1;
                    }
                }
                break;
            }
        }
    }
    return answer;
}

int main(){

    auto res = solution({"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"});

    return 0;
}