#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Pair{
    int first;
    int second;
} pair;
void displace(int *a,int *b)
{
    int dis=(rand()%4);
    // int dis1=dis;
    int dis1=(dis+rand()%4)%4;
    int *c=(int *)(malloc((4)*sizeof(int)));
    int *d=(int *)(malloc((4)*sizeof(int)));
    int k1=0;
    int k2=0;
    for(int i=dis1;i<4;i++)
    {
        c[k1++]=a[i];
        d[k2++]=b[i];
    }
    for(int i=0;i<dis1;i++)
    {
        c[k1++]=a[i];
        d[k2++]=b[i];
    }
    for(int i=0;i<4;i++)
    {
        a[i]=c[i];
        b[i]=d[i];
    }
}
void displayB(int m,int n,int **h,int **v,char**grid)
{
    printf(" ");
    for(int j=0;j<n;j++)
    {
        printf("--- ");
    }
    printf("\n");
    for(int i=0;i<m;i++)
    {
        printf("|  ");
        for(int j=0;j<n;j++)
        {
            char c=' ';
            if(grid[i][j]=='*')
            {
                c='*';
            }
            if(h[i][j]==1)
            {
               printf("%c|  ",c);
            }
            else
            {
               printf("%c   ",c);
            }
        }
        // printf("|   ");
        printf("\n");
        printf(" ");
        for(int j=0;j<n;j++)
        {
            if(v[i][j]==1)
            {
               printf("--- ");
            }
            else
            {
               printf("    ");
            }
        }
        printf("\n");
    }
}
int dfsBhul(int i,int j,int m,int n,int **h,int **v,int **vis,pair **p)
{
    vis[i][j]=1;
    // printf("%d %d\n",i,j);
    int a[]={1,0,-1,0};
    int b[]={0,1,0,-1};
    int flag=0;
    for(int k=0;k<4;k++)
    {
        // int d=(rand()%4);
        int x=i+a[k];
        int y=j+b[k];
        if(x>=0 && y>=0 && x<m && y<n)
        {
            if(vis[x][y]==0)
            flag=1;
        }
    }
    if(flag==0)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(vis[i][j]==0)
                return 0;
            }
        }
        return 1;
    }
    displace(a,b);
    for(int d=0;d<4;d++)
    { 
        // int d1=(d)%4;
        int x=i+a[d];
        int y=j+b[d];
        if(x>=0 && y>=0 && x<m && y<n)
        {
            if(vis[x][y]==0)
            {
                vis[x][y]=1;
                if(j-y==1)
                {
                    h[x][y]=0;
                }
                else if(y-j==1)
                {
                    h[i][j]=0;
                }
                else if(x-i==1)
                {
                    v[i][j]=0;
                }
                else if(i-x==1)
                {
                    v[x][y]=0;
                }
                p[x][y].first=i;
                p[x][y].second=j;
                int res=dfsBhul(x,y,m,n,h,v,vis,p);
                if(res==1)
                return 1;
                // vis[x][y]=0;
                // if(j-y==1)
                // {
                //     h[x][y]=1;
                // }
                // else if(y-j==1)
                // {
                //     h[i][j]=1;
                // }
                // else if(x-i==1)
                // {
                //     v[i][j]=1;
                // }
                // else if(i-x==1)
                // {
                //     v[x][y]=1;
                // }
            }
        }
    }
    return 0;
}
void findRani(int i,int j,char **grid,pair**p)
{
    if(grid[i][j]=='*')
    {
        grid[i][j]='/';
    }
    else if(grid[i][j]=='/'){
        grid[i][j]='*';
    }
    int pi=p[i][j].first;
    int pj=p[i][j].second;
    if(i==pi && j==pj)
    return ;
    findRani(pi,pj,grid,p);
}
int main()
{
    srand((time(NULL)));
    int n,m;
    scanf("%d %d",&m,&n);
    int **h=(int**)(malloc((m)*sizeof(int*)));
    int **v=(int**)(malloc((m)*sizeof(int*)));
    printf("Initializing The Horizontal Walls ->\n");
    for(int i=0;i<m;i++)
    {
        h[i]=(int *)(malloc((n)*sizeof(int)));
        for(int j=0;j<n;j++)
        {
            h[i][j]=1;
        }
    }
    printf("Initializing The Vertical Walls ->\n");
    for(int i=0;i<m;i++)
    {
        v[i]=(int *)(malloc((n)*sizeof(int)));
        for(int j=0;j<n;j++)
        {
            v[i][j]=1;
        }
    }
    pair **p=(pair **)(malloc((m+1)*sizeof(pair*)));
    for(int i=0;i<m;i++)
    {
        p[i]=(pair*)(malloc((n+1)*sizeof(pair)));
        for(int j=0;j<n;j++)
        {
            p[i][j].first=-1;
            p[i][j].second=-1;
        }
    }
     char **grid=(char**)(malloc((m+1)*sizeof(char*)));
    for(int i=0;i<m;i++)
    {
        grid[i]=(char *)(malloc((n+1)*sizeof(char)));
        for(int j=0;j<n;j++)
        {
            grid[i][j]='/';
        }
    }
    displayB(m,n,h,v,grid);
    int **vis=(int **)(malloc((m+1)*sizeof(int*)));
    for(int i=0;i<m;i++)
    {
        vis[i]=(int*)(malloc((n+1)*sizeof(int)));
    }
    printf("\n After DFS \n");
    p[0][0].first=0;
    p[0][0].second=0;
    int a=dfsBhul(0,0,m,n,h,v,vis,p);
    displayB(m,n,h,v,grid);
    int s1=rand()%m;
    int s2=rand()%n;
    int t1=rand()%m;
    int t2=rand()%n;
    printf("The Source Cell is ->%d %d \n",s1,s2);
    printf("The Target Cell is ->%d %d \n",t1,t2);
   
    findRani(s1,s2,grid,p);
    findRani(t1,t2,grid,p);
    grid[s1][s2]='*';
    grid[t1][t2]='*';
    //  for(int i=0;i<m;i++)
    // {
    //     for(int j=0;j<n;j++)
    //     {
    //         printf("%c ",grid[i][j]);
    //     }
    //     printf("\n");
    // }
    displayB(m,n,h,v,grid);

}