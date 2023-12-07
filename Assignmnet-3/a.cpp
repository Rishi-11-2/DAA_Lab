#include <bits/stdc++.h>
using namespace std;

bool myCmp(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}
int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].first >> arr[i].second;
    }

    sort(arr, arr + n, myCmp);

    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i].first < arr[index].second)
        {
            arr[index].second=max(arr[index].second,)
        }
    }
}