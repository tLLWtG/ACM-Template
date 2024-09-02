### Gospers_Hack

```cpp
void GospersHack(int k, int n)
{
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    while (cur < limit)
    {
        // do something
        int lb = cur & -cur;
        int r = cur + lb;
        cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
        // or：cur = (((r ^ cur) >> 2) / lb) | r;
    }
}

// GospersHack(3, 5)

// 00111
// 01011
// 01101
// 01110
// 10011
// 10101
// 10110
// 11001
// 11010
// 11100
```

