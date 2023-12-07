#include <stdio.h>
#include <stdlib.h>
int solve(int n, int *memo)
{
    if (n < 0) // base case of recursion
        return 0;
    if (n == 0) // base case of recursion
        return 1;
    if (memo[n] != -1)
        return memo[n];
    return memo[n] = solve(n - 1, memo) + solve(n - 2, memo) + solve(n - 3, memo); // enumerating over all the possibilities
}
int solveM(int n, int memoM[21][21], int m, int j)
{
    if (n == 0) // base case of recursion
    {
        if (j == m) // base case of recursion
            return 1;
        else
            return 0;
    }
    if (memoM[n][j] != -1)  // checking the value was previously cached or not
        return memoM[n][j]; // returning the cached result
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        count += solveM(n - i, memoM, m, j + 1); // setting the value of j to check all the possibilities
    }
    return memoM[n][j] = count;
}

int main()
{
    int n;
    scanf("%d", &n);
    int a = 1;
    int b = 1;
    int c = 1;
    for (int i = 2; i <= n; i++)
    {
        int k = 0;
        k += a;
        k += b;
        if (i >= 3)
            k += c;
        a = b; // updating the value
        b = c; // updating the value
        c = k; // updating the value
    }
    printf("%d  \n", c);
    int *memo = (int *)(malloc((n + 1) * sizeof(int)));
    for (int i = 0; i <= n; i++)
        memo[i] = -1;
    int x = solve(n, memo); // enumerating over all the possibilities
    printf("%d \n", x);
    int m;
    scanf("%d", &m);
    int memoM[21][21];
    for (int i = 0; i <= 20; i++) // setting the value of j to check all the possibilities
    {
        for (int j = 0; j <= 20; j++)
        {
            memoM[i][j] = -1;
        }
    }
    int y = solveM(n, memoM, m, 0); // setting the value of j to check all the possibilities
    printf("%d\n", y);
    int res = 1;
    for (int i = 0; i < m; i++) // calcuating NcR in most efficient time
    {
        res = res * (n - i); // calcuating NcR in most efficient time
        res = res / (i + 1);
    }
    printf("%d\n", res); // printing out all the results
}