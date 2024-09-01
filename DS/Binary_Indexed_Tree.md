### Binary_Indexed_Tree

> prefix sum version
> 
> also able to update range with difference

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
```

