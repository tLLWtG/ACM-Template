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

// Anti-SG 游戏
// 决策集合为空的游戏者赢。
// 其余规则与 SG 游戏相同。

// SJ 定理
// 对于 Anti-SG 游戏，如果我们规定当局面中所有单一游戏的 SG 值为 0 时，游戏结束，则先手必胜当且仅当：
// 游戏的 SG 函数不为 0 且游戏中某个单一游戏的 SG 函数值大于 1。
// 游戏的 SG 函数为 0 且没有某个单一游戏的 SG 函数大于 1。

// anti-nim
// 有 n 堆石子，两个人可以从任意一堆石子中拿任意多个石子(不能不拿)，拿走最后一个石子的人失败。
// 对于这个游戏，先手必胜有两种情况：
// 当每堆石子都只有一个，且游戏的 SG 值为 0
// 至少一堆石子多于一个，且游戏的 SG 值不为 0

bool anti_nim()
{
    int n, cnt = 0, sg = 0, x;
    cin >> n;
    while (n--)
    {
        cin >> x;
        if (x > 1)
            ++cnt;
        sg ^= x;
    }
    if ((!cnt && sg == 0) || (cnt && sg != 0))
        return true;
    else
        return false;
}