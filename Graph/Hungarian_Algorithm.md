### Hungarian_Algorithm

> Hungarian Algorithm or Kuhn–Munkres Algorithm
>
> index starts from 0
> 
> if perfect is true and output is about -1e14, there is no solution

```cpp
template <typename T>
class Hungarian
{
private:
    bool perfect;
    int n;
    int org_n;
    int org_m;
    T inf;
    vector<int> pre;
    vector<bool> visx;
    vector<bool> visy;
    vector<T> slack;
    vector<T> lx;
    vector<T> ly;
    queue<int> q;
    vector<vector<T>> g;

    bool check(int v)
    {
        visy[v] = true;
        if (matchy[v] != -1)
        {
            q.push(matchy[v]);
            visx[matchy[v]] = true;
            return false;
        }
        while (v != -1)
        {
            matchy[v] = pre[v];
            swap(v, matchx[pre[v]]);
        }
        return true;
    }

    void bfs(int i)
    {
        while (!q.empty())
            q.pop();
        q.push(i);
        visx[i] = true;
        while (true)
        {
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; v++)
                {
                    if (visy[v])
                        continue;
                    T delta = lx[u] + ly[v] - g[u][v];
                    if (slack[v] >= delta)
                    {
                        pre[v] = u;
                        if (delta)
                            slack[v] = delta;
                        else if (check(v))
                            return;
                    }
                }
            }
            T a = inf;
            for (int j = 0; j < n; j++)
            {
                if (!visy[j])
                    a = min(a, slack[j]);
            }
            for (int j = 0; j < n; j++)
            {
                if (visx[j])
                    lx[j] -= a;
                if (visy[j])
                    ly[j] += a;
                else
                    slack[j] -= a;
            }
            for (int j = 0; j < n; j++)
            {
                if (!visy[j] && slack[j] == 0 && check(j))
                    return;
            }
        }
    }

public:
    T res;
    vector<int> matchx;
    vector<int> matchy;

    Hungarian(int _n, int _m, bool _perfect = false)
    {
        org_n = _n;
        org_m = _m;
        perfect = _perfect;
        n = max(_n, _m);
        inf = numeric_limits<T>::max();
        res = 0;
        if (perfect)
            g = vector<vector<T>>(n, vector<T>(n, -1e14));
        else
            g = vector<vector<T>>(n, vector<T>(n, 0));
        matchx = vector<int>(n, -1);
        matchy = vector<int>(n, -1);
        pre = vector<int>(n);
        visx = vector<bool>(n);
        visy = vector<bool>(n);
        lx = vector<T>(n, -inf);
        ly = vector<T>(n);
        slack = vector<T>(n);
    }

    void addEdge(int u, int v, int w)
    {
        if (perfect)
            g[u][v] = w;
        else
            g[u][v] = max(w, 0);
    }

    T solve()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                lx[i] = max(lx[i], g[i][j]);
        for (int i = 0; i < n; i++)
        {
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            bfs(i);
        }
        if (perfect)
        {
            for (int i = 0; i < n; i++)
            {
                res += g[i][matchx[i]];
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (g[i][matchx[i]] > 0)
                    res += g[i][matchx[i]];
                else
                    matchx[i] = -1;
            }
        }
        return res;
    }
};
```

