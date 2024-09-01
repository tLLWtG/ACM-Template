### Biconnected_Component

1. Edge-bcc

```cpp
namespace Ebcc
{
    const int N = 5e5 + 5, M = 2e6 + 5;
    int n, m;

    struct edge {
        int to, nt;
    } e[M << 2];

    int hd[N << 1], tot = 1;

    void add(int u, int v) { e[++tot] = (edge){v, hd[u]}, hd[u] = tot; }
    void uadd(int u, int v) { add(u, v), add(v, u); }

    int bcc_cnt, sum;
    int dfn[N], low[N];
    bool vis[N];
    vector<vector<int>> ans;
    stack<int> st;

    void tarjan(int u, int in) {
        low[u] = dfn[u] = ++bcc_cnt;
        st.push(u), vis[u] = 1;
        for (int i = hd[u]; i; i = e[i].nt) {
            int v = e[i].to;
            if (i == (in ^ 1)) continue;
            if (!dfn[v])
                tarjan(v, i), low[u] = min(low[u], low[v]);
            else if (vis[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            vector<int> t;
            t.push_back(u);
            while (st.top() != u)
                t.push_back(st.top()), vis[st.top()] = 0, st.pop();
            st.pop(), ans.push_back(t);
        }
    }

    int main() {
        scanf("%d%d", &n, &m);
        int u, v;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &u, &v);
            if (u != v) uadd(u, v);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(i, 0);
        printf("%llu\n", ans.size());
        for (int i = 0; i < ans.size(); i++) {
            printf("%llu ", ans[i].size());
            for (int j = 0; j < ans[i].size(); j++) printf("%d ", ans[i][j]);
            printf("\n");
        }
        return 0;
    }
}
```

2. Vetex-bcc

```cpp
namespace Vbcc
{
    const int N = 5e5 + 5, M = 2e6 + 5;
    int n, m;

    struct edge {
        int to, nt;
    } e[M << 1];

    int hd[N], tot = 1;

    void add(int u, int v) { e[++tot] = (edge){v, hd[u]}, hd[u] = tot; }
    void uadd(int u, int v) { add(u, v), add(v, u); }

    int ans;
    int dfn[N], low[N], bcc_cnt;
    int sta[N], top, cnt;
    bool cut[N];
    vector<int> dcc[N];
    int root;

    void tarjan(int u) {
        dfn[u] = low[u] = ++bcc_cnt, sta[++top] = u;
        if (u == root && hd[u] == 0) {
            dcc[++cnt].push_back(u);
            return;
        }
        int f = 0;
        for (int i = hd[u]; i; i = e[i].nt) {
            int v = e[i].to;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (++f > 1 || u != root) cut[u] = true;
                    cnt++;
                    do
                        dcc[cnt].push_back(sta[top--]);
                    while (sta[top + 1] != v);
                    dcc[cnt].push_back(u);
                }
            } else
                low[u] = min(low[u], dfn[v]);
        }
    }

    int main() {
        scanf("%d%d", &n, &m);
        int u, v;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &u, &v);
            if (u != v) uadd(u, v);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) root = i, tarjan(i);
        printf("%d\n", cnt);
        for (int i = 1; i <= cnt; i++) {
            printf("%llu ", dcc[i].size());
            for (int j = 0; j < dcc[i].size(); j++) printf("%d ", dcc[i][j]);
            printf("\n");
        }
        return 0;
    }
}
```

