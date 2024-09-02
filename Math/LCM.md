### LCM

1. 两个数

```cpp
ll lcm1(ll a, ll b)
{
    return a / gcd(a, b) * b;
}
```

2. multiple numbers

```cpp
ll lcm2(vector<ll> a)
{
    ll res = 1;
    for (auto x : a)
        res = lcm1(res, x);
    return res;
}
```

