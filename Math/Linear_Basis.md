### Linear Basis

1. 插入

> 保证以下性质：
>
> 1. p[i]=0 时，只有 j>i 的 p[j] 的第 i 位可能为 1。
> 
> 2. p[i]!=0 时，整个线性基只有 p[i] 的第 i 位为 1，p[i] 的更高位都为 0，更低位可能为 1。

```cpp
using ull = unsigned long long;

ull p[64];

void insert(ull x)
{
    for (int i = 63; i >= 0; --i)
    {
        if (((x >> i) & 1ull) == 0)
            continue;
        if (p[i] == 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if ((x >> j) & 1ull)
                    x ^= p[j];
            }
            for (int j = i + 1; j < 64; ++j)
            {
                if ((p[j] >> i) & 1ull)
                    p[j] ^= x;
            }
            p[i] = x;
            return;
        }
        else
            x ^= p[i];
    }
}
```

2. 合并

> 直接把一个线性基插入另一个线性基。

3. 最大值、最小值、可构造
   
```cpp
ull qmax()
{
    ull res = 0;
    for (int i = 0; i <= 63; ++i)
        res = res ^ p[i];
}

// 特判：若线性基小于原集合，则原集合可构造出 0
ull qmin()
{
    ull res = 0;
    for (int i = 0; i <= 63; ++i)
        if (p[i])
        {
            res = p[i];
            break;
        }
    return res;
}

bool check(ull x)
{
    for (int i = 63; i >= 0; --i)
    {
        if (((x >> i) & 1ull) == 0)
            continue;
        x ^= p[i];
    }
    return x == 0;
}
```

4. 第 k 小

> 类似二进制分解，另外同 qmin，要特判 0。

```cpp
// 先把线性基存在的数塞进 B。
sort(B.begin(), B.end());
ull ans = 0;
// 特判
if (B.size() < n)
    k--;
for (auto b : B)
{
    if (k & 1)
        ans ^= b;
    k >>= 1;
}
if (k == 0)
    cout << ans << endl;
else
    cout << -1 << endl;
```


