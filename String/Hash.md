### Hash

1. string hash

```cpp
const int M = 1e9 + 7;
const int B = 233;

int get_hash(const string &s)
{
    int res = s[0], sz = s.size();
    for (int i = 1; i < sz; ++i)
        res = (ll(res) * B + s[i]) % M;
    return res;
}
```

2. double hash

```cpp
const int mod1 = 19260817;
const int mod2 = 1e9 + 7;

pii get_hash(string &s)
{
    ll r1 = 0, r2 = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        r1 = (r1 * 131 + s[i]) % mod1;
        r2 = (r2 * 233 + s[i]) % mod2;
    }
    return {r1, r2};
}
```

3. substring hash(with prefix)

```cpp
const int N = 1e5 + 5, P = 133;
unsigned long long h[N], p[N];

unsigned long long query(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

void prepro(string &str)
{
    // index start from 1
    p[0] = 1;
    h[0] = 0;
    int sz = str.size();
    for (int i = 0; i < sz; i++)
    {
        p[i + 1] = p[i] * P;
        h[i + 1] = h[i] * P + str[i];
    }
}
```

4. double substring hash(with prefix)

```cpp
namespace Double_Pre_Hash
{
    using pll = pair<ll, ll>;
    static const int N = 1048576 * 2 + 5, P = 133;
    const ll mod = 1000000033;
    const ll mod2 = 1000000007;
    ll h[N], p[N];
    ll h2[N], p2[N];

    map<pll, ll> ID;
    ll cnt = 0;

    ll query(int l, int r)
    {
        ll res = ((h[r] - h[l - 1] * p[r - l + 1]) % mod + mod) % mod;
        ll res2 = ((h2[r] - h2[l - 1] * p2[r - l + 1]) % mod2 + mod2) % mod2;
        if (ID.find({res, res2}) == ID.end())
            ID[{res, res2}] = ++cnt;
        return ID[{res, res2}];
    }

    void prepro(string &str)
    {
        // index start from 1
        p[0] = 1;
        h[0] = 0;
        p2[0] = 1;
        h2[0] = 0;
        int sz = str.size();
        for (int i = 0; i < sz; i++)
        {
            p[i + 1] = (p[i] * P) % mod;
            h[i + 1] = (h[i] * P + str[i]) % mod;
            p2[i + 1] = (p2[i] * P) % mod2;
            h2[i + 1] = (h2[i] * P + str[i]) % mod2;
        }
    }
}
```

