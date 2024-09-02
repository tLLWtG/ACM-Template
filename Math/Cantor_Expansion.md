### Cantor_Expansion

1. 康托展开
   
> 用于求某排列的排名
> 
> $rk=1+\sum_{i=1}^{n}{A[i]×(n−i)!}$
> 
> 其中 $A[i]$ 为 $\sum_{j=i}^{n}{[a[j]<a[i]]}$，朴素求 $A$ 是 $O(n^2)$，可以考虑树状数组优化。

```cpp
class biTree
{
private:
    int MAXN;
    vector<ll> tree;
    ll lowbit(ll x)
    {
        return x & (-x);
    }

public:
    biTree(int _MAXN = 100005) : MAXN(_MAXN)
    {
        tree.resize(MAXN);
    }
    void update(ll index, ll x)
    {
        for (ll pos = index; pos < MAXN; pos += lowbit(pos))
            tree[pos] += x;
    }
    ll query(ll n)
    {
        ll sum = 0;
        for (ll i = n; i; i -= lowbit(i))
            sum += tree[i];
        return sum;
    }
    // (a, b]
    ll query(ll a, ll b)
    {
        return query(b) - query(a);
    }
};

ll cantor()
{
    ll ans = 1, MOD = 998244353;

    int n;
    cin >> n;
    vector<ll> arr(n + 1), A(n + 1), fac(n + 1);
    biTree tree(n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], fac[i] = fac[i - 1] * i % MOD;

    for (int i = n; i >= 1; --i)
    {
        tree.update(arr[i], 1);
        A[i] = tree.query(arr[i] - 1);
    }
    for (int i = 1; i <= n; ++i)
    {
        ans += A[i] * fac[n - i];
        ans %= MOD;
    }

    return ans;
}
```

2. 逆康托展开

> 类似于进制转换，不断 $\mod (n-i)!$, $/(n-1)!$ 就可以得到 $A$ 数组，然后就可以还原出原排列。

```cpp
vector<int> incantor(int x, int n) {
    x--;
    vector<int> res(n), fac(n);
    fac[0] = 1;
    for (int i = 1; i < n; ++i)
        fac[i] = fac[i - 1] * i;
    bool st[10] = {0};
    for (int i = 0; i < n; ++i)
    {
        int cnt = x / fac[n - i - 1]; // 比a[i]小且没有出现过的数的个数
        x %= fac[n - i - 1];
        for (int j = 1;j <= n; ++j)
        {
            if (st[j])
                continue;
            if (!cnt)
            {
                st[j] = 1;
                res[i] = j;
                break;
            }
            cnt--;
        }
    }
    return res;
}
```

