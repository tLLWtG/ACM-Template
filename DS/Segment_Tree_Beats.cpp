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

/*
segment tree beats
可以以O((n + q)logn)的复杂度处理区间cmax / cmin, 区间求和的问题
如果在以上操作加上区间加, 复杂度上界为O((n + q)log^2n), 实际运用可能为O((n + q)logn)
*/

// 数组大小
#define maxn 100005

int N;
// 初始数组
int a[maxn];

class sgt
{
    // maxi: 子区间最大值, maxi2: 子区间严格次大值
    // maxi_cnt: ma的个数, tag: 是否需要push_down
    // sumi: 子区间求和
    struct tree
    {
        int maxi, maxi2;
        int maxi_cnt, tag;
        ll sumi;
    };
    tree t[maxn << 3];

public:
    void build(int p = 1, int cl = 1, int cr = N)
    {
        t[p].tag = 0;
        if (cl == cr)
        {
            t[p].sumi = t[p].maxi = a[cl];
            t[p].maxi_cnt = 1;
            return;
        }
        int lc = p << 1, rc = lc + 1, mid = (cl + cr) >> 1;
        build(lc, cl, mid);
        build(rc, mid + 1, cr);
        merge(p);
    }
    // 合并左右子区间信息(最大值、次大值等)
    void merge(int p)
    {
        int lc = p << 1, rc = lc + 1;
        t[p].sumi = t[lc].sumi + t[rc].sumi;
        if (t[lc].maxi > t[rc].maxi)
        {
            t[p].maxi = t[lc].maxi;
            t[p].maxi_cnt = t[lc].maxi_cnt;
            t[p].maxi2 = max(t[lc].maxi2, t[rc].maxi);
        }
        else if (t[rc].maxi > t[lc].maxi)
        {
            t[p].maxi = t[rc].maxi;
            t[p].maxi_cnt = t[rc].maxi_cnt;
            t[p].maxi2 = max(t[rc].maxi2, t[lc].maxi);
        }
        else
        {
            t[p].maxi = t[lc].maxi;
            t[p].maxi_cnt = t[lc].maxi_cnt + t[rc].maxi_cnt;
            t[p].maxi2 = max(t[lc].maxi2, t[rc].maxi2);
        }
    }
    // 更新左右子节点区间
    void push_down(int p)
    {
        if (!t[p].tag)
            return;
        t[p].tag = 0;
        int lc = p << 1, rc = lc + 1;
        if (t[lc].maxi > t[p].maxi)
        {
            t[lc].sumi -= 1ll * t[lc].maxi_cnt * (t[lc].maxi - t[p].maxi);
            t[lc].maxi = t[p].maxi;
            t[lc].tag = 1;
        }
        if (t[rc].maxi > t[p].maxi)
        {
            t[rc].sumi -= 1ll * t[rc].maxi_cnt * (t[rc].maxi - t[p].maxi);
            t[rc].maxi = t[p].maxi;
            t[rc].tag = 1;
        }
    }
    // for(a[l....r], cmin(a[i], x))
    // 如果最大值小于x, 直接返回
    // 如果x大于次大值，小于最大值, 更新sum
    // 如果x小于等于次大值, 递归更新
    void update_cmin(int l, int r, int x, int p = 1, int cl = 1, int cr = N)
    {
        if (cl > r || cr < l)
            return;
        if (cl != cr)
            push_down(p);
        if (cl >= l && cr <= r)
        {
            if (t[p].maxi <= x)
                return;
            if (t[p].maxi2 < x)
            {
                t[p].sumi -= 1ll * t[p].maxi_cnt * (t[p].maxi - x);
                t[p].maxi = x;
                t[p].tag = 1;
                return;
            }
        }
        int lc = p << 1, rc = lc + 1, mid = (cl + cr) / 2;
        update_cmin(l, r, x, lc, cl, mid);
        update_cmin(l, r, x, rc, mid + 1, cr);
        merge(p);
    }
    ll query_sum(int l, int r, int p = 1, int cl = 1, int cr = N)
    {
        if (cl > r || cr < l)
            return 0;
        push_down(p);
        if (cl >= l && cr <= r)
            return t[p].sumi;
        int lc = p << 1, rc = lc + 1, mid = (cl + cr) / 2;
        return query_sum(l, r, lc, cl, mid) + query_sum(l, r, rc, mid + 1, cr);
    }
    ll query_max(int l, int r, int p = 1, int cl = 1, int cr = N)
    {
        if (cl > r || cr < l)
            return 0;
        push_down(p);
        if (cl >= l && cr <= r)
            return t[p].maxi;
        int lc = p << 1, rc = lc + 1, mid = (cl + cr) / 2;
        return max(query_max(l, r, lc, cl, mid), query_max(l, r, rc, mid + 1, cr));
    }
    void clear()
    {
        memset(t + 1, 0, sizeof(tree) * (N << 2));
    }
};