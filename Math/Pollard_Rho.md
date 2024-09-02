### Pollard_Rho

> for 1 ~ (1 << 64)
>
> max fac

```cpp
namespace millerRabin
{
    ll qpow(ll a, ll t, ll mod)
    {
        a %= mod;
        ll res = 1;
        while (t)
        {
            if (t & 1)
                res = (__int128)res * a % mod;
            a = (__int128)a * a % mod;
            t >>= 1;
        }
        return res;
    }

    const int primebook[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    bool isPrime(ll n)
    {
        if (n < 3 || n % 2 == 0)
            return n == 2;
        if (n <= 40)
        {
            for (ll a : primebook)
                if (a == n)
                    return 1;
            return 0;
        }
        ll u = n - 1, t = 0;
        while (u % 2 == 0)
            u /= 2, ++t;
        for (ll a : primebook)
        {
            ll v = qpow(a, u, n);
            if (v == 1)
                continue;
            ll s;
            for (s = 0; s < t; ++s)
            {
                if (v == n - 1)
                    break;
                v = (__int128)v * v % n;
            }
            if (s == t)
                return 0;
        }
        return 1;
    }
}

namespace pollardRho
{
    ll max_factor;
    ll Pollard_Rho(ll x)
    {
        ll s = 0, t = 0;
        ll c = (ll)rand() % (x - 1) + 1;
        int step = 0, goal = 1;
        ll val = 1;
        for (goal = 1;; goal *= 2, s = t, val = 1)
        {
            for (step = 1; step <= goal; ++step)
            {
                t = ((__int128)t * t + c) % x;
                val = (__int128)val * abs(t - s) % x;
                if ((step % 127) == 0)
                {
                    ll d = gcd(val, x);
                    if (d > 1)
                        return d;
                }
            }
            ll d = gcd(val, x);
            if (d > 1)
                return d;
        }
    }

    void func(ll x)
    {
        if (x <= max_factor || x < 2)
            return;
        if (millerRabin::isPrime(x))
        {
            max_factor = max(max_factor, x);
            return;
        }
        ll p = x;
        while (p >= x)
            p = Pollard_Rho(x);
        while ((x % p) == 0)
            x /= p;
        func(x), func(p);
    }

    ll fac(ll x)
    {
        srand((unsigned)time(0));
        max_factor = 0;
        func(x);
        return max_factor;
    }
}
```

