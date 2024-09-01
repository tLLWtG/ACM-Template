#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'
#define debug(x) { cerr << #x << " = " << x << endl; }

/*-------------------------------------------*/

// g 是原图，g2 是反图

#define MAXN 100005

vector<bool> vis(MAXN);
vector<int> color(MAXN), s;
int n, sccCnt;

vector<vector<int>> g(MAXN), g2(MAXN);

// g2 is the converse digraph of g

void dfs1(int u)
{
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v])
            dfs1(v);
    s.push_back(u);
}

void dfs2(int u)
{
    color[u] = sccCnt;
    for (int v : g2[u])
        if (!color[v])
            dfs2(v);
}

void kosaraju()
{
    sccCnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs1(i);
    for (int i = n; i >= 1; --i)
        if (!color[s[i]])
        {
            ++sccCnt;
            dfs2(s[i]);
        }
}
