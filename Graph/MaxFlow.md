### MaxFlow

1. EK

> O(V*E^2)
>
> 未处理重边

```cpp
struct Edge
{
    int to;
    int w;
    int nxt;
};


void solve()
{
    int m, n, u, v, w;
    cin >> m >> n;
    int s = 1, t = n;
    vector<Edge> e(m * 2 + 10);
    vector<int> head(n + 1, 0), last(n + 1), flow(n + 1);
    int cnt = 1;
    function<void(int u, int v, int w)> add = [&](int u, int v, int w)
    {
        ++cnt;
        e[cnt].to = v;
        e[cnt].w = w;
        e[cnt].nxt = head[u];
        head[u] = cnt;
    }; 
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, 0);
    }
    function<bool()> bfs = [&]()->bool
    {
        queue<int> q;
        flow[s] = 1e9;
        fill(all(last), -1);
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int eg = head[u]; eg; eg = e[eg].nxt)
            {
                int to = e[eg].to;
                int w = e[eg].w;
                if (last[to] == -1 && w > 0)
                {
                    last[to] = eg;
                    flow[to] = min(flow[u], w);
                    q.push(to);
                    if (to == t)
                        return true;
                }
            }
        }
        return last[t] != -1;
    };
    int maxflow = 0;
    while (bfs())
    {
        maxflow += flow[t];
        for (int x = t; x != s; x = e[last[x] ^ 1].to)
        {
            e[last[x]].w -= flow[t];
            e[last[x] ^ 1].w += flow[t];
        }
    }
    cout << maxflow << endl;
}
```

2. Dinic

> O(V^2*E) 跑不满
> 
> 在单位容量的网络上，Dinic 算法的总时间复杂度是 O(E*min(E^0.5, V^0.66))
> 
> 在单位容量的网络上，如果除源汇点外每个结点 u 都满入度出度为 1，Dinic 算法的总时间复杂度是 O(E*V^0.5)

```cpp
namespace Dinic
{
    const ll N = 1e4, INF = 1e9;

    struct MF {
        struct edge {
            int v, nxt, cap, flow;
        } e[N];

        int fir[N], cnt = 0;

        int n, S, T;
        ll maxflow = 0;
        int dep[N], cur[N];

        void init() {
            memset(fir, -1, sizeof fir);
            cnt = 0;
        }

        void addedge(int u, int v, int w) {
            e[cnt] = {v, fir[u], w, 0};
            fir[u] = cnt++;
            e[cnt] = {u, fir[v], 0, 0};
            fir[v] = cnt++;
        }

        bool bfs() {
            queue<int> q;
            memset(dep, 0, sizeof(int) * (n + 1));

            dep[S] = 1;
            q.push(S);
            while (q.size()) {
                int u = q.front();
                q.pop();
                for (int i = fir[u]; ~i; i = e[i].nxt) {
                    int v = e[i].v;
                    if ((!dep[v]) && (e[i].cap > e[i].flow)) {
                        dep[v] = dep[u] + 1;
                        q.push(v);
                    }
                }
            }
            return dep[T];
        }

        int dfs(int u, int flow) {
            if ((u == T) || (!flow)) return flow;

            int ret = 0;
            for (int& i = cur[u]; ~i; i = e[i].nxt) {
                int v = e[i].v, d;
                if ((dep[v] == dep[u] + 1) &&
                    (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))) {
                    ret += d;
                    e[i].flow += d;
                    e[i ^ 1].flow -= d;
                    if (ret == flow) return ret;
                }
            }
            return ret;
        }

        void dinic() {
            while (bfs()) {
                memcpy(cur, fir, sizeof(int) * (n + 1));
                maxflow += dfs(S, INF);
            }
        }
    } mf;

    void solve()
    {
        int n, m, s, t, x, y, w;
        cin >> n >> m >> s >> t;
        mf.init();
        mf.n = n;
        mf.S = s;
        mf.T = t;
        for (int i = 1; i <= m; ++i)
        {
            cin >> x >> y >> w;
            mf.addedge(x, y, w);
        }
        mf.dinic();
        cout << mf.maxflow << endl;
    }
}
```

