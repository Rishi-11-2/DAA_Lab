#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100
vector<int> t[4 * MAXN];
// brute force approach
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
// merging two sorted arrays in  segment function
vector<int> merge(vector<int> &left, vector<int> &right)
{
    int i = 0;
    int j = 0;
    int n1 = left.size();
    int n2 = right.size();
    vector<int> res;
    while (i < n1 && j < n2)
    {
        if (left[i] < right[j])
        {
            res.push_back(left[i]);
            i++;
        }
        else
        {
            res.push_back(right[j]);
            j++;
        }
    }
    while (i < n1)
    {
        res.push_back(left[i]);
        i++;
    }
    while (j < n2)
    {
        res.push_back(right[j]);
        j++;
    }
    return res;
}
// merge function of mergeSort
void mergeS(vector<pair<int, int>> &a, int low, int mid, int high)
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
    int i = 0;
    int j = 0;
    int k = low;
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
// merge sort on the basis of x-coordinate
void mergeSort(vector<pair<int, int>> &a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        mergeS(a, low, mid, high);
    }
}
// building the segment tree
void build(vector<int> &v, int si, int ss, int se)
{
    if (ss == se)
    {
        // cout << ss << endl;
        t[si] = vector<int>(1, v[ss]);
        return;
    }
    else
    {
        int mid = (ss + se) / 2;
        build(v, 2 * si + 1, ss, mid);
        build(v, 2 * si + 2, mid + 1, se);
        auto it1 = t[2 * si + 1];
        auto it2 = t[2 * si + 2];
        t[si] = merge(it1, it2);
    }
}
// querying on the segment tree for y coordinate
int query(int si, int ss, int se, int l, int r, int x)
{
    if (l > se || ss > r)
        return 0;
    int count = 0;
    if (l <= ss && r >= se)
    {
        auto it = lower_bound(t[si].begin(), t[si].end(), x);
        // cout << endl;
        count += it - t[si].begin();
        // cout << x << "  " << count << endl;
        return count;
    }
    int mid = (ss + se) / 2;
    return query(2 * si + 1, ss, mid, l, r, x) + query(2 * si + 2, mid + 1, se, l, r, x);
}
int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    vector<int> yc;
    vector<pair<int, int>> xc;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
        yc.push_back(y);
        xc.push_back({x, i});
    }
    bF(v, n);
    mergeSort(xc, 0, n - 1);
    int l = xc[0].second;
    int r = xc[0].second;
    vector<int> ans(n, 0);
    build(yc, 0, 0, n - 1);
    // cout << "hi" << endl;
    // for (auto it : t[0])
    // {
    //     cout << it << " ";
    // }
    // cout << endl;
    // for (auto it : t)
    // {
    //     for (auto i : it)
    //         cout << i << " ";
    //     cout << endl;
    // }
    // for (auto it : t)
    // {
    //     for (auto j : it)
    //         cout << j << " ";
    //     cout << endl;
    // }
    // finding the queries w.r.t to y-coordinates
    // First we sort the pairs of points on the basis of x-coordinates . After that
    // we find the the number of points which  will be greater w.r.t y using querying
    // from segment tree. What we basically do is that we find the number of points having
    // y-coordinate less than given y in the range(0,i). Then the answer to that particular index
    // will be min(i,query(ST)).
    // In segment tree we are basically storing the array in sorted fashion between every index range
    // after finding that particular range we just use binary search on the array at the given range
    // to find the number of elements havaing y-coordinate less than y in the given range
    for (int i = 0; i < n; i++)
    {
        int xx = query(0, 0, n - 1, l, r, v[xc[i].second].second);
        // cout << xx << endl;
        ans[xc[i].second] = min(i, xx);
        l = min(l, xc[i].second);
        r = max(r, xc[i].second);
        // cout << l << " " << r << endl;
    }

    for (auto it : ans)
        cout << it << " ";
    cout << endl;
}