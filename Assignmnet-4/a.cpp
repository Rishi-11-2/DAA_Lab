#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
bool isValid(vector<int> &count, int n)
{
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        a[count[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] != count[i])
            return false;
    }
    return true;
}
void solve(int i, int n, vector<int> &count)
{
    if (i == n - 1)
    {
        if (isValid(count, n))
        {
            for (int j = 0; j < n; j++)
                cout << count[j] << " ";
            cout << endl;
        }
        return;
    }
    int x = 0;
    int m = n;
    if (i == 0)
        x++;
    if (i != 0)
        m = n / i;
    for (int j = x; j <= m; j++)
    {
        count[i] = j;
        solve(i + 1, n, count);
        count[i] = 0;
    }
}
int main()
{
    int n;
    cin >> n;
    vector<int> count(n, 0);
    solve(0, n, count);
}