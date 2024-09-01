### LCA

> Binary Lifting

```cpp
class LCA
{
private:
    int n;
    vector<int> dep;
    vector<vector<int>> fa;

public:
    vector<vector<int>> v;
    LCA(int _n) : n(_n)
    {
        v.resize(n + 5);
        dep.resize(n + 5, 0);
        fa = vector<vector<int>>(n + 5, vector<int>(31, 0));
    }
    void init(int cur = 1, int fanode = 0)
    {
        fa[cur][0] = fanode;
        dep[cur] = dep[fanode] + 1;
        for (int i = 1; i < 31; ++i)
            fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
        for (int i = 0; i < v[cur].size(); ++i)
        {
            if (v[cur][i] == fanode)
                continue;
            init(v[cur][i], cur);
        }
    }
    int lca(int x, int y)
    {
        if (dep[x] > dep[y])
            swap(x, y);
        int tmp = dep[y] - dep[x];
        for (int j = 0; tmp; ++j, tmp >>= 1)
            if (tmp & 1)
                y = fa[y][j];
        if (y == x)
            return x;
        for (int j = 30; j >= 0 && y != x; --j)
        {
            if (fa[x][j] != fa[y][j])
            {
                x = fa[x][j];
                y = fa[y][j];
            }
        }
        return fa[x][0];
    }
};
```

