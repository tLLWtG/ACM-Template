#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

#define debug(x)                          \
    {                                     \
        cerr << #x << " = " << x << endl; \
    }
#define debugfull(x)                                                      \
    {                                                                     \
        cerr << #x << " = " << x << " (line " << __LINE__ << ")" << endl; \
    }

/*-------------------------------------------*/

// (1) nim 游戏
// SG(x) = x
// a1^a2^...^an != 0 即必胜

bool nim(int n, vector<int> &arr)
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans ^= arr[i];
    return ans;
}

// (2) 威佐夫博弈
// 有两堆各若干个物品，两个人轮流从任一堆取至少一个或同时从两堆中取同样多的物品
// 每次至少取一个，至多不限，最后取完者胜利。
// 若两堆物品的初始值为 (x,y)，且 x < y，则令 z = y-x；
// 记 w = (int)((sqrt(5)+1)/2*z)
// 若 w == x，则先手必败，否则先手必胜。

bool Wythoff(int x, int y)
{
    if (x > y)
        swap(x, y);
    int z = y - x;
    if ((int)((sqrt(5) + 1) / 2 * z) == x)
        return false; // 先手必败
    else
        return true; // 先手必胜
}

// (3) 巴什博弈
// 一堆 n 个物品，两个人轮流从中取出 1~m 个，最后取完者胜利。
// 同余定理：n = k∗(m+1)+r，先者拿走 r 个，那么后者无论拿走几个，先者只要的数目使和为 m+1，那么先手必赢。
// 反之若 n = k∗(m+1)，那么先手无论怎样都会输。

bool Bash(int n, int m)
{
    if (n % (m + 1))
        return true; // 先手获胜
    else
        return false; // 后手获胜
}

// (4) 斐波那契博弈
// 有 n 个物品，两人轮流取物品，先手最少取一个，至多无上限，但不能把物品取完，
// 之后每次取的物品数不能超过上一次取的物品数的二倍且至少为一件，取走最后一件物品的人获胜。
// 先手胜当且仅当 n 不是斐波那契数。

bool fib(int n)
{
    int a = 1, b = 1, c = 1;
    while (c <= n)
    {
        if (c == n)
            return false; // 后手获胜
        c = a + b;
        a = b;
        b = c;
    }
    return true; // 先手获胜
}

// (5) 树的删边游戏
// 给出一个有 N 个点的树，有一个点作为树的根节点。
// 游戏者轮流从树中删去边，删去一条边后，不与根节点相连的部分将被移走。最后删去者胜利。
// 叶子节点的 SG 值为 0；中间节点的 SG 值为它的所有子节点的 SG 值加 1 后的异或和。

// (6) 无向图的删边游戏
// 给出一个有 N 个点的树，有一个点作为树的根节点。
// 游戏者轮流从树中删去边，删去一条边后，不与根节点相连的部分将被移走。谁无法移动谁输。
// 由 Fusion Principle，
// 我们可以对无向图做如下改动：将图中的任意一个偶环缩成一个新点，任意一个奇环缩成一个新点加一个新边；
// 所有连到原先环上的边全部改为与新点相连。这样的改动不会影响图的 SG 值。
// 这样的话，我们可以将任意一个无向图改成树结构，“无向图的删边游戏”就变成了“树的删边游戏”。