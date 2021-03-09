#include <string>
#include <vector>
using namespace std;

//다시 풀기.
bool isLower(char c){
    if('a'<= c && c <= 'z') return true;
    return false;
}

string solution(string sentence) {
    string answer = "";
    int size = sentence.size();
    vector<int> startAlpha(26, -1);
    vector<int> endAlpha(26, -1);
    vector<int> cntAlpha(26, 0);
    vector<int> sentenceSpace(size );
    vector<int> sentenceCnt(size);

    for(int i=0;i<sentence.size();i++){
        char c = sentence[i];
        if(!isLower(c)) continue;
        int cidx = c-'a';
        cntAlpha[cidx]++;
        if(startAlpha[cidx] == -1) startAlpha[cidx] = i;
        if(startAlpha[cidx] != -1) endAlpha[cidx] = i;
    }
    
    for(int i = 0 ; i < size; ){
        char c = sentence[i];
        if(cntAlpha[c] == 2){
            //first case aAAAAa
            // 1 == space 
            sentenceSpace[startAlpha[c]] = 1;
            sentenceSpace[endAlpha[c]] = 1;
            for(int i=startAlpha[c]+1;i<=endAlpha[c]-1;i++){
                if(!isLower(sentence[i])) sentenceCnt[i]++;
            }
            if(isLower(sentence[i+2]) && c != sentence[i+2]){

            }
            i += endAlpha[c]+1;
        }   
        else if(cntAlpha[c] >= 1){
            //second case AaAaA
            for(int i=startAlpha[c];i<=endAlpha[c];i+=2){
                // 2 != space
                sentenceSpace[i] = 2;
            }
            for(int i=startAlpha[c]-1;i<=endAlpha[c]+1 ;i+=2){
                if(i >= size) return "invalid";
                sentenceCnt[i]++;
            }
            
            i += endAlpha[c]+2;
        } 
    }
    
    for(int i=0;i<size;i++) {
        if(!isLower(sentence[i]) && sentenceCnt[i] >= 2) return "invalid";
    }

    bool isPreSpace = true;
    for(int i=0;i<size;i++){
        char c = sentence[i];
        if(sentenceSpace[i] == 1 && !isPreSpace && i != sentence.size()-1){
            isPreSpace = true;
            answer += ' ';
        }
        if(isLower(c)) continue;
        if(sentenceCnt[i] == 0 && !isPreSpace){
            isPreSpace = ' ';
            answer += ' ';
        }
        if(sentenceSpace[i] == 0){
            isPreSpace = false;
            answer += c;
        }

    }
    
    return answer;
}


#include <iostream>
int main(){

    auto ans = solution("aAazAbAbAz");
    cout << ans << endl;
    return 0;
}
