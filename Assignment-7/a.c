#include <stdio.h>
#include <stdlib.h>
int solve(int *arr, int n, int i, int sum, int target, int **dp, int x)
{
    if (i == n)
    {
        if (sum == target)
        {
            return 1;
        }
        else
            return 0;
    }
    if (dp[i][sum + x] != -1)
        return dp[i][sum + x];
    int s1 = sum + arr[i];
    int s2 = sum - arr[i];
    int ans = solve(arr, n, i + 1, s1, target, dp, x) || solve(arr, n, i + 1, s2, target, dp, x);
    return dp[i][sum + x] = ans;
}
int solveOne(int *arr, int n, int i, int sum, int target, int **dp, int x, int *c, int j, int flag)
{
    if (i == n)
    {
        // printf("hi");
        if (sum == target)
        {
            for (int k = 0; k < 2 * n; k += 2)
            {
                char r = c[k] + '0';
                printf("%c ", r);
                printf("%d ", c[k + 1]);
            }
            printf("\n");

            return 1;
        }
        else
            return 0;
    }
    if (dp[i][sum + x] != -1)
        return dp[i][sum + x];
    int s1 = sum + arr[i];
    int s2 = sum - arr[i];
    c[j] = ('+' - '0');
    c[j + 1] = (arr[i]);
    int x1 = solveOne(arr, n, i + 1, s1, target, dp, x, c, j + 2, flag);
    c[j] = ('-' - '0');
    c[j + 1] = (arr[i]);
    int x2 = solveOne(arr, n, i + 1, s2, target, dp, x, c, j + 2, flag);
    int ans = x1 || x2;
    return dp[i][sum + x] = ans;
}
void solveALL(int *arr, int n, int i, int sum, int target, int **dp, int x, int *d, int j)
{
    if (i == n)
    {
        // printf("%d\n", sum);
        if (sum == target)
        {
            // printf("hi\n");
            for (int k = 0; k < 2 * n; k += 2)
            {
                char r = d[k] + '0';
                printf("%c ", r);
                printf("%d ", d[k + 1]);
            }
            printf("\n");
            return;
        }
        return;
    }
    if (dp[i][sum + x] == 0)
    {
        return;
    }
    int s1 = sum + arr[i];
    int s2 = sum - arr[i];
    d[j] = ('+' - '0');
    d[j + 1] = (arr[i]);
    // printf("%d %d \n", s1, s2);
    solveALL(arr, n, i + 1, s1, target, dp, x, d, j + 2);
    d[j] = ('-' - '0');
    solveALL(arr, n, i + 1, s2, target, dp, x, d, j + 2);
    return;
}
int main()
{
    int n;
    scanf("%d", &n);
    int *arr = (int *)(malloc((n + 1) * sizeof(int)));
    int s1 = 0;
    int s2 = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        s1 -= arr[i];
        s2 += arr[i];
    }
    int target;
    scanf("%d", &target);
    int x = abs(s1);
    int t = x + s2 + 1;
    int **dp = (int **)(malloc((n + 1) * sizeof(int *)));
    for (int i = 0; i <= n; i++)
    {
        dp[i] = (int *)(malloc((t) * sizeof(int)));
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < t; j++)
        {
            dp[i][j] = -1;
        }
    }
    int aa = solve(arr, n, 0, 0, target, dp, x);
    if (aa == 1)
        printf("YES\n");
    else
        printf("NO\n");

    int *c = (int *)(malloc((2 * n + 1) * sizeof(int)));
    int *d = (int *)(malloc((2 * n + 1) * sizeof(int)));
    for (int i = 0; i <= 2 * n; i++)
        d[i] = 0;
    solveALL(arr, n, 0, 0, target, dp, x, d, 0);
}