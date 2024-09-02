### Modular_Multiplicative_Inverse

1. with exgcd

> a * x === 1 (mod b)   =>   a * x + b * y == 1
>
> ans = (a * b * c) % p;
>
> to get rid of a
>
> ans = ans * x % p;

```cpp
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

ll inv(ll a, ll b)
{
    ll x, y;
    ll d = exgcd(a, b, x, y);
    // smallest x
    if (d == 1)
        return (x % b + b) % b;
    return -1;
}
```

2. if b is prime

> according to Fermat's little theorem

```cpp
ll inv(ll a, ll b)
{
    ll ans = 1, M = b;
    b -= 2;
    while (b)
    {
        if (b & 1)
            ans = (a * ans) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return ans;
}
```

