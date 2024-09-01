### Tarjan

```cpp
#define N 100005

vector<vector<int>> e(N);

int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;
int sz[N];

void tarjan(int u)
{
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
    for (auto v : e[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++sc;
        while (s[tp] != u)
        {
            scc[s[tp]] = sc;
            ++sz[sc];
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        ++sz[sc];
        in_stack[s[tp]] = 0;
        --tp;
    }
}
```

