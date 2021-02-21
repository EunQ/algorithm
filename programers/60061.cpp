#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Space{
    bool pillar;
    bool beam;
};

struct Ans{
    int x,y,type;

    bool operator< (const Ans &b){
        if(x == b.x){
            if(y == b.y){
                return type < b.type;
            }
            return y < b.y;
        }
        return x < b.x;
    }
};

bool isBuildPiller(int n, int curI, int curJ, vector<vector<Space>> &map){
    bool isBuild = false;
    if(curI == 0){
        //바닥일 경우.
        isBuild = true;
    }
    else{
        //다른 기둥 위에 설치되거나.
        if(map[curI-1][curJ].pillar) isBuild = true;
        //다른 보 위에 설치.
        if(map[curI][curJ].beam || (curJ - 1 >= 0 & map[curI][curJ-1].beam)) isBuild = true;
    }
    return isBuild;
}

bool isBuildBeam(int n, int curI, int curJ, vector<vector<Space>> &map){

    bool isBuild = false;    
    //만약 아래에 기둥이 있다면 보를 설치.
    if(curI - 1 >= 0){
        if(map[curI-1][curJ].pillar) isBuild = true;
        if(map[curI-1][curJ+1].pillar) isBuild = true;
    }

    //양 옆에 보가 있으면 설치.
    if(curJ - 1 >= 0 && curJ + 1 <= n && map[curI][curJ-1].beam && map[curI][curJ+1].beam) isBuild = true;

    return isBuild;
}

//뺄 때 단순하게 생각. 나머지 전체가 올바르게 설치 되는지 확인한다.
bool isDeleteFunc(int n, int curI, int curJ, vector<vector<Space>> &map){
    bool isDelete = true;
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(map[i][j].pillar){
                if(!isBuildPiller(n, i, j, map)) return false;
            }
            if(map[i][j].beam){
                if(!isBuildBeam(n, i, j, map)) return false;
            }
        }
    }

    return isDelete;
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame)
{
    vector<vector<int>> answer;
    vector<vector<Space>> map(n + 1, vector<Space>(n + 1, {false,false}));
    //0는 기둥 1은 보
    
    for (auto inputData : build_frame)
    {
        int type = inputData[2];
        int curJ = inputData[0];
        int curI = inputData[1];
        int append = inputData[3];
        
        if (append)
        {
            //설치
            
            bool isBuild = false;
            if (type == 0)
            {
                //기둥을 설치
                isBuild = isBuildPiller(n, curI, curJ, map);
                if(isBuild) map[curI][curJ].pillar = true;
            }
            else
            {
                //보를 설치.
                isBuild = isBuildBeam (n, curI, curJ, map);
                if(isBuild) map[curI][curJ].beam = true;
            }
        }
        else
        {
            //삭제
            bool isDelete = false;
            if (type == 0)
            {
                //기둥을 삭제
                map[curI][curJ].pillar = false;
                isDelete = isDeleteFunc(n, curI, curJ, map);
                if(!isDelete) map[curI][curJ].pillar = true;
            }
            else
            {
                //보를 삭제
                map[curI][curJ].beam = false;
                isDelete = isDeleteFunc(n, curI, curJ, map);
                if(!isDelete) map[curI][curJ].beam = true;

            }
        }
    }

    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(map[i][j].pillar){
                answer.push_back({j,i,0});
            }
            if(map[i][j].beam){
                answer.push_back({j,i,1});
            }
        }
    }
    sort(answer.begin(), answer.end());

    return answer;
}
