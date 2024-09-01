### Difference

1. 1d

```cpp
int diff_1[MAXN];

void insert_1(int l, int r, int val)
{
    diff_1[l] += val;
    diff_1[r + 1] -= val;
}

void build_1(int n)
{
    int cur = 0;
    for (int i = 1; i <= n; ++i)
    {
        cur += diff_1[i];
        arr[i] = cur;
    }
}
```

2. 2d

```cpp
// 2d -> 1d

int diff_2[MAXN][MAXN];

void insert_2_v1(int x1, int y1, int x2, int y2, int val)
{
    for (int i = x1; i <= x2; ++i)
    {
        diff_2[i][y1] += val;
        diff_2[i][y2 + 1] -= val;
    }
}

void build_2_v1(int n, int m)
{
    for (int i = 1; i <= n; ++i)
    {
        int cur = 0;
        for (int j = 1; j <= m; ++j)
        {
            cur += diff_2[i][j];
            mat[i][j] = cur;
        }
    }
}

// 2d

void insert_2_v2(int x1, int y1, int x2, int y2, int val)
{
    diff_2[x1][y1] += val;
    diff_2[x2 + 1][y2 + 1] += val;
    diff_2[x1][y2 + 1] -= val;
    diff_2[x2 + 1][y1] -= val;
}

void build_2_v2(int n, int m)
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            mat[i][j] = diff_2[i][j] + mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
}
```

3. 对角线差分

`rl[x + y], lr[x - y + n]`

4. 差分用于区间去重

```cpp
// 对不符合的区间加上 1，则符合的区间累加后一定为 0，由此可以进行计数
int lr[MAXN][MAXN];
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
    {
        lr[i][j] += lr[i][j - 1];
        if (!lr[i][j] && i <= j)
            ++ans;
    }
```

