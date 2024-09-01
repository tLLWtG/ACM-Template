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

// 1. persistent array
// (partially persistent)

namespace pa
{
    vector<pii> arr[100005];
    int get_item(int index, int time)
    {
        auto ub = upper_bound(all(arr[index]), make_pair(time, INT_MAX));
        return prev(ub)->se;
    }
    void update_item(int index, int value, int time)
    {
        assert(arr[index].back().fi < time);
        arr[index].pb({time, value});
    }
    void init_arr(int n, const vector<int> &init)
    {
        for (int i = 0; i < n; ++i)
            arr[i].pb({0, init[i]});
    }
}

// 2. persistent segment tree

namespace PST
{
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define val(x) tree[x].val
#define mark(x) tree[x].mark
    const int MAXV = 20000000, MAXN = 1000005;
    struct node
    {
        int val, ls, rs;
    } tree[MAXV];
    int A[MAXN], roots[MAXN], n, m, cnt = 1; // roots记录每个历史版本的根节点
    void build(int l = 1, int r = n, int p = 1)
    {
        if (l == r)
            val(p) = A[l];
        else
        {
            ls(p) = ++cnt, rs(p) = ++cnt;
            int mid = (l + r) / 2;
            build(l, mid, ls(p));
            build(mid + 1, r, rs(p));
            val(p) = val(ls(p)) + val(rs(p));
        }
    }
    void update(int x, int d, int p, int q, int cl = 1, int cr = n) // 单点修改
    {
        if (cl == cr)
            val(q) = d;
        else
        {
            ls(q) = ls(p), rs(q) = rs(p);
            int mid = (cl + cr) / 2;
            if (x <= mid)
                ls(q) = ++cnt, update(x, d, ls(p), ls(q), cl, mid);
            else
                rs(q) = ++cnt, update(x, d, rs(p), rs(q), mid + 1, cr);
            val(q) = val(ls(q)) + val(rs(q));
        }
    }
    int query(int l, int r, int p, int cl = 1, int cr = n) // 区间查询
    {
        if (cl > r || cr < l)
            return 0;
        else if (cl >= l && cr <= r)
            return val(p);
        else
        {
            int mid = (cl + cr) / 2;
            return query(l, r, ls(p), cl, mid) + query(l, r, rs(p), mid + 1, cr);
        }
    }

    // example
    void solve()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            cin >> A[i];
        build();
        roots[0] = 1;
        for (int t = 1; t <= m; ++t)
        {
            int v, o;
            cin >> v >> o;
            if (o == 1)
            {
                int x, d;
                cin >> x >> d;
                roots[t] = ++cnt; // 新建节点
                update(x, d, roots[v], roots[t]);
            }
            else
            {
                int x;
                cin >> x;
                roots[t] = roots[v]; // 复用v号版本
                cout << query(x, x, roots[v]) << endl;
            }
        }
    }
}

// 3. president tree
namespace PT
{
#define ls(x) (tr[x].l)
#define rs(x) (tr[x].r)
#define sum(x) tr[x].sum
    const int N = 2e5 + 5;
    const int M = 1e6 + 5;
    struct node
    {
        int sum = 0;
        int l = 0, r = 0;
    } tr[M * 30];
    int tot = 1;
    int root[N], a[N], n, m;
    void pushup(int x)
    {
        sum(x) = sum(ls(x)) + sum(rs(x));
    }
    void upd(int last, int now, int pos, int k, int l, int r)
    {
        // 过去的节点 现在的节点 修改的位置，k ，当前节点表示的区间[l,r]
        if (l == r)
        {
            sum(now) = sum(last) + k;
        }
        else
        {
            ls(now) = ls(last), rs(now) = rs(last);
            int mid = (l + r - 1) / 2;
            if (pos <= mid)
                ls(now) = ++tot, upd(ls(last), ls(now), pos, k, l, mid);
            else
                rs(now) = ++tot, upd(rs(last), rs(now), pos, k, mid + 1, r);
            pushup(now);
        }
    }
    const int up = 1e9 + 5;
    const int down = -(1e9 + 5);
    void upd(int last, int now, int pos, int k)
    {
        upd(last, now, pos, k, down, up);
    }
    int kth(int last, int now, int k, int l, int r)
    {
        if (l == r)
            return l;
        int mid = (l + r - 1) / 2;
        int val = sum(ls(now)) - sum(ls(last));
        if (val >= k)
            return kth(ls(last), ls(now), k, l, mid);
        else
            return kth(rs(last), rs(now), k - val, mid + 1, r);
    }
    int kth(int last, int now, int k)
    {
        return kth(last, now, k, down, up);
    }

    // example
    void solve()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
        {
            root[i] = ++tot;
            upd(root[i - 1], root[i], a[i], 1);
        }
        while (m--)
        {
            int L, R, k;
            cin >> L >> R >> k;
            cout << kth(root[L - 1], root[R], k) << endl;
        }
    }
}