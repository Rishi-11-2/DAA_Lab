#include <iostream>
#include <vector>
using namespace std;
void bF(vector<pair<int, int>> &v, int n)
{
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (v[i].first > v[j].first && v[i].second > v[j].second)
            {
                ans[i]++;
            }
        }
    }
    for (auto it : ans)
    {
        cout << it << " ";
    }
    cout << endl;
}
int countAndMerge(int idx, int y, vector<pair<int, int>> &b, int l, int mid, int r, vector<int> &vis)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    vector<pair<int, int>> left(n1);
    vector<pair<int, int>> right(n2);
    for (int i = 0; i < n1; i++)
        left[i] = b[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = b[mid + 1 + i];
    int i = 0;
    int j = 0;
    int k = l;
    int count = 0;
    while (i < n1 && j < n2)
    {
        if (left[i].first < right[j].first)
        {
            b[k] = left[i];
            if (left[i].first < y && left[i].second < idx && vis[left[i].second] == 0)
            {
                count++;
                vis[left[i].second] = 1;
            }
            i++;
        }
        else
        {
            b[k] = right[j];
            if (right[j].first < y && right[j].second < idx && vis[right[j].second] == 0)
            {
                count++;
                vis[right[j].second] = 1;
            }
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        if (left[i].first < y && left[i].second < idx)
            count++;
        b[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        if (right[j].first < y && right[j].second < idx)
            count++;
        b[k] = right[j];
        j++;
        k++;
    }
    return count;
}
int count(int idx, int y, vector<pair<int, int>> &b, int l, int r, vector<int> &vis)
{
    int x = 0;
    if (l < r)
    {
        int mid = (l + r) / 2;
        x += count(idx, y, b, l, mid, vis);
        x += count(idx, y, b, mid + 1, r, vis);
        x += countAndMerge(idx, y, b, l, mid, r, vis);
    }
    return x;
}
vector<int> ans;
void merge(vector<pair<int, int>> &a, vector<pair<int, int>> b, vector<pair<int, int>> &v, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    vector<pair<int, int>> left(n1);
    vector<pair<int, int>> right(n2);
    for (int i = 0; i < n1; i++)
    {
        left[i] = a[low + i];
    }
    for (int i = 0; i < n2; i++)
        right[i] = a[mid + 1 + i];
    int i = n1 - 1;
    int j = n2 - 1;
    int k = low;
    while (i >= 0 && j >= 0)
    {
        if (right[j].first > left[i].first)
        {
            int n = (int)(v.size());
            vector<int> vis(n, 0);
            int countY = count(right[j].second, v[right[j].second].second, b, 0, n - 1, vis);
            int cc = i + 1;
            // cout << right[j].second << " " << v[right[j].second].second << " " << cc << " " << countY << endl;
            ans[right[j].second] += min(cc, countY);
            j--;
        }
        else
        {
            int n = (int)(v.size());
            vector<int> vis(n, 0);
            int countY = count(left[i].second, v[left[i].second].second, b, 0, n - 1, vis);
            int cc = j + 1;
            // cout << left[i].second << " " << v[left[i].second].second << " " << cc << " " << countY << endl;
            ans[left[i].second] += min(cc, countY);
            i--;
        }
    }
    i = 0;
    j = 0;
    while (i < n1 && j < n2)
    {
        if (left[i].first < right[j].first)
        {
            a[k] = left[i];
            i++;
        }
        else
        {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        a[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        a[k] = right[j];
        j++;
        k++;
    }
}
void mergeSort(vector<pair<int, int>> &a, vector<pair<int, int>> b, vector<pair<int, int>> &v, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, b, v, low, mid);
        mergeSort(a, b, v, mid + 1, high);
        merge(a, b, v, low, mid, high);
    }
}
int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    bF(v, n);
    vector<pair<int, int>> a(n);
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = {v[i].first, i};
        b[i] = {v[i].second, i};
    }
    int low = 0;
    ans.resize(n, 0);
    int high = n - 1;
    mergeSort(a, b, v, low, high);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << a[i].first << " " << a[i].second << endl;
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << ans[i] << " ";
    // }
    bF(v, n);
    cout << endl;
}