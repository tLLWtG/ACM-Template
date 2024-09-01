### Graph

1. 邻接表

```cpp
struct edge
{
    int v, w;
};

vector<vector<edge>> e1(MAXN);
```

2. 邻接矩阵

```cpp
int e2[MAXN][MAXN];
```

3. 链式前向星

```cpp
int n, m, cnt = 0;

struct Edge
{
    int to;
    int w;
    int nxt;
};

vector<Edge> e(m * 2 + 10);
vector<int> head(n + 1, 0);

function<void(int u, int v, int w)> add = [&](int u, int v, int w)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}; 

bool find_edge(int u, int v)
{
    for (int eg = head[u]; eg; eg = e[eg].nxt)
        if (e[eg].to == v)
            return true;
    return false;
}
```
