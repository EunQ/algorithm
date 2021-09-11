#include <string>
#include <vector>
#include <stack>

using namespace std;

struct Node{
    int id;
    Node* nextNode;
    Node* preNode;
    bool vaild;
};

#include <iostream>

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    vector<Node> nodes(n);
    for(int i=1;i<n-1;i++){
        nodes[i].nextNode = &nodes[i+1];
        nodes[i].preNode = &nodes[i-1];
        nodes[i].id = i;
        nodes[i].vaild = true;
    }
    nodes[0].preNode = nullptr;
    nodes[0].nextNode = &nodes[1];
    nodes[0].id = 0;
    nodes[0].vaild = true;

    nodes[n-1].preNode = &nodes[n-2];
    nodes[n-1].nextNode = nullptr;
    nodes[n-1].id = n-1;
    nodes[n-1].vaild = true;

    Node* selectedNode = nullptr;
    selectedNode = &nodes[k];
    stack<Node*> delStack;

    for(auto c : cmd){
        if(c[0] == 'U'){
            int cnt = stoi(c.substr(2));
            for(int i=0;i<cnt;i++){
                selectedNode = selectedNode->preNode;
            }
            cout << selectedNode->id  << endl;
        }
        else if(c[0] == 'D'){
            int cnt = stoi(c.substr(2));
            for(int i=0;i<cnt;i++){
                selectedNode = selectedNode->nextNode;
            }
            cout << selectedNode->id  << endl;
        }
        else if(c[0] == 'C'){
            delStack.push(selectedNode);
            selectedNode->vaild = false;
            if(selectedNode->nextNode == nullptr){
                selectedNode = selectedNode->preNode;
                selectedNode->nextNode = nullptr;
            }
            else{
                Node* preNode = selectedNode->preNode;
                Node* nextNode = selectedNode->nextNode;
                if(preNode != nullptr){
                    preNode->nextNode = nextNode;
                }
                nextNode->preNode = preNode;
                selectedNode = nextNode;
            }
        }   
        else{
            Node* undoNode = delStack.top(); delStack.pop();
            undoNode->vaild = true;
            if(undoNode->nextNode != nullptr){
                undoNode->nextNode->preNode = undoNode;
            }
            if(undoNode->preNode != nullptr){
                undoNode->preNode->nextNode = undoNode;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(nodes[i].vaild){
            answer += 'O';
        }
        else answer += 'X';
    }
    return answer;
}

int main(){
    solution(8, 2, {"D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z"});
}