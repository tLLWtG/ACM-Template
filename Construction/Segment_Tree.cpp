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

// sum version
class SegmentTree
{
    SegmentTree(int _n): n(_n)
    {
        tree.resize(4 * n + 10, 0);
        mark.resize(4 * n + 10, 0);
        arr.resize(n + 10);
    }
    vector<ll> arr;

    void build(ll l, ll r, ll p = 1)
    {
        if (l == r)
            tree[p] = arr[l];
        else
        {
            ll middle = (l + r) / 2;
            build(l, middle, 2 * p);
            build(middle + 1, r, 2 * p + 1);
            tree[p] = tree[2 * p] + tree[2 * p + 1];
        }
    }

    void push_down(ll p, ll len)
    {
        mark[p * 2] += mark[p];
        mark[p * 2 + 1] += mark[p];
        tree[p * 2] += mark[p] * (len - len / 2);
        tree[p * 2 + 1] += mark[p] * (len / 2);
        mark[p] = 0;
    }

    void update(ll l, ll r, ll cl, ll cr, ll d, ll p = 1)
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
            ll middle = (cl + cr) / 2;
            push_down(p, cr - cl + 1);
            update(l, r, cl, middle, d, p * 2);
            update(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p] = tree[p * 2] + tree[p * 2 + 1];
        }
    }

    ll query(ll l, ll r, ll cl, ll cr, ll p = 1)
    {
        if (cl > r || cr < l)
            return 0;
        else if (cl >= l && cr <= r)
            return tree[p];
        else
        {
            ll mid = (cl + cr) / 2;
            push_down(p, cr - cl + 1);
            return query(l, r, cl, mid, p * 2) + query(l, r, mid + 1, cr, p * 2 + 1);
        }
    }

private:
    int n;
    vector<ll> tree, mark;
};

