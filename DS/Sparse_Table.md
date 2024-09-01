### Sparse_Table

```cpp
class ST
{
private:
    int n, MAXN;
    vector<vector<int>> stable;

public:
    vector<int> arr;
    ST(int _n) : n(_n), MAXN(_n + 5)
    {
        arr.resize(MAXN);
        stable = vector<vector<int>>(__lg(MAXN) + 1, vector<int>(MAXN));
    }
    void init()
    {
        for (int i = 1; i <= n; ++i)
            stable[0][i] = arr[i];
        for (int i = 1; i <= __lg(MAXN); ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                stable[i][j] = max(stable[i - 1][j], stable[i - 1][j + (1 << (i - 1))]);
    }
    int query(int l, int r)
    {
        int s = __lg(r - l + 1);
        return max(stable[s][l], stable[s][r - (1 << s) + 1]);
    }
};
```

