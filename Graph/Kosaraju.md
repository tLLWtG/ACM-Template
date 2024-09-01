### Kosaraju

> g 是原图，g2 是反图

```cpp
#define MAXN 100005

vector<bool> vis(MAXN);
vector<int> color(MAXN), s;
int n, sccCnt;

vector<vector<int>> g(MAXN), g2(MAXN);

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
```

