### Manacher

> 下标从 0 开始。
> 
> 输入 abcd，返回数组的位置对应为：#a#b#c#d#，且值要再 -1 才是当前位置最长回文长度。

```cpp
vector<int> manacher(vector<int> s)
{
    vector<int> t{0};
    for (auto c : s)
    {
        t.push_back(c);
        t.push_back(0);
    }
    int n = t.size();
    vector<int> r(n);
    for (int i = 0, j = 0; i < n; i++)
    {
        if (2 * j - i >= 0 && j + r[j] > i)
            r[i] = min(r[2 * j - i], j + r[j] - i);
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]])
            r[i] += 1;
        if (i + r[i] > j + r[j])
            j = i;
    }
    return r;
}

void solve()
{
    string s;
    cin >> s;
    vector<int> t(s.size());
    for (int i = 0; i < s.size(); ++i)
        t[i] = s[i];
    auto v = manacher(t);
    int ans = 0;
    for (auto x: v)
        ans = max(ans, x - 1);
    cout << ans << endl;
}
```

