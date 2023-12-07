#include <stdio.h>
#include <stdlib.h>

#include <time.h>
// representing intervals in form of structs
struct interval
{
    float start;
    float end;
};

typedef struct interval I;

I *getIntervals(int n)
{
    I *intervals = (I *)(malloc(n * (sizeof(I)))); // defining array of structs

    srand(time(0)); // using randomness

    for (int i = 0; i < n; i++)
    {
        float ed = ((float)rand() / (RAND_MAX));      // getting the endpoint of an interval
        float st = ((float)rand() / (RAND_MAX / ed)); // getting the startpoint of an interval using random function
        intervals[i].start = st;
        intervals[i].end = ed;
    }
    return intervals;
}
void merge(I *arr, int l, int mid, int r) // merging two sorted parts of an array
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    I *left = (I *)(malloc(n1 * (sizeof(I))));  // declaring a left array of structs
    I *right = (I *)(malloc(n2 * (sizeof(I)))); // declaring a right array of structs

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        // sorting by their start times
        if (left[i].start < right[j].start || (left[i].start == right[j].start && left[i].end < right[j].end))
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) // performing the logic for merge operations in merge sort
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}
// performing merge sort operations to sort the array of structs by their start time
void mergeSort(I *arr, int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    I *arr = getIntervals(n);
    // printing the intervals as generated by the random function
    for (int i = 0; i < n; i++)
    {
        printf("Start:  %lf End: %lf \n", arr[i].start, arr[i].end);
    }
    mergeSort(arr, 0, n - 1);
    // printing the sorted array of structs
    printf("The Sorted is \n");
    for (int i = 0; i < n; i++)
    {
        printf("Start:  %lf End: %lf \n", arr[i].start, arr[i].end);
    }

    int i = 0;
    int j = 1;
    int res = 1;
    float minEnd = arr[i].end;
    float maxStart = arr[i].start;
    float rs = 0;
    float re = 0;
    // implementing the revelant logic
    while (j < n)
    {
        while (i < j && arr[j].start > arr[i].end)
        {
            i++;
        }
        int count = j - i + 1;
        if (j < n && count > res)
        {
            res = count;
            printf("%lf %lf\n", arr[j].start, minEnd);
            rs = arr[j].start;
            re = minEnd;
            minEnd = arr[j].end;
        }

        if (minEnd > arr[j].end)
            minEnd = arr[j].end;
        j++;
    }
    // printing the answer
    printf("%d\n", res);
    printf("%lf   %lf\n", rs, re);
}