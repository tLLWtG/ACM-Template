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

// if data is complex, use node struct to manage them

// 1. add and sum version

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

// 2. change and sum version

template <typename T>
class SegTreeLazyRangeSet
{
private:
    vector<T> tree, lazy;
    vector<T> *arr;
    int n, root, n4, end;
    void maintain(int cl, int cr, int p)
    {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && lazy[p])
        {
            lazy[p * 2] = lazy[p];
            lazy[p * 2 + 1] = lazy[p];
            tree[p * 2] = lazy[p] * (cm - cl + 1);
            tree[p * 2 + 1] = lazy[p] * (cr - cm);
            lazy[p] = 0;
        }
    }
    T range_sum(int l, int r, int cl, int cr, int p)
    {
        if (l <= cl && cr <= r)
            return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m)
            sum += range_sum(l, r, cl, m, p * 2);
        if (r > m)
            sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }
    void range_set(int l, int r, T val, int cl, int cr, int p)
    {
        if (l <= cl && cr <= r)
        {
            lazy[p] = val;
            tree[p] = (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m)
            range_set(l, r, val, cl, m, p * 2);
        if (r > m)
            range_set(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void build(int s, int t, int p)
    {
        if (s == t)
        {
            tree[p] = (*arr)[s];
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    explicit SegTreeLazyRangeSet<T>(vector<T> v)
    {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }
    void show(int p, int depth = 0)
    {
        if (p > n4 || tree[p] == 0)
            return;
        show(p * 2, depth + 1);
        for (int i = 0; i < depth; ++i)
            putchar('\t');
        printf("%d:%d\n", tree[p], lazy[p]);
        show(p * 2 + 1, depth + 1);
    }
    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }
    void range_set(int l, int r, int val) { range_set(l, r, val, 0, end, root); }
};

// 3. add, mul and sum version

template <typename T>
class SegmentTree_pro
{
private:
    int n, mod;
    vector<T> tree, mark_p, mark_m;
    void push_down(int p, int len)
    {
        mark_m[p * 2] = mark_m[p * 2] * mark_m[p] % mod;
        mark_m[p * 2 + 1] = mark_m[p * 2 + 1] * mark_m[p] % mod;
        mark_p[p * 2] = (mark_p[p * 2] * mark_m[p] % mod + mark_p[p]) % mod;
        mark_p[p * 2 + 1] = (mark_p[p * 2 + 1] * mark_m[p] % mod + mark_p[p]) % mod;
        tree[p * 2] = (tree[p * 2] * mark_m[p] % mod + mark_p[p] * (len - len / 2) % mod) % mod;
        tree[p * 2 + 1] = (tree[p * 2 + 1] * mark_m[p] % mod + mark_p[p] * (len / 2) % mod) % mod;
        mark_p[p] = 0;
        mark_m[p] = 1;
    }

public:
    vector<T> arr;
    SegmentTree_pro(int _n, int _mod) : n(_n), mod(_mod)
    {
        tree.resize(4 * n + 10, 0);
        mark_p.resize(4 * n + 10, 0);
        mark_m.resize(4 * n + 10, 1);
        arr.resize(n + 10);
    }
    void build(int l, int r, int p = 1)
    {
        if (l == r)
            tree[p] = arr[l] % mod;
        else
        {
            int middle = (l + r) / 2;
            build(l, middle, 2 * p);
            build(middle + 1, r, 2 * p + 1);
            tree[p] = (tree[2 * p] + tree[2 * p + 1]) % mod;
        }
    }
    void update_add(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p] = (tree[p] + d * (cr - cl + 1)) % mod;
            if (cr > cl)
                mark_p[p] = (mark_p[p] + d) % mod;
        }
        else
        {
            int middle = (cl + cr) / 2;
            push_down(p, cr - cl + 1);
            update_add(l, r, cl, middle, d, p * 2);
            update_add(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p] = (tree[p * 2] + tree[p * 2 + 1]) % mod;
        }
    }
    void update_mul(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p] = tree[p] * d % mod;
            if (cr > cl)
            {
                mark_p[p] = mark_p[p] * d % mod;
                mark_m[p] = mark_m[p] * d % mod;
            }
        }
        else
        {
            T middle = (cl + cr) / 2;
            push_down(p, cr - cl + 1);
            update_mul(l, r, cl, middle, d, p * 2);
            update_mul(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p] = (tree[p * 2] + tree[p * 2 + 1]) % mod;
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
            return (query(l, r, cl, mid, p * 2) + query(l, r, mid + 1, cr, p * 2 + 1)) % mod;
        }
    }
};

// 4. add and max version (no sum)

template <typename T>
class SegmentTree_max
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
    SegmentTree_max(int _n) : n(_n)
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
            tree[p] = max(tree[2 * p], tree[2 * p + 1]);
        }
    }
    void update(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p] += d;
            if (cr > cl)
                mark[p] += d;
        }
        else
        {
            int middle = (cl + cr) / 2;
            push_down(p, cr - cl + 1);
            update(l, r, cl, middle, d, p * 2);
            update(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
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
            return max(query(l, r, cl, mid, p * 2), query(l, r, mid + 1, cr, p * 2 + 1));
        }
    }
};