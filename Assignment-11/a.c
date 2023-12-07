#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000

int res = INT_MIN;
int rru, rrv;
int sum = 0;

typedef struct {
    int first;
    int second;
} Pair;

int dfs(int u, Pair adj[], int subtree[], int vis[], int mp[][MAX_N], int wv[]) {
    vis[u] = 1;
    Pair xx[MAX_N];
    int s = 0;
    int i = 0;
    for (i = 0; i < MAX_N; i++) {
        int v = adj[u][i].first;
        if (v == 0)
            break;
        if (vis[v] == 0) {
            subtree[v] = dfs(v, adj, subtree, vis, mp, wv);
            s += subtree[v];
        }
        xx[i].first = subtree[v];
        xx[i].second = v;
    }
    for (int j = 0; j < i; j++) {
        int v = xx[j].second;
        int as = mp[u][v] - abs(sum - 2 * subtree[v]);
        if (as > res) {
            res = as;
            rru = u;
            rrv = v;
        }
    }
    subtree[u] = s + wv[u];
    return subtree[u];
}

int dfsA(int u, Pair adj[], int wv[], int vis[], int b) {
    int s = 0;
    vis[u] = 1;
    s += wv[u];
    for (int i = 0; i < MAX_N; i++) {
        int v = adj[u][i].first;
        if (v == 0)
            break;
        if (v != b && vis[v] == 0) {
            s += dfsA(v, adj, wv, vis, b);
        }
    }
    return s;
}

int main() {
    int n;
    scanf("%d", &n);
    int* wv = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &wv[i]);
        sum += wv[i];
    }
    Pair* adj = (Pair*)malloc((n + 1) * MAX_N * sizeof(Pair));
    Pair* edges = (Pair*)malloc(n * sizeof(Pair));
    int mp[MAX_N][MAX_N] = {0};
    for (int i = 1; i <= n - 1; i++) {
        int x, y, wt;
        scanf("%d %d %d", &x, &y, &wt);
        edges[i].first = x;
        edges[i].second = y;
        mp[x][y] = wt;
        mp[y][x] = wt;
        int j;
        for (j = 0; adj[x][j].first != 0; j++);
        adj[x][j].first = y;
        adj[x][j].second = wt;
        for (j = 0; adj[y][j].first != 0; j++);
        adj[y][j].first = x;
        adj[y][j].second = wt;
    }

    int ru;
    int rv;
    int minm = INT_MIN;
    for (int i = 1; i < n; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        int* vis = (int*)calloc((n + 1), sizeof(int));
        int s1 = dfsA(u, adj, wv, vis, v);
        int s2 = dfsA(v, adj, wv, vis, u);
        int res = edges[i].second - (abs(s1 - s2));
        if (minm < res) {
            minm = res;
            ru = u;
            rv = v;
        }
        free(vis);
    }
    printf("\nTHE EDGES FROM METHOD 1 IS -> ");
    printf("%d %d\n", ru, rv);

    int* vis = (int*)calloc((n + 1), sizeof(int));
    int* subtree = (int*)malloc((n + 1) * sizeof(int));
    int xyz = dfs(1, adj, subtree, vis, mp, wv);
    printf("\nTHE EDGES FROM METHOD 2 IS -> ");
    printf("%d %d\n", rru, rrv);

    free(wv);
    free(adj);
    free(edges);
    free(vis);
    free(subtree);

    return 0;
}
