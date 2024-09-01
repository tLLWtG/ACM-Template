### DP_Digit

> 记忆化搜索或循环迭代递推或（人类智慧）
> 
> 求 [l, r] 答案时，可考虑 [0, r] - [0, l - 1]
> 
> 数字间无关系时，可考虑每个数字分别 dp 一次
> 
> 考虑贡献
> 
> 可拓展到其他进制

1. 给定正整数 n，返回在 [1, n] 范围内无重复数字的正整数的个数。

```cpp
ll digitDP(ll n)
{
    string s = to_string(n);
    int len = s.length();
    vector<vector<ll>> dp(len, vector<ll>(1 << 10, -1));
    // is_limit 是否受 n 限制，is_num 前面是否已经填了数字
    function<ll(int, int, bool, bool)> f = [&](int cur, int mask, bool is_limit, bool is_num) -> ll
    {
        if (cur == len)
            return is_num; // is_num 为 true 表示得到了一个合法数字
        if (!is_limit && is_num && dp[cur][mask] != -1)
            return dp[cur][mask];
        ll res = 0;
        if (!is_num) // 可以跳过当前数位
            res += f(cur + 1, mask, false, false);
        int up = is_limit ? s[cur] - '0' : 9;  // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[cur]
        for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
            if ((mask >> d & 1) == 0)          // d 不在 mask 中
                res += f(cur + 1, mask | (1 << d), is_limit && d == up, true);
        if (!is_limit && is_num)
            dp[cur][mask] = res;
        return res;
    };
    return f(0, 0, true, false);
}
```

2. 求 [a,b] 范围的所有整数中，每个数码(digit)各出现了多少次

```cpp
namespace count
{
    vector<ll> digitDP(ll n)
    {
        string s = to_string(n);
        int len = s.length();
        vector<vector<ll>> dp(len, vector<ll>(14, -1));
        vector<ll> ans(10);
        function<ll(int, bool, bool, int, int)> f = [&](int cur, bool is_limit, bool is_num, int d, int sumi) -> ll
        {
            if (cur == len)
                return sumi;
            if (!is_limit && is_num && dp[cur][sumi] != -1)
                return dp[cur][sumi];
            ll res = 0;
            if (!is_num)
                res += f(cur + 1, false, false, d, sumi);
            int up = is_limit ? s[cur] - '0' : 9;
            for (int dd = 1 - is_num; dd <= up; ++dd)
                res += f(cur + 1, is_limit && dd == up, true, d, sumi + (dd == d));
            if (!is_limit && is_num)
                dp[cur][sumi] = res;
            return res;
        };
        for (int i = 0; i < 10; ++i)
        {
            dp.assign(len, vector<ll>(14, -1));
            ans[i] = f(0, true, false, i, 0);
        }
        return ans;
    }

    int main()
    {
        // clock_t st = clock(), ed;
        ios::sync_with_stdio(0);
        cin.tie(0);
        // cout << setprecision(15) << fixed;
        ll a, b;
        cin >> a >> b;
        vector<ll> aa(digitDP(a - 1));
        vector<ll> bb(digitDP(b));
        for (int i = 0; i < 10; ++i)
            cout << bb[i] - aa[i] << " ";
        cout << endl;
        // ed = clock();
        // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
        // cout << "Total time: " << endtime << endl;
        return 0;
    }
}
```

