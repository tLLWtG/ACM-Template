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

// cp from Pecco

// dynamic node (and cnt) SegmentTree

namespace DST
{
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define val(x) tree[x].val
#define mark(x) tree[x].mark
    const int MAXV = 8e6;
    int L = -1e5, R = 1e5, cnt = 1;
    struct node
    {
        ll val, mark;
        int ls, rs;
    } tree[MAXV];
    void upd(int &p, int x, int len)
    {
        if (!p)
            p = ++cnt;
        val(p) += x * len;
        mark(p) += x;
    }
    void push_down(int p, int cl, int cr)
    {
        if (cl >= cr)
            return;
        int mid = (cl + cr - 1) / 2;
        upd(ls(p), mark(p), mid - cl + 1);
        upd(rs(p), mark(p), cr - mid);
        mark(p) = 0;
    }
    ll query(int l, int r, int p = 1, int cl = L, int cr = R)
    {
        if (cl >= l && cr <= r)
            return val(p);
        push_down(p, cl, cr);
        ll mid = (cl + cr - 1) / 2, ans = 0;
        if (mid >= l)
            ans += query(l, r, ls(p), cl, mid);
        if (mid < r)
            ans += query(l, r, rs(p), mid + 1, cr);
        return ans;
    }
    void update(int l, int r, int d, int p = 1, int cl = L, int cr = R)
    {
        if (cl >= l && cr <= r)
            return (void)(val(p) += d * (cr - cl + 1), mark(p) += d);
        push_down(p, cl, cr);
        int mid = (cl + cr - 1) / 2;
        if (mid >= l)
            update(l, r, d, ls(p), cl, mid);
        if (mid < r)
            update(l, r, d, rs(p), mid + 1, cr);
        val(p) = val(ls(p)) + val(rs(p));
    }
    // cnt part
    void insert(int v)
    {
        update(v, v, 1);
    }
    void remove(int v)
    {
        update(v, v, -1);
    }
    int countl(int v)
    {
        return query(L, v - 1);
    }
    int countg(int v)
    {
        return query(v + 1, R);
    }
    int rank(int v)
    {
        return countl(v) + 1;
    }
    int kth(int k, int p = 1, int cl = L, int cr = R)
    {
        if (cl == cr)
            return cl;
        int mid = (cl + cr - 1) / 2;
        if (val(ls(p)) >= k)
            return kth(k, ls(p), cl, mid);
        else
            return kth(k - val(ls(p)), rs(p), mid + 1, cr);
    }
    int pre(int v)
    {
        int r = countl(v);
        return kth(r);
    }
    int suc(int v)
    {
        int r = val(1) - countg(v) + 1;
        return kth(r);
    }
}

// merge segment tree
//
// 1. new root
// int merge(int a, int b, int l = 1, int r = nn)
// {
//     if (!a || !b)
//         return a + b; // 如果有一个为空，就返回不为空的；如果都为空就返回空
//     int c = ++cnt;
//     if (l == r)
//         return T[c].v = T[a].v + T[b].v, c;
//     int mid = l + r >> 1;
//     T[c].ls = merge(T[a].ls, T[b].ls, l, mid);
//     T[c].rs = merge(T[a].rs, T[b].rs, mid + 1, r);
//     pushup(c);
//     return c;
// }
//
// 2. use a's root
// more efficient
//
// int merge(int a, int b, int l = 1, int r = nn)
// {
//     if (!a || !b)
//         return a + b;
//     if (l == r)
//         return T[a].v += T[b].v, a;
//     int mid = l + r >> 1;
//     T[a].ls = merge(T[a].ls, T[b].ls, l, mid);
//     T[a].rs = merge(T[a].rs, T[b].rs, mid + 1, r);
//     pushup(a);
//     return a;
// }