
#include <string>
#include <algorithm>
using namespace std;
int solution(string s)
{
    int answer=1;

    for(int i=0;i<s.size();i++){
        int tmpAns = 1;
        // odd length
        for(int j=1;i-j >= 0 && i+j < s.size() ;j++){
            if (s[i-j] == s[i+j]) tmpAns+=2;
            else break;
        }
        answer = max(answer, tmpAns);

        int k = 0;
        tmpAns = 0;
        // even length
        for(int j=i, k=j+1; j >= 0 && k < s.size() ; j--,k++){
            if (s[j] == s[k] ) tmpAns+=2;
            else break;
        }
        answer = max(answer, tmpAns);
    }


    return answer;
}


#include <iostream>
int main(){

    int ans = solution("aaaa");

    cout << ans << endl;
    return 0;
}