### Lucas

```cpp
namespace comb
{
    int n, p;
    vector<int> inv, fac, finv;
    void Preprocess(int _n, int _p)
    {
        n = _n;
        p = _p;
        inv.resize(n + 5);
        fac.resize(n + 5);
        finv.resize(n + 5);
        inv[1] = 1;
        for (int i = 2; i <= n + 1; ++i)
            inv[i] = (ll)(p - p / i) * inv[p % i] % p;
        fac[0] = 1;
        for (int i = 1; i <= n + 1; ++i)
            fac[i] = (ll)fac[i - 1] * i % p;
        finv[0] = 1;
        for (int i = 1; i <= n + 1; ++i)
            finv[i] = (ll)finv[i - 1] * inv[i] % p;
    }
    int C(int x, int y) { return (ll)fac[x] * finv[y] % p * finv[x - y] % p; }
}

ll Lucas(ll n, ll m, ll p)
{
    if (m == 0)
        return 1;
    if (n % p < m % p)
        return 0;
    return (comb::C(n % p, m % p) * Lucas(n / p, m / p, p)) % p;
}
```

