#include <string>
#include <vector>
#include <iostream>
using namespace std;
string getAns(int n){
    string res = "";
    while( n != 0){
        int tmp = n%3;
        n = n / 3;
        if(tmp == 0) 
        {
            n -= 1;
            tmp = 4;
        }
        res = to_string(tmp) + res;
    }
    //cout << res << endl;
    return res;
}

string solution(int n) {
    string answer = "";
    return answer = getAns(n);
}