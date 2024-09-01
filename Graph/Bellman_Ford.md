### Bellman_Ford

```cpp
#define MAXN 10005

struct edge
{
    int v, w;
};

vector<vector<edge>> e(MAXN);
int dis[MAXN];
const int inf = 0x3f3f3f3f;

bool bellmanford(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    bool flag;
    for (int i = 1; i <= n; ++i)
    {
        flag = false;
        for (int u = 1; u <= n; ++u)
        {
            if (dis[u] == inf)
                continue;
            for (auto &x : e[u])
            {
                int v = x.v, w = x.w;
                if (dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    flag = true;
                }
            }
        }
        if (!flag)
            break;
    }
    return flag;
}

//

int vis[MAXN], cnt[MAXN];
queue<int> q;

bool spfa(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto &x : e[u])
        {
            int v = x.v, w = x.w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n)
                    return false;
                if (!vis[v])
                    q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}
```

