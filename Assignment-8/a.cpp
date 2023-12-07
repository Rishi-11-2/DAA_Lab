#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
struct result
{
    int minm;
    int maxm;
    int amount;
    int sellingD;
    int buyingD;
};
typedef struct result Result;
int combine(int low, int mid, int high, vector<int> &b, vector<int> &s, int c)
{
    int minm = INT_MAX;
    int maxm = 0;
    int minD = INT_MAX;
    int maxD = 0;
    for (int i = low; i <= mid; i++)
    {

        if (minm > b[i])
        {
            minm = b[i];
            minD = i;
        }
    }
    for (int i = mid; i <= high; i++)
    {

        if (s[i] > maxm)
        {
            maxm = s[i];
        }
    }
    int x = ceil((c / minm) * 1.0);
    int res = (maxm - minm) * x;
    // cout << maxm << " " << minm << "  " << res << endl;
    return res;
}
int singletrans1(int low, int high, vector<int> &b, vector<int> &s, int c)
{
    int res = 0;
    if (low < high)
    {
        int mid = (low + high) / 2;
        int a1 = singletrans1(low, mid, b, s, c);
        int a2 = singletrans1(mid + 1, high, b, s, c);
        int a3 = combine(low, mid, high, b, s, c);
        res = max(a1, max(a2, a3));
    }
    return res;
}
int combine2(int low, int mid, int high, vector<int> &b, vector<int> &s, int c, Result a1, Result a2)
{
    int minm = a1.minm;
    int maxm = a2.maxm;

    int x = ceil((c / minm) * 1.0);
    int res = (maxm - minm) * x;
    // cout << maxm << " " << minm << "  " << res << " " << low << " " << mid << " " << high << endl;
    return res;
}
Result singletrans2(int low, int high, vector<int> &b, vector<int> &s, int c)
{
    Result res;
    if (low == high)
    {
        res.minm = b[low];
        res.maxm = s[high];
        int minm = res.minm;
        int maxm = res.maxm;
        int x = ceil((c / minm) * 1.0);
        int amount = (maxm - minm) * x;
        res.amount = amount;
        res.buyingD = low + 1;
        res.sellingD = low + 1;
        return res;
    }
    Result a3;
    if (low < high)
    {
        int mid = (low + high) / 2;
        Result a1 = singletrans2(low, mid, b, s, c);
        Result a2 = singletrans2(mid + 1, high, b, s, c);
        int sD = -1;
        int bD = -1;
        int maxt = 0;
        maxt = max(a1.amount, a2.amount);
        if (a1.amount > a2.amount)
        {
            bD = a1.buyingD;
            sD = a1.sellingD;
        }
        else
        {
            bD = a2.buyingD;
            sD = a2.sellingD;
        }
        a3.amount = combine2(low, mid, high, b, s, c, a1, a2);
        if (a3.amount > maxt)
        {
            bD = a1.buyingD;
            sD = a2.sellingD;
        }
        a3.buyingD = bD;
        a3.sellingD = sD;
        a3.amount = max(a1.amount, max(a2.amount, a3.amount));
        a3.minm = min(a2.minm, a1.minm);
        a3.maxm = max(a1.maxm, a2.maxm);
    }
    return a3;
}
void printHistory(vector<int> b, vector<int> s, int c, vector<int> maxCapital, vector<int> buyIdx, vector<int> sellIdx, int idx)
{
    int i = buyIdx[idx];
    int j = sellIdx[idx];
    if (i == -1)
    {
        return;
    }
    printHistory(b, s, c, maxCapital, buyIdx, sellIdx, i);
    c += ((s[idx] - b[idx]) * (maxCapital[idx] / b[idx]));
    printf("    Buying  date = %2d, Buying  rate = %2d\n", i, b[i]);
    printf("    Selling date = %2d, Selling rate = %2d\n", j, s[j]);
    printf("    Current capital = %d\n\n", c);
}
void multiT(int n, vector<int> b, vector<int> s, int c)
{
    vector<int> maxCapital(n + 1, 0);
    vector<int> sellIdx(n + 1, 0);
    vector<int> buyIdx(n + 1, 0);

    maxCapital[0] = 0;
    buyIdx[0] = -1;
    sellIdx[0] = -1;

    maxCapital[0] = c;
    for (int i = 1; i <= n; i++)
    {
        maxCapital[i] = maxCapital[i - 1];
        buyIdx[i] = buyIdx[i - 1];
        sellIdx[i] = sellIdx[i - 1];
        int maxidx = i - 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (s[j] >= s[maxidx])
            {
                maxidx = j;
            }
            int thiscap = maxCapital[j] + (s[maxidx] - b[j]) * (maxCapital[j] / b[j]);
            if (thiscap > maxCapital[i])
            {
                maxCapital[i] = thiscap;
                buyIdx[i] = j;
                sellIdx[i] = maxidx;
            }
        }
    }
    printHistory(b, s, c, maxCapital, buyIdx, sellIdx, n);
    printf("    Maximum profit = %d\n", maxCapital[n] - c);
}
int main()
{
    int n;
    scanf("%d", &n);
    vector<int> b(n + 1, 0);
    vector<int> s(n + 1, 0);
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n; i++)
        cin >> s[i];
    int c;
    cin >> c;
    int a = singletrans1(0, n - 1, b, s, c);
    cout << a << endl;
    Result bb = singletrans2(0, n - 1, b, s, c);
    cout << bb.amount << " " << bb.buyingD << " " << bb.sellingD << endl;

    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    multiT(n, b, s, c);
}