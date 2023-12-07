#include <stdio.h>
#include <stdlib.h>
int **RO(int **orders, int n, int k)
{
    int **ordersR = (int **)(malloc(k * sizeof(int *)));
    for (int i = 0; i < k; i++)
    {
        int sz = 0;
        for (int j = 0; j < n; j++)
        {
            if (orders[i][j] != 0)
                sz++;
        }
        ordersR[i] = (int *)(malloc((sz + 1) * sizeof(int)));
        int idx = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            if (orders[i][j] != 0)
            {
                ordersR[i][idx] = orders[i][j];
                idx++;
            }
        }
    }
    return ordersR;
}
void mergeS(int *a, int low, int mid, int high)
{

    int n1 = mid - low + 1;
    int n2 = high - mid;
    int *left = (int *)(malloc((n1) * sizeof(int)));
    int *right = (int *)(malloc((n2) * sizeof(int)));
    for (int i = 0; i < n1; i++)
    {
        left[i] = a[low + i];
        // printf("ho\n");
        // printf("%d ", left[i].first);
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = a[mid + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {

        if (left[i] > right[j])
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
void mergeSort(int *a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        mergeS(a, low, mid, high);
    }
}
void solveA(int n, int k, int *t)
{
    int **orders = (int **)(malloc(k * sizeof(int *)));
    int **preOrders = (int **)(malloc(k * sizeof(int *)));
    int *indices = (int *)(malloc(k * sizeof(int)));
    for (int i = 0; i < k; i++)
    {
        indices[i] = -1;
        orders[i] = (int *)(malloc(n * sizeof(int)));
        preOrders[i] = (int *)(malloc(n * sizeof(int)));
        for (int j = 0; j < n; j++)
        {
            orders[i][j] = 0;
            preOrders[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < k; j++)
        {
            // printf("hi");
            if (indices[j] == -1)
            {
                indices[j]++;
                orders[j][indices[j]] = t[i];
                preOrders[j][indices[j]] = t[i];
                // indices[j]++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int idx = -1;
            int maxm = (int)(1100);
            for (int j = 0; j < k; j++)
            {
                // printf("hi");
                if (preOrders[j][indices[j]] < maxm)
                {
                    maxm = preOrders[j][indices[j]];
                    idx = j;
                }
            }
            indices[idx]++;
            orders[idx][indices[idx]] = t[i];
            preOrders[idx][indices[idx]] = orders[idx][indices[idx]] + preOrders[idx][indices[idx] - 1];
            // indices[idx]++;
        }
        // printf("\n");
    }
    int maxm = 0;
    int s = 0;
    for (int i = 0; i < k; i++)
    {
        int x = 0;
        for (int j = 0; j < n; j++)
        {
            if (orders[i][j] != 0)
                printf("%d ", orders[i][j]);
            if (preOrders[i][j] > maxm)
                maxm = preOrders[i][j];
            if (preOrders[i][j] > x)
                x = preOrders[i][j];
        }
        for (int j = 0; j < n; j++)
        {
            if (preOrders[i][j] != x)
                s += preOrders[i][j];
        }
        printf("\n");
    }
    printf("The Cafe Closes at->%d \n", maxm);
    printf("The Waiting Time is ->%d \n", s);
}
int **solveB(int n, int k, int *t)
{
    int **orders = (int **)(malloc(k * sizeof(int *)));
    int **preOrders = (int **)(malloc(k * sizeof(int *)));
    int *indices = (int *)(malloc(k * sizeof(int)));
    for (int i = 0; i < k; i++)
    {
        indices[i] = -1;
        orders[i] = (int *)(malloc(n * sizeof(int)));
        preOrders[i] = (int *)(malloc(n * sizeof(int)));
        for (int j = 0; j < n; j++)
        {
            orders[i][j] = 0;
            preOrders[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < k; j++)
        {
            // printf("hi");
            if (indices[j] == -1)
            {
                indices[j]++;
                orders[j][indices[j]] = t[i];
                preOrders[j][indices[j]] = t[i];
                // indices[j]++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int idx = -1;
            int maxm = (int)(1100);
            for (int j = 0; j < k; j++)
            {
                // printf("hi");
                if (preOrders[j][indices[j]] < maxm)
                {
                    maxm = preOrders[j][indices[j]];
                    idx = j;
                }
            }
            indices[idx]++;
            orders[idx][indices[idx]] = t[i];
            preOrders[idx][indices[idx]] = orders[idx][indices[idx]] + preOrders[idx][indices[idx] - 1];
            // indices[idx]++;
        }
        // printf("\n");
    }
    int maxm = 0;
    int s = 0;
    for (int i = 0; i < k; i++)
    {
        int x = 0;
        for (int j = 0; j < n; j++)
        {
            if (orders[i][j] != 0)
                printf("%d ", orders[i][j]);
            if (preOrders[i][j] > maxm)
                maxm = preOrders[i][j];
            if (preOrders[i][j] > x)
                x = preOrders[i][j];
        }
        for (int j = 0; j < n; j++)
        {
            if (preOrders[i][j] != x)
                s += preOrders[i][j];
        }
        printf("\n");
    }
    printf("The Cafe Closes at->%d \n", maxm);
    printf("The Waiting Time is ->%d \n", s);
    int **ordersR = RO(orders, n, k);
    return ordersR;
}

void solveC(int **orders, int n, int k, int *t)
{
    int **preOrders = (int **)(malloc(k * sizeof(int *)));
    int *indices = (int *)(malloc(k * sizeof(int)));
    for (int i = 0; i < k; i++)
    {
        indices[i] = -1;
        preOrders[i] = (int *)(malloc(n * sizeof(int)));
        for (int j = 0; j < n; j++)
        {
            preOrders[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < k; j++)
        {
            // printf("hi");
            if (indices[j] == -1)
            {
                indices[j]++;
                preOrders[j][indices[j]] = orders[j][indices[j]];
                // indices[j]++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int idx = -1;
            int maxm = (int)(1100);
            for (int j = 0; j < k; j++)
            {
                // printf("hi");
                if (preOrders[j][indices[j]] < maxm)
                {
                    maxm = preOrders[j][indices[j]];
                    idx = j;
                }
            }
            indices[idx]++;
            preOrders[idx][indices[idx]] = orders[idx][indices[idx]] + preOrders[idx][indices[idx] - 1];
            // indices[idx]++;
        }
        // printf("\n");
    }
    int maxm = 0;
    int s = 0;
    for (int i = 0; i < k; i++)
    {
        int x = 0;
        int sz = sizeof(orders[i]) / sizeof(orders[i][0]);
        for (int j = 0; j <= sz; j++)
        {
            if (orders[i][j] != 0)
                printf("%d ", orders[i][j]);
            if (preOrders[i][j] > maxm)
                maxm = preOrders[i][j];
            if (preOrders[i][j] > x)
                x = preOrders[i][j];
        }
        for (int j = 0; j <= sz; j++)
        {
            if (preOrders[i][j] != x)
                s += preOrders[i][j];
        }
        printf("\n");
    }
    printf("The Cafe Closes at->%d \n", maxm);
    printf("The Waiting Time is ->%d \n", s);
}
int main()
{
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int *t = (int *)(malloc(n * sizeof(int)));
    printf("Enter The Times->\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t[i]);
    }
    solveA(n, k, t);
    mergeSort(t, 0, n - 1);
    int **ordersR = solveB(n, k, t);
    solveC(ordersR, n, k, t);
}