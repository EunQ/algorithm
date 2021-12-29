#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Core
{
    int cost;
    int index;
    bool operator<(const Core &a) const
    {
        if (cost == a.cost)
            return index > a.index;
        return cost > a.cost;
    }
};

int solution(int n, vector<int> cores)
{
    int answer = 0;
    priority_queue<Core> corePQ;
    priority_queue<Core> runCorePQ;

    for (int i = 0; i < cores.size(); i++)
    {
        int core = cores[i];
        corePQ.push({core, i});
    }

    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (corePQ.size() == 0)
        {
            auto runCore = runCorePQ.top();
            runCorePQ.pop();
            time = max(time, runCore.cost);
            corePQ.push({cores[runCore.index], runCore.index});
        }
        auto core = corePQ.top();
        corePQ.pop();
        runCorePQ.push({time + cores[core.index], core.index});
        answer = core.index + 1;
    }

    return answer;
}