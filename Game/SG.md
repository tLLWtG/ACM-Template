### SG

1. 公平组合游戏

> 1. 游戏有两个人参与，二者轮流做出决策，双方均知道游戏的完整信息；
> 
> 2. 任意一个游戏者在某一确定状态可以作出的决策集合只与当前的状态有关，而与游戏者无关；
> 
> 3. 游戏中的同一个状态不可能多次抵达，游戏以玩家无法行动为结束，且游戏一定会在有限步后以非平局结束。
> 
> P-position(Previous-position)：必败态(简记为 P) 。
> 
> N-position(Next-position)：必胜态(简记为 N)。

2. 博弈图

> 1. 没有后继状态的状态是必败状态。
> 2. 一个状态是必胜状态当且仅当存在至少一个必败状态为它的后继状态。
> 3. 一个状态是必败状态当且仅当它的所有后继状态均为必胜状态。

3. Sprague-Grundy 定理

> SG(x) = mex({SG(y)|x->y})
> 
> SG(x) = 0 时，称 x 为必败态，反之为必胜态
> 
> SG(x+y) = SG(x)^SG(y)
> 
> 对于由 n 个有向图游戏组成的组合游戏，设它们的起点分别为 s1, s2,..., sn，
> 
> 则当且仅当 SG(s1)^SG(s2)^...^SG(sn) != 0 时，这个游戏是先手必胜的。

4. mex 函数

```cpp
int mex(auto v)
{
    unordered_set<int> S;
    for (auto e : v)
        S.insert(e);
    for (int i = 0;; ++i)
        if (S.find(i) == S.end())
            return i;
}
```

5. multi-nim 打表

```cpp
void SG()
{
    vector<int> sg(510, 0), vis;
    sg[0] = 0, sg[1] = 1;
    for (int i = 2; i <= 505; ++i)
    {
        vis.assign(510, 0);
        for (int j = 1; j <= i; ++j)
            vis[sg[i - j]] = true;
        for (int j = 1; j < i; ++j)
            vis[sg[j] ^ sg[i - j]] = true;
        int j = 0;
        while (vis[j])
            sg[i] = ++j;
    }
}
```

