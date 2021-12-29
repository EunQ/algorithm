#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num = 0;
vector<int> dp;
int ans = 0;

int N, S;
void dfs(int idx, int tmpSum, int count, vector<int> &input, vector<bool> &visited)
{
    if (idx >= input.size())
    {
        if (tmpSum == S && count > 0)
        {
            ans += 1;
        }
        return;
    }
    visited[idx] = true;
    dfs(idx + 1, tmpSum + input[idx], count + 1, input, visited);
    visited[idx] = false;
    dfs(idx + 1, tmpSum, count, input, visited);
}

int main()
{
    cin >> N >> S;
    vector<int> input(N);
    vector<bool> visited(N);
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> input[i];
    }
    sort(input.begin(), input.end());
    dfs(0, 0, 0, input, visited);

    cout << ans << endl;
    return 0;
}