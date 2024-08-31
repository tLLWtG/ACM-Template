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
    void push_down(int p)
    {
        mark[p * 2] += mark[p];
        mark[p * 2 + 1] += mark[p];
        tree[p * 2] += mark[p];
        tree[p * 2 + 1] += mark[p];
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
            push_down(p);
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
            push_down(p);
            return max(query(l, r, cl, mid, p * 2), query(l, r, mid + 1, cr, p * 2 + 1));
        }
    }
};

// 另一种思路：维护差分数组的正负个数，区间最值（都为0则相等）

template <typename T>
class SegmentTree1
{
public:
    int n;
    // vector<T> tree, mark;
    struct node
    {
        T val, mark;
        bool iseq;
    };
    
    vector<node> tree;
    
	struct qres1
	{
		T val;
		bool ok, iseq;
	};
	
    void push_down(int p)
    {
        tree[2 * p].val += tree[p].mark;
        tree[2 * p + 1].val += tree[p].mark;
        tree[2 * p].mark += tree[p].mark;
        tree[2 * p + 1].mark += tree[p].mark;
        tree[p].mark = 0;
    }

public:
    vector<T> arr;
    SegmentTree1(int _n) : n(_n)
    {
        tree.resize(4 * n + 10);
        arr.resize(n + 10);
    }
    void build(int l, int r, int p = 1)
    {
        if (l == r)
        {
            tree[p].val = arr[l];
            tree[p].mark = 0;
            tree[p].iseq = true;
        }
        else
        {
            int middle = (l + r) / 2;
            build(l, middle, 2 * p);
            build(middle + 1, r, 2 * p + 1);
            tree[p].val = tree[2 * p].val;
            tree[p].mark = 0;
            tree[p].iseq = tree[2 * p].val == tree[2 * p + 1].val && tree[2 * p].iseq && tree[2 * p + 1].iseq;
        }
    }
    void update(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p].val += d;
            if (cr > cl)
                tree[p].mark += d;
        }
        else
        {
            int middle = (cl + cr) / 2;
            push_down(p);
            update(l, r, cl, middle, d, p * 2);
            update(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p].val = tree[2 * p].val;
            tree[p].iseq = tree[2 * p].val == tree[2 * p + 1].val && tree[2 * p].iseq && tree[2 * p + 1].iseq;
        }
    }
    qres1 query(int l, int r, int cl, int cr, int p = 1)
    {
        if (cl > r || cr < l)
            return (qres1){0, false, true};
        else if (cl >= l && cr <= r)
        {
            return (qres1){tree[p].val, true, tree[p].iseq};
        }
        else
        {
            int mid = (cl + cr) / 2;
            push_down(p);
            // return query(l, r, cl, mid, p * 2) && query(l, r, mid + 1, cr, p * 2 + 1) && tree[2 * p].val == tree[2 * p + 1].val;
            qres1 res1 = query(l, r, cl, mid, p * 2);
            qres1 res2 = query(l, r, mid + 1, cr, p * 2 + 1);

            if (res1.ok && res2.ok)
            {
                return (qres1){res1.val, true, res1.iseq && res2.iseq && res1.val == res2.val};
            }
            else if (res1.ok && !res2.ok)
            {
				return (qres1){res1.val, true, res1.iseq};
            }
            else if (!res1.ok && res2.ok)
            {
				return (qres1){res2.val, true, res2.iseq};
            }
            else
            {
				return (qres1){0, false, true};
            }
        }
    }
};

template <typename T>
class SegmentTree2
{
private:
    int n;
    // vector<T> tree, mark;
    struct node
    {
        T lval, rval, mark;
        bool isgt;
    };
    vector<node> tree;
    
    struct qres2
    {
        T lval, rval;
        bool ok, isgt;
    };

