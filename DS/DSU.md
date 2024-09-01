### DSU

1. 普通并查集

```cpp
class DSU
{
private:
    int n;
    vector<int> fa, sz;

public:
    DSU(int _n) : n(_n)
    {
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x)
    {
        if (fa[x] == x)
            return x;
        else
        {
            fa[x] = find(fa[x]);
            return fa[x];
        }
    }
    void merge(int x, int y)
    {
        int xfa = find(x), yfa = find(y);
        if (xfa == yfa)
            return;
        if (sz[xfa] <= sz[yfa])
        {
            sz[yfa] += sz[xfa];
            fa[xfa] = yfa;
        }
        else
        {
            sz[xfa] += sz[yfa];
            fa[yfa] = xfa;
        }
    }
    int get_size(int x)
    {
        return sz[find(x)];
    }
};
```

2. 带权并查集（以点到根的距离为例）

```cpp
// 1. 路径压缩
int FindSet(int x) {
    if (x == parent[x])
		return x;
    else {
		int t = parent[x]; //记录原父节点编号
		parent[x] = FindSet(parent[x]); //父节点变为根节点，此时value[x]=父节点到根节点的权值
		value[x] += value[t]; //当前节点的权值加上原本父节点的权值
         return parent[x]
    }
}

// 2. 一种合并方式（依题目变化）
//
// 已知 x，y 根节点分别为 xRoot，yRoot，如果有了 x、y 之间的关系，
// 得求出 xRoot 与 yRoot 这条边的权值是多少，很显然 x 到 yRoot 两条路径的权值之和应该相同
// 	int xRoot = FindSet(x);
//	int yRoot = FindSet(y);
//	if (xRoot != yRoot)
//	{
//		parent[xRoot] = yRoot;
//		value[xRoot] = -value[x] + value[y] + s;
//	}
```

3. 种类并查集（以食物链为例）

> 我们可以用一个三倍大小的并查集进行维护，用 i+n 表示 i 的捕食对象，而 i+2n 表示 i 的天敌

```cpp
int main()
{
    int n = read(), m = read(), ans = 0;
    init(n * 3); //i吃i+n，被i+2n吃
    for (int i = 0; i < m; ++i)
    {
        int opr, x, y;
        scanf("%d%d%d", &opr, &x, &y);
        if (x > n || y > n) //特判x或y不在食物链中的情况
            ans++;
        else if (opr == 1)
        {
            if (query(x, y + n) || query(x, y + 2 * n)) //如果已知x吃y，或者x被y吃，说明这是假话
                ans++;
            else
            {
                merge(x, y);                 //这是真话，则x和y是一族
                merge(x + n, y + n);         //x的猎物和y的猎物是一族
                merge(x + 2 * n, y + 2 * n); //x的天敌和y的天敌是一族
            }
        }
        else if (opr == 2)
        {
            if (query(x, y) || query(x, y + 2 * n)) //如果已知x与y是一族，或者x被y吃，说明这是假话
                ans++;
            else
            {
                merge(x, y + n);         //这是真话，则x吃y
                merge(x + n, y + 2 * n); //x的猎物吃y的猎物
                merge(x + 2 * n, y);     //x的天敌吃y的天敌，或者说y吃x的天敌
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

