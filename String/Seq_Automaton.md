### Seq_Automaton

> nxt[i][j] 表示 i 位置后第一个出现的 j 的 位置。

```cpp
vector nxt(n + 1, vector<int>(m + 1));
for (int i = n; i >= 1; --i)
{
    for (int j = 1; j <= m; ++j)
        nxt[i - 1][j] = nxt[i][j];
    nxt[i - 1][a[i]] = i;
}

// 判断 b 序列是否是其字串
for (int i = 1; i <= t; ++i)
    cin >> b[i];
int cur = 0, appear = 1;
for (int i = 1; i <= t; ++i)
{
    cur = nxt[cur][b[i]];
    if (cur == 0)
    {
        appear = 0;
        break;
    }
}
if (appear) cout << "Yes" << endl;
else cout << "No" << endl;
```