    void push_down(int p)
    {
        tree[2 * p].lval += tree[p].mark;
        tree[2 * p + 1].lval += tree[p].mark;
        tree[2 * p].rval += tree[p].mark;
        tree[2 * p + 1].rval += tree[p].mark;
        tree[2 * p].mark += tree[p].mark;
        tree[2 * p + 1].mark += tree[p].mark;
        tree[p].mark = 0;
    }

public:
    vector<T> arr;
    SegmentTree2(int _n) : n(_n)
    {
        tree.resize(4 * n + 10);
        arr.resize(n + 10);
    }
    void build(int l, int r, int p = 1)
    {
        if (l == r)
        {
            tree[p].lval = arr[l];
            tree[p].rval = arr[l];
            tree[p].mark = 0;
            tree[p].isgt = true;
        }
        else
        {
            int middle = (l + r) / 2;
            build(l, middle, 2 * p);
            build(middle + 1, r, 2 * p + 1);
            tree[p].lval = tree[2 * p].lval;
            tree[p].rval = tree[2 * p + 1].rval;
            tree[p].mark = 0;
            tree[p].isgt = tree[2 * p].rval < tree[2 * p + 1].lval && tree[2 * p].isgt && tree[2 * p + 1].isgt;
        }
    }
    void update(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p].lval += d;
            tree[p].rval += d;
            if (cr > cl)
                tree[p].mark += d;
        }
        else
        {
            int middle = (cl + cr) / 2;
            push_down(p);
            update(l, r, cl, middle, d, p * 2);
            update(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p].lval = tree[2 * p].lval;
            tree[p].rval = tree[2 * p + 1].rval;
            tree[p].isgt = tree[2 * p].rval < tree[2 * p + 1].lval && tree[2 * p].isgt && tree[2 * p + 1].isgt;
        }
    }
    qres2 query(int l, int r, int cl, int cr, int p = 1)
    {
        if (cl > r || cr < l)
            return (qres2){0, 0, false, true};
        else if (cl >= l && cr <= r)
            return (qres2){tree[p].lval, tree[p].rval, true, tree[p].isgt};
        else
        {
            int mid = (cl + cr) / 2;
            push_down(p);
            // return query(l, r, cl, mid, p * 2) && query(l, r, mid + 1, cr, p * 2 + 1) && tree[2 * p].rval < tree[2 * p + 1].lval;
//            return query(l, r, cl, mid, p * 2) && query(l, r, mid + 1, cr, p * 2 + 1);
			qres2 res1 = query(l, r, cl, mid, p * 2);
			qres2 res2 = query(l, r, mid + 1, cr, p * 2 + 1);
			
			if (res1.ok && res2.ok)
			{
				return (qres2){res1.lval, res2.rval, true, res1.isgt && res2.isgt && res1.rval < res2.lval};
			}
			else if (res1.ok && !res2.ok)	
			{
				return (qres2){res1.lval, res2.rval, true, res1.isgt};
			}
			else if (!res1.ok && res2.ok)
			{
				return (qres2){res2.lval, res2.rval, true, res2.isgt};
			}
			else
			{
				return (qres2){0, 0, false, true};
			}
        }
    }
};

template <typename T>
class SegmentTree3
{
private:
    int n;
    // vector<T> tree, mark;
    struct node
    {
        T lval, rval, mark;
        bool islt;
    };
    vector<node> tree;
	struct qres3
	{
		T lval, rval;
		bool ok, islt;
	};
    
    void push_down(int p)
    {
        tree[2 * p].lval += tree[p].mark;
        tree[2 * p + 1].lval += tree[p].mark;
        tree[2 * p].rval += tree[p].mark;
        tree[2 * p + 1].rval += tree[p].mark;
        tree[2 * p].mark += tree[p].mark;
        tree[2 * p + 1].mark += tree[p].mark;
        tree[p].mark = 0;
    }

public:
    vector<T> arr;
    SegmentTree3(int _n) : n(_n)
    {
        tree.resize(4 * n + 10);
        arr.resize(n + 10);
    }
    void build(int l, int r, int p = 1)
    {
        if (l == r)
        {
            tree[p].lval = arr[l];
            tree[p].rval = arr[l];
            tree[p].mark = 0;
            tree[p].islt = true;
        }
        else
        {
            int middle = (l + r) / 2;
            build(l, middle, 2 * p);
            build(middle + 1, r, 2 * p + 1);
            tree[p].lval = tree[2 * p].lval;
            tree[p].rval = tree[2 * p + 1].rval;
            tree[p].mark = 0;
            tree[p].islt = tree[2 * p].rval > tree[2 * p + 1].lval && tree[2 * p].islt && tree[2 * p + 1].islt;
        }
    }
    void update(int l, int r, int cl, int cr, T d, int p = 1)
    {
        if (cr < l || cl > r)
            return;
        else if (l <= cl && cr <= r)
        {
            tree[p].lval += d;
            tree[p].rval += d;
            if (cr > cl)
                tree[p].mark += d;
        }
        else
        {
            int middle = (cl + cr) / 2;
            push_down(p);
            update(l, r, cl, middle, d, p * 2);
            update(l, r, middle + 1, cr, d, p * 2 + 1);
            tree[p].lval = tree[2 * p].lval;
            tree[p].rval = tree[2 * p + 1].rval;
            tree[p].islt = tree[2 * p].rval > tree[2 * p + 1].lval && tree[2 * p].islt && tree[2 * p + 1].islt;
        }
    }
    qres3 query(int l, int r, int cl, int cr, int p = 1)
    {
        if (cl > r || cr < l)
            return (qres3){0, 0, false, true};
        else if (cl >= l && cr <= r)
            return (qres3){tree[p].lval, tree[p].rval, true, tree[p].islt};
        else
        {
            int mid = (cl + cr) / 2;
            push_down(p);
            // return query(l, r, cl, mid, p * 2) && query(l, r, mid + 1, cr, p * 2 + 1) && tree[2 * p].rval > tree[2 * p + 1].lval;
//            return query(l, r, cl, mid, p * 2) && query(l, r, mid + 1, cr, p * 2 + 1);
			qres3 res1 = query(l, r, cl, mid, p * 2);
			qres3 res2 = query(l, r, mid + 1, cr, p * 2 + 1);
			
			if (res1.ok && res2.ok)
			{
				return (qres3){res1.lval, res2.rval, true, res1.islt && res2.islt && res1.rval > res2.lval};
			}
			else if (res1.ok && !res2.ok)	
			{
				return (qres3){res1.lval, res2.rval, true, res1.islt};
			}
			else if (!res1.ok && res2.ok)
			{
				return (qres3){res2.lval, res2.rval, true, res2.islt};
			}
			else
			{
				return (qres3){0, 0, false, true};
			}
        }
    }
};
