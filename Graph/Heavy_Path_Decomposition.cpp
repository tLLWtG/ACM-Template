#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

#define debug(x)                          \
    {                                     \
        cerr << #x << " = " << x << endl; \
    }
#define debugfull(x)                                                      \
    {                                                                     \
        cerr << #x << " = " << x << " (line " << __LINE__ << ")" << endl; \
    }

/*-------------------------------------------*/

namespace PD
{
    template <typename T>
    class SegmentTree
    {
    private:
        int n;
        vector<T> tree, mark;
        void push_down(int p, int len)
        {
            mark[p * 2] += mark[p];
            mark[p * 2 + 1] += mark[p];
            tree[p * 2] += mark[p] * (len - len / 2);
            tree[p * 2 + 1] += mark[p] * (len / 2);
            mark[p] = 0;
        }

    public:
        vector<T> arr;
        SegmentTree(int _n) : n(_n)
        {
            tree.resize(4 * n + 10, 0);
            mark.resize(4 * n + 10, 0);
            arr.resize(n + 10);
        }
        void build(int l, int r, int p = 1)
        {
            if (l == r)
                tree[p] = arr[l];
            else
            {
                int middle = (l + r) / 2;
                build(l, middle, 2 * p);
                build(middle + 1, r, 2 * p + 1);
                tree[p] = tree[2 * p] + tree[2 * p + 1];
            }
        }
        void update(int l, int r, int cl, int cr, T d, int p = 1)
        {
            if (cr < l || cl > r)
                return;
            else if (l <= cl && cr <= r)
            {
                tree[p] += d * (cr - cl + 1);
                if (cr > cl)
                    mark[p] += d;
            }
            else
            {
                int middle = (cl + cr) / 2;
                push_down(p, cr - cl + 1);
                update(l, r, cl, middle, d, p * 2);
                update(l, r, middle + 1, cr, d, p * 2 + 1);
                tree[p] = tree[p * 2] + tree[p * 2 + 1];
            }
        }
        T query(int l, int r, int cl, int cr, int p = 1)
        {
            if (cl > r || cr < l)
                return 0;
            else if (cl >= l && cr <= r)
                return tree[p];
            else
            {
                int mid = (cl + cr) / 2;
                push_down(p, cr - cl + 1);
                return query(l, r, cl, mid, p * 2) + query(l, r, mid + 1, cr, p * 2 + 1);
            }
        }
    };
    const int MAXN = 100005;
    int n;
    int tot = 0;
    vector<vector<int>> e(MAXN);
    vector<ll> val(MAXN);
    vector<int> fa(MAXN), hson(MAXN), sz(MAXN), dep(MAXN);
    vector<int> dfn(MAXN), rank(MAXN), rdfn(MAXN), top(MAXN);
    SegmentTree<ll> tree(MAXN);
    void dfs1(int cur, int last, int d = 1)
    {
        int maxi = 0;
        sz[cur] = 1;
        dep[cur] = d;
        for (auto v : e[cur])
        {
            if (v == last)
                continue;
            dfs1(v, cur, d + 1);
            fa[v] = cur;
            sz[cur] += sz[v];
            if (sz[v] > maxi)
                hson[cur] = v, maxi = sz[v];
        }
    }
    // initially t=root
    void dfs2(int cur, int last, int t)
    {
        top[cur] = t;
        dfn[cur] = ++tot;
        rank[tot] = cur;
        if (hson[cur])
            dfs2(hson[cur], cur, t);
        for (auto v : e[cur])
        {
            if (v == last || v == hson[cur])
                continue;
            dfs2(v, cur, v);
        }
        rdfn[cur] = tot;
    }
    int lca(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] > dep[top[y]])
                x = fa[top[x]];
            else
                y = fa[top[y]];
        }
        return dep[x] > dep[y] ? y : x;
    }
    // build after e and val is filled
    void build(int root, int _n)
    {
        n = _n;
        dfs1(root, 0);
        dfs2(root, 0, root);
        for (int i = 1; i <= n; ++i)
            tree.arr[dfn[i]] = val[i];
        tree.build(1, n);
    }
    void update_path(int x, int y, ll d)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] > dep[top[y]])
            {
                tree.update(dfn[top[x]], dfn[x], 1, n, d);
                x = fa[top[x]];
            }
            else
            {
                tree.update(dfn[top[y]], dfn[y], 1, n, d);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y])
            tree.update(dfn[y], dfn[x], 1, n, d);
        else
            tree.update(dfn[x], dfn[y], 1, n, d);
    }
    void update_tree(int x, ll d)
    {
        tree.update(dfn[x], rdfn[x], 1, n, d);
    }
    ll query_path(int x, int y)
    {
        ll ans = 0;
        while (top[x] != top[y])
        {
            if (dep[top[x]] > dep[top[y]])
            {
                ans += tree.query(dfn[top[x]], dfn[x], 1, n);
                x = fa[top[x]];
            }
            else
            {
                ans += tree.query(dfn[top[y]], dfn[y], 1, n);
                y = fa[top[y]];
            }
        }
        if (dep[x] > dep[y])
            ans += tree.query(dfn[y], dfn[x], 1, n);
        else
            ans += tree.query(dfn[x], dfn[y], 1, n);
        return ans;
    }
    ll query_tree(int x)
    {
        return tree.query(dfn[x], rdfn[x], 1, n);
    }
}
