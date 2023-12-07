#include <stdlib.h>
#include <stdio.h>
#define MAXN 100
int *t[4 * MAXN];
typedef struct
{
    int first;
    int second;
} Cord;
// brute force approach
int bS(int a[], int x)
{
    int n = sizeof(a) / sizeof(a[0]);
    int low = 0;
    int high = n - 1;
    int res = 0;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (x < a[mid])
        {
            high = mid;
        }
        else
            low = mid + 1;
    }

    // if (low < n && a[low] < x)
    //     low++;
    return low;
}
void bF(Cord *v, int n)
{
    int *ans = (int *)(malloc((n) * (sizeof(int))));
    for (int i = 0; i < n; i++)
        ans[i] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if ((v[i].first >= v[j].first) && (v[i].second >= v[j].second))
            {
                ans[i]++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
    }
    // printf("j");
    printf("\n");
}
// merging two sorted arrays in  segment function
int *merge(int *left, int *right)
{
    int i = 0;
    int j = 0;
    int n1 = sizeof(left) / sizeof(left[0]);
    int n2 = sizeof(right) / sizeof(right[0]);
    int *res = (int *)(malloc((n1 + n2) * sizeof(int)));
    int k = 0;
    while (i < n1 && j < n2)
    {
        if (left[i] < right[j])
        {
            res[k] = left[i];
            i++;
        }
        else
        {
            res[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        res[k] = left[i];
        k++;
        i++;
    }
    while (j < n2)
    {
        res[k] = right[j];
        k++;
        j++;
    }
    return res;
}
// merge function of mergeSort
void mergeS(Cord a[], int low, int mid, int high)
{

    int n1 = mid - low + 1;
    int n2 = high - mid;
    Cord *left = (Cord *)(malloc((n1) * sizeof(Cord)));
    Cord *right = (Cord *)(malloc((n2) * sizeof(Cord)));
    for (int i = 0; i < n1; i++)
    {
        left[i].first = a[low + i].first;
        // printf("ho\n");
        left[i].second = a[low + i].second;
        // printf("%d ", left[i].first);
    }
    for (int i = 0; i < n2; i++)
    {
        right[i].first = a[mid + 1 + i].first;
        right[i].second = a[mid + 1 + i].second;
    }
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {

        if (left[i].first < right[j].first)
        {
            a[k].first = left[i].first;
            a[k].second = left[i].second;
            i++;
        }
        else
        {
            a[k].first = right[j].first;
            a[k].second = right[j].second;
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k].first = left[i].first;
        a[k].second = left[i].second;
        i++;
        k++;
    }
    while (j < n2)
    {
        a[k].first = right[j].first;
        a[k].second = right[j].second;
        j++;
        k++;
    }
}
// merge sort on the basis of x-coordinate
void mergeSort(Cord *a, int low, int high)
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
void build(int *v, int si, int ss, int se)
{
    if (ss == se)
    {
        // cout << ss << endl;
        t[si] = (int *)malloc(1 * sizeof(int));
        t[si][0] = v[ss];
        return;
    }
    else
    {
        int mid = (ss + se) / 2;
        build(v, 2 * si + 1, ss, mid);
        build(v, 2 * si + 2, mid + 1, se);
        t[si] = merge(t[2 * si + 1], t[2 * si + 2]);
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
        count = bS(t[si], x);
        // cout << endl;
        // cout << x << "  " << count << endl;
        return count;
    }
    int mid = (ss + se) / 2;
    return query(2 * si + 1, ss, mid, l, r, x) + query(2 * si + 2, mid + 1, se, l, r, x);
}
int main()
{
    int n;
    scanf("%d", &n);
    Cord *v = (Cord *)(malloc((n) * (sizeof(Cord))));
    int *yc = (int *)(malloc((n) * (sizeof(int))));
    Cord *xc = (Cord *)(malloc((n) * (sizeof(Cord))));
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        // printf("%d %d ", x, y);
        yc[i] = y;
        xc[i].first = x;
        xc[i].second = i;
        v[i].first = x;
        v[i].second = y;
    }
    bF(v, n);
    mergeSort(xc, 0, n - 1);
    int l = xc[0].second;
    int r = xc[0].second;
    int *ans = (int *)(malloc((n) * sizeof(int)));
    build(yc, 0, 0, n - 1);
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
        int t = i;
        if (t > xx)
            t = xx;
        ans[xc[i].second] = t;
        if (l > xc[i].second)
            l = xc[i].second;
        if (r < xc[i].second)
            r = xc[i].second;
        // cout << l << " " << r << endl;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");
}