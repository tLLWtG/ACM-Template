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

// Multi-SG 游戏
// Multi-SG 游戏规定，在符合拓扑原则的前提下，一个单一游戏的后继可以为多个单一游戏
// Multi-SG 其他规则与 SG 游戏相同。
// 对于一个状态来说，不同的划分方法会产生多个不同的后继，而在一个后继中可能含有多个独立的游戏
// 一个后继状态的 SG 值即为后继状态中独立游戏的异或和
// 该状态的 SG 值即为后继状态的SG值中未出现过的最小值

// multi-nim
// 有 n 堆石子，两个人可以从任意一堆石子中拿任意多个石子(不能不拿)，
// 或把一堆数量不少于 2 石子分为两堆不为空的石子，最后取完者胜利。
// 操作一与普通的 nim 游戏等价，
// 操作二实际上是将一个游戏分解为两个游戏，根据 SG 定理，我们可以通过异或运算把两个游戏连接到一起，作为一个后继状态。
// SG(3)的后继状态有{(0), (1), (2), (1, 2)}他们的 SG 值分别为{0, 1, 2, 3}，因此 SG(3) = mex{0, 1, 2, 3} = 4。
//          = x−1   (x%4 == 0)
// SG(x)    = x     (x%4 == 1 or 2)
//          = x+1   (x%4 == 3)

bool multi_nim()
{
    int n, sg = 0, x;
    cin >> n;
    while (n--)
    {
        cin >> x;
        if (x % 4 == 0)
            sg ^= x - 1;
        else if (x % 4 == 3)
            sg ^= x + 1;
        else
            sg ^= x;
    }
    return sg;
}