#include <algorithm>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
int res = INT_MIN;
int rru, rrv;
int sum = 0;
int dfs(int u, vector<pair<int, int>> adj[], vector<int> &subtree, vector<int> &vis, map<pair<int, int>, int> mp, vector<int> &wv)
{
    vis[u] = 1;
    vector<pair<int, int>> xx;
    int s = 0;
    for (auto it : adj[u])
    {
        int v = it.first;
        if (vis[v] == 0)
        {
            subtree[v] = dfs(v, adj, subtree, vis, mp, wv);
            s += subtree[v];
        }
        xx.push_back({subtree[v], v});
    }
    // cout << "hi " << xx.size() << " " << u << endl;
    for (auto it : xx)
    {
        int v = it.second;
        // cout << v << " " << subtree[v] << endl;
        int as = mp[{u, v}] - abs(sum - 2 * subtree[v]);
        // cout << u << " " << v << " " << as << endl;
        if (as > res)                                                                                                                   
        {
            // cout << u << " " << v << " " << as << endl;
            res = as;
            rru = u;
            rrv = v;
        }
    }
    subtree[u] = s + wv[u];
    return subtree[u];
}
int dfsA(int u, vector<pair<int, int>> adj[], vector<int> &wv, vector<int> &vis, int b)
{
    int s = 0;
    vis[u] = 1;
    s += wv[u];
    for (auto it : adj[u])
    {
        if (it.first != b)
        {
            // cout << it.first << endl;
            if (vis[it.first] == 0)
            {
                s += dfsA(it.first, adj, wv, vis, b);
            }
        }
    }
    return s;
}
int main()
{
    int n;
    cin >> n;
    vector<int> wv(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> wv[i];
        sum += wv[i];
    }
    vector<pair<int, int>> adj[n + 1];
    vector<vector<int>> edges(n + 1);
    map<pair<int, int>, int> mp;
    for (int i = 1; i <= n - 1; i++)
    {
        int x, y, wt;
        cin >> x >> y >> wt;
        edges[i] = {x, y, wt};
        mp[{x, y}] = wt;
        mp[{y, x}] = wt;
        adj[x].push_back({y, wt});
        adj[y].push_back({x, wt});
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (auto it : adj[i])
    //     {
    //         cout << it.first << " ";
    //     }
    //     cout << endl;
    // }
    int ru;
    int rv;
    int minm = INT_MIN;
    for (int i = 1; i < n; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        vector<int> vis(n + 1, 0);
        int s1 = dfsA(u, adj, wv, vis, v);
        int s2 = dfsA(v, adj, wv, vis, u);
        // cout << s1 << " " << s2 << endl;
        int res = edges[i][2] - (abs(s1 - s2));
        if (minm < res)
        {
            minm = res;
            ru = u;
            rv = v;
        }
    }
    cout << "\nTHE EDGES FROM METHOD 1 IS -> ";
    cout << ru << " " << rv << endl;
    // cout << sum << endl;
    vector<int> vis(n + 1, 0);
    vector<int> subtree(n + 1, 0);
    int xyz = dfs(1, adj, subtree, vis, mp, wv);
    cout << "\nTHE EDGES FROM METHOD 2 IS -> ";
    cout << rru << " " << rrv << endl;
}
