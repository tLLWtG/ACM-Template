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

// 启发式合并：将小的集合合并到大的集合中，以降低平均时间复杂度，一般为 nlogn。

// 1. 树上启发式合并 (dsu on tree)

// from oiwiki

// 给出一棵 n 个节点以 1 为根的树，节点 u 的颜色为 c_u，现在对于每个结点 u 询问 u 子树里一共出现了多少种不同的颜色。
// (n <= 10^5)

namespace solve
{
    const int N = 1e5 + 5;
    int n;
    // g[u]: 存储与 u 相邻的结点
    vector<int> g[N];
    // sz: 子树大小
    // big: 重儿子
    // col: 结点颜色
    // L[u]: 结点 u 的 DFS 序
    // R[u]: 结点 u 子树中结点的 DFS 序的最大值
    // Node[i]: DFS 序为 i 的结点
    // ans: 存答案
    // cnt[i]: 颜色为 i 的结点个数
    // totColor: 目前出现过的颜色个数
    int sz[N], big[N], col[N], L[N], R[N], Node[N], totdfn;
    int ans[N], cnt[N], totColor;
    void add(int u)
    {
        if (cnt[col[u]] == 0)
            ++totColor;
        cnt[col[u]]++;
    }
    void del(int u)
    {
        cnt[col[u]]--;
        if (cnt[col[u]] == 0)
            --totColor;
    }
    int getAns() { return totColor; }
    void dfs0(int u, int p)
    {
        L[u] = ++totdfn;
        Node[totdfn] = u;
        sz[u] = 1;
        for (int v : g[u])
            if (v != p)
            {
                dfs0(v, u);
                sz[u] += sz[v];
                if (!big[u] || sz[big[u]] < sz[v])
                    big[u] = v;
            }
        R[u] = totdfn;
    }
    void dfs1(int u, int p, bool keep)
    {
        // 计算轻儿子的答案
        for (int v : g[u])
            if (v != p && v != big[u])
            {
                dfs1(v, u, false);
            }
        // 计算重儿子答案并保留计算过程中的数据（用于继承）
        if (big[u])
        {
            dfs1(big[u], u, true);
        }
        for (int v : g[u])
            if (v != p && v != big[u])
            {
                // 子树结点的 DFS 序构成一段连续区间，可以直接遍历
                for (int i = L[v]; i <= R[v]; i++)
                {
                    add(Node[i]);
                }
            }
        add(u);
        ans[u] = getAns();
        if (keep == false)
        {
            for (int i = L[u]; i <= R[u]; i++)
            {
                del(Node[i]);
            }
        }
    }
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &col[i]);
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs0(1, 0);
        dfs1(1, 0, false);
        for (int i = 1; i <= n; i++)
            printf("%d%c", ans[i], " \n"[i == n]);
        return 0;
    }
}