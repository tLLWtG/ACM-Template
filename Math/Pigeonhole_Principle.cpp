#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'
#define debug(x) { cerr << #x << " = " << x << endl; }

/*-------------------------------------------*/

// 将 n+1 个物体，划分为 n 组，那么有至少一组有两个（或以上）的物体。
// 把 mn－1 个物体放入 n 个抽屉中，其中必有一个抽屉中至多有 m—1 个物体

// https://ac.nowcoder.com/acm/problem/257495
// 自动计算机

// 给定一个长度为 m 的序列 a，分别为 a_0, a_1, ... , a_m-1，一开始你拥有一个初始数为 x，
// 你的第 i 次操作会使得 x=(x+a_((i−1)%m))%n，请问至少多少次操作才能使 x 变成 0。
// 如果无论多少次操作均无法使 x=0，那么输出 −1。

// 由抽屉原理，n 轮操作后 x 一定循环。
// 而每一轮中的 m 次操作可以预处理出进行 i 次操作后在模意义下的偏差值。

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;
    ll n, m, x;
    cin >> n >> m >> x;
    vector<ll> pre(m + 1, 0), arr(m + 1);
    map<ll, ll> book;
    for (int i = 1; i <= m; ++i)
    {
        cin >> arr[i];
        pre[i] = (pre[i - 1] + arr[i]) % n;
        if (book.find(pre[i]) == book.end())
            book[pre[i]] = i;
    }
    ll ans = -1;
    for (int i = 1; i <= n; ++i)
    {
        ll goal = n - x;
        if (x == 0)
        {
            ans = (i - 1) * m;
            break;
        }
        else
        {
            if (book.find(goal) != book.end())
            {
                ans = (i - 1) * m + book[goal];
                break;
            }
        }
        x = (x + pre[m]) % n;
    }
    cout << ans << endl;
    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
