#include <stdio.h>
#include <stdlib.h>
int isValid(int *count, int n)
{
    int *a = (int *)(malloc((n + 1) * sizeof(int))); // declaring an array of size n
    // for (int i = 0; i < n; i++)
    //     a[i] = 0;
    for (int i = 0; i < n; i++)
    {
        a[count[i]]++; // counting the number of digits in a number
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] != count[i]) // checking whether the number is valid or not
            return 0;
    }
    return 1;
}
void solve(int i, int n, int *count)
{
    if (i == n - 1) // base case of recursion
    {
        if (isValid(count, n)) // checking whether the current count array is valid or not
        {
            for (int j = 0; j < n; j++)
            {
                if (count[j] <= 9) // printing the array
                    printf("%d ", count[j]);
                else
                {
                    int x = count[j] - 10;
                    char c = (char)(x + 'A'); // printing the characters if digits are greater than 10
                    printf("%c ", c);
                }
            }
            printf("\n");
        }
        return;
    }
    int x = 0;
    int m = n; // initializing the maximum number of possibilities a number can have
    if (i == 0)
        x++;
    if (i > 4)
        m = 1;
    else if (i > 0 && i <= 4)
        m = (n / i);
    for (int j = x; j <= m; j++)
    {
        count[i] = j;           // setting the value of j to check all the possibilities
        solve(i + 1, n, count); // enumerating over all the possibilities
        count[i] = 0;           // preparing the value of count[i]=0
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        printf("The Answer for %d->\n", i);
        int *count = (int *)(malloc((i + 1) * sizeof(int)));
        solve(0, i, count);
        printf("\n");
    }
}