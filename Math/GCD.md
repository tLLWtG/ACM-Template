### GCD

1. 减法

```cpp
ll gcd1(ll a, ll b)
{
    // if (a == 1 || b == 1)
    //     return 1;
    // if (a == b)
    //     return a;
    // if (a > b)
    //     return gcd(a - b, b);
    // return gcd(a, b - a);
    while (a != b)
    {
        if (a == 1 || b == 1)
            return 1;
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
```

2. Euclid

```cpp
ll gcd2(ll a, ll b)
{
    while (b != 0)
    {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}
```

3. multiple numbers

```cpp
ll gcd3(vector<ll> &v)
{
    ll res = v[0];
    for (int i = 1; i < v.size(); i++)
        res = gcd2(res, v[i]);
    return res;
}
```

