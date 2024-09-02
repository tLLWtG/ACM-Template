### Mo's_Algorithm

```cpp
namespace normalMo
{
    const int MAXN = 30005, MAXQ = 200005, MAXM = 1000005;
    int sq;
    struct query // 把询问以结构体方式保存
    {
        int l, r, id;
        bool operator<(const query &o) const // 重载<运算符，奇偶化排序
        {
            // 这里只需要知道每个元素归属哪个块，而块的大小都是sqrt(n)，所以可以直接用l/sq
            if (l / sq != o.l / sq)
                return l < o.l;
            if (l / sq & 1)
                return r < o.r;
            return r > o.r;
        }
    } Q[MAXQ];
    int A[MAXN], ans[MAXQ], cnt[MAXM], cur = 0, l = 1, r = 0;
    void add(int p)
    {
        if (cnt[A[p]] == 0)
            cur++;
        cnt[A[p]]++;
    }
    void del(int p)
    {
        cnt[A[p]]--;
        if (cnt[A[p]] == 0)
            cur--;
    }
    void solve()
    {
        int n;
        cin >> n;
        sq = sqrt(n);
        for (int i = 1; i <= n; ++i)
            cin >> A[i];
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i)
            cin >> Q[i].l >> Q[i].r, Q[i].id = i; // 把询问离线下来
        sort(Q, Q + q);                           // 排序
        for (int i = 0; i < q; ++i)
        {
            while (l > Q[i].l)
                add(--l);
            while (r < Q[i].r)
                add(++r);
            while (l < Q[i].l)
                del(l++);
            while (r > Q[i].r)
                del(r--);
            ans[Q[i].id] = cur; // 储存答案
        }
        for (int i = 0; i < q; ++i)
            cout << ans[i] << endl; // 按编号顺序输出
    }
}
```

