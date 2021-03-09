#include<iostream>
#include<vector>
using namespace std;

void printTest(int n, vector<vector<int>> vec){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << vec[i][j] ;
        }
        cout << endl;
    }
    cout << endl;
}

void test(int n, vector<vector<int>> vec){

    
    vector<vector<int>> tmp3(n, vector<int> (n));    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tmp3[j][n-i-1] = vec[i][j];
        }
    }
    printTest(n, tmp3);
    
    vector<vector<int>> tmp1(n, vector<int> (n));    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tmp1[n-i-1][n-j-1] = vec[i][j];
        }
    }
    printTest(n, tmp1);

    vector<vector<int>> tmp2(n, vector<int> (n));    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tmp2[n-j-1][i] = vec[i][j];
        }
    }
    printTest(n, tmp2);

}

int main(){

    printTest(3, {{0,0,0},{1,0,0},{0,1,1}});
    test(3, {{0,0,0},{1,0,0},{0,1,1}});
}