#include<iostream>
#include<string>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        string P,Q;
        cin >> P >> Q;
        
        char ans = 'Y';
        string nextP = P + "a";
        if(nextP == Q) ans = 'N';
        cout << "#" << test_case << " " << ans;
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}