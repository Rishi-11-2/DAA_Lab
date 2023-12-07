#include <iostream>
#include <bits/stdc++.h>
using namespace std;
bool isFeasible(string s)
{
    int count = 0;
    for (int i = 0; i < s.length() - 2; i++)
    {
        if (s[i] == 'x' && s[i + 1] == 'y' && s[i + 2] == 'z')
            count++;
    }
    if (count == 1)
        return 1;
    else
        return 0;
}
int search_exh(string s, int n, int i, string a)
{
    if (i == n)
    {
        return isFeasible(s);
    }

    int count = 0;
    for (int k = 0; k < 3; k++)
    {
        count += search_exh(s + a[k], n, i + 1, a);
    }
    return count;
}
long long search_exh_iterative(string s, int n, string a)
{
    long long count = 0;
    long long k = pow(3, n) * 1LL;
    for (long long i = 0; i < k; i++)
    {
        for (long long j = n - 1; j >= 0; j--)
        {
            long long x = pow(3, n - j - 1) * 1LL;
            long long y = i / x;
            y = y % 3;
            s[j] = a[y];
        }
        // cout << s << endl;
        count += isFeasible(s);
    }
    return count;
}
int ncr(int n, int r)
{
    int res = 1;
    for (int i = 0; i < r; i++)
    {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}
int count_P(int n)
{
    int arr[n];
    int x = 1;
    for (int i = 0; i <= n; i++)
    {
        arr[i] = x;
        x = x * 3;
    }
    int s[n];
    for (int i = 0; i <= (n - 3); i++)
    {
        s[i] = arr[i];
        int j = (i / 3);
        for (int k = 1; k <= j; k++)
        {
            s[i] += (pow(-1, k)) * ncr(i - 2 * k, k) * arr[i - 3 * k];
        }
    }
    int count = 0;
    for (int i = 0; i <= (n - 3); i++)
    {
        count += s[i] * s[n - i - 3];
    }
    return count;
}
int main()
{
    int n;
    cin >> n;
    string a = "xyz";
    int count = search_exh("", n, 0, a);
    string s = "";
    for (int i = 0; i < n; i++)
    {
        s += 'x';
    }
    long long count1 = search_exh_iterative(s, n, a);
    // int count1 = count_P(n);
    cout << count1 << endl;
}