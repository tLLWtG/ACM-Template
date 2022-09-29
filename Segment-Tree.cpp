#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

/*-------------------------------------------*/

// sum 版本
#define MAXN 100005

ll tree[MAXN * 4];
ll mark[MAXN * 4];
ll arr[MAXN];

ll n;

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

void update(ll l, ll r, ll d, ll p = 1, ll cl = 1, ll cr = n)
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
        /*
        mark[p * 2] += mark[p];
        mark[p * 2 + 1] += mark[p];
        tree[p * 2] += mark[p] * (middle - cl + 1);
        tree[p * 2 + 1] += mark[p] * (cr - middle);
        mark[p] = 0;
        */
        push_down(p, cr - cl + 1);
        update(l, r, d, p * 2, cl, middle);
        update(l, r, d, p * 2 + 1, middle + 1, cr);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
}

ll query(ll l, ll r, ll p = 1, ll cl = 1, ll cr = n)
{
    if (cl > r || cr < l)
        return 0;
    else if (cl >= l && cr <= r)
        return tree[p];
    else
    {
        ll mid = (cl + cr) / 2;
        push_down(p, cr - cl + 1);
        return query(l, r, p * 2, cl, mid) + query(l, r, p * 2 + 1, mid + 1, cr);
    }
}