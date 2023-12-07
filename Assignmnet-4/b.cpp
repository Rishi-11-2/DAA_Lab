#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] += dp[i - 1];
        dp[i] += dp[i - 2];
        if (i >= 3)
            dp[i] += dp[i - 3];
    }
    cout << dp[n] << endl;
}