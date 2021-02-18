#include <string>
#include <vector>

using namespace std;

//60061 다시 풀기
bool isDeletPillar(int n, int curI, int curJ, vector<vector<int>> &map)
{

    if (map[curI + 1][curJ] & 2)
    {
        int beamCnt = -1;
        for (int i = -1; i <= 1; i++)
        {
            if (curJ + i <= n && curJ - i >= 0)
            {
                beamCnt++;
            }
        }
        if (beamCnt == 2)
            return true;
        if (curJ + 1 <= n && map[curI + 1][curJ + 1] & 2 && map[curI][curJ + 1] & 1)
        {
            return true;
        }
        if (curJ - 1 >= 0 && map[curI + 1][curJ - 1] & 2 && map[curI][curJ - 1] & 1)
        {
            return true;
        }

        return false;
    }

    return true;
}

bool isDeleteBeam(int n, int curI, int curJ, vector<vector<int>> &map)
{
    if (curI + 1 <= n && map[curI+1][curJ] & 1){
        if ( ! (map[curI][curJ] & 1)) return false;
    }

    //옆에 보가 있는 경우
    int beamCnt = -1;
    for(int i=-1;i<=1;i++){
        if(curJ + 1 > n || curJ-1 < 0) continue;
        if(map[curI][curJ+i] & 2) beamCnt++;
    }
    if (beamCnt == 2) return true;
    else if(beamCnt == 1){
        if (curJ+1 <= n && map[curI][curJ+1] & 2){
            if (!(map[curI-1][curJ] & 1) && !(map[curI-1][curJ+1] & 1)){
                return false;
            }
        }
        if (curJ-1 >= 0 && map[curI][curJ-1] & 2){
            if (!(map[curI-1][curJ] & 1) && !(map[curI-1][curJ-1] & 1)){
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame)
{
    vector<vector<int>> answer;
    vector<vector<int>> map(n + 1, vector<int>(n + 1, 0));
    //0는 기둥 1은 보
    //(1<< 0), (1<< 1);
    for (int i = 0; i < n; i++)
    {
        map[0][i] = 1;
    }
    for (auto inputData : build_frame)
    {
        int type = inputData[2];
        int curJ = inputData[0];
        int curI = inputData[1];
        int append = inputData[3];
        if (append)
        {
            //설치
            if (type == 0)
            {
                //기둥을 설치
                if (map[curI][curJ] & 1 || map[curI][curJ] & 2)
                {
                    map[curI + 1][curJ] |= 1;
                }
            }
            else
            {
                int isBuild = false;
                if (map[curI][curJ] & 1 || map[curI][curJ + 1] & 1)
                {
                    isBuild = true;
                }
                else if (map[curI][curJ] & 2 && map[curI][curJ + 1] & 2)
                {
                    isBuild = true;
                }
                if (isBuild)
                {
                    map[curI][curJ] |= 2;
                    map[curI][curJ + 1] |= 2;
                }
            }
        }
        else
        {
            //삭제
            bool isDelete = false;
            if (type == 0)
            {
                //기둥을 삭제
                //삭제 할려고 하는 윗부분에 보가 있는 경우.
                isDelete = isDeletPillar(n, curI, curJ, map);
                if(isDelete) map[curI+1][curJ] &= ~1;
            }
            else
            {
                //보를 삭제
                //위에 기둥이 있으면 아래쪽엔 기둥이 있어야 된다.
                isDelete = isDeleteBeam(n, curI, curJ, map);
            }
        }
    }

    return answer;
}