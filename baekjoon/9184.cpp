#include<iostream>
#include<cstdio>

using namespace std;

int mem[21][21][21] = {0};
bool visited[21][21][21] = {0};

int findMem(int a, int b, int c){
    if(a <= 0 || b <= 0 || c <= 0){
        return 1;
    }
    if(a>20 || b > 20 || c > 20 ){
        return findMem(20, 20, 20);
    }

    if(visited[a][b][c]){
        return mem[a][b][c];
    }

    int res = 0;
    if(a < b && b < c){
        res = findMem(a,b,c-1) + findMem(a,b-1, c-1) - findMem(a, b-1,c);
    }
    else{
        res = findMem(a-1,b,c) + findMem(a-1,b-1, c) + findMem(a-1, b,c-1) - findMem(a-1, b-1,c-1); 
    }
    visited[a][b][c] = true;
    mem[a][b][c] = res;
    return mem[a][b][c];
}

int main(){
    mem[0][0][0] = 1;
    while(true){
        int a, b,c;
        cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) break;
        int res = findMem(a,b,c);

        printf("w(%d, %d, %d) = %d\n", a,b,c,res);        
    }
    return 0;
}