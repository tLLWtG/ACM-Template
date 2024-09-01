### k-D_Tree

> 查询某个点集离某个点距离前m小的点

```cpp
namespace KDtree
{
    const int maxn = 2e5 + 100;
    const int K = 3;
    int idx; // 存储超平面的维度
    struct Node
    {
        ll a[K]; // 分维度位置
        int id;  // 输入数据的标识
        int way; // 超平面的维度号
        bool operator<(const Node &oth) const
        { // 根据超平面维度决定比较函数
            return a[idx] < oth.a[idx];
        }
    } p[maxn];          // 存初始数据
    Node pt[4 * maxn];  // 存KDTree数据
    int flag[4 * maxn]; // 存节点是否存在数据
    priority_queue<pair<ll, Node>> pq;
    ll dis_sqr(ll a, ll b)
    { // 距离平方
        return (a - b) * (a - b);
    }
    double var[K];
    void build(int l, int r, int rt, int dept)
    { // 注意l要从0开始
        if (l > r)
            return;
        flag[rt] = 1; // 当前节点存在
        int lc = rt << 1;
        int rc = rt << 1 | 1;
        flag[lc] = flag[rc] = -1; // 初始化子节点不存在
        /*                                              //根据方差选择超平面
        int maxx = 0;
        for(int i = 0; i < K; i++){
            double avg = var[i] = 0.0;
            for(int j = l; j <= r; j++){
                avg += p[j].a[i];
            }
            avg /= (r - l + 1);
            for(int j = l; j <= r; j++){
                var[i] += (avg - p[j].a[i]) * (avg - p[j].a[i]);
            }
            var[i] /= (r - l + 1);
            if(var[i] > var[maxx]) maxx = i;
        }
        idx = maxx;
        */
        idx = dept % K; // 随机选择超平面
        int mid = (l + r) >> 1;
        nth_element(p + l, p + mid, p + r + 1); // 分为左右子树
        pt[rt] = p[mid];
        pt[rt].way = idx; // 若采用方差选择超平面，则记录使用的哪一维
        build(l, mid - 1, lc, dept + 1);
        build(mid + 1, r, rc, dept + 1);
    }
    void query(Node &nd, int m, int rt, int dept)
    { // 查询离nd点前m小的点
        if (flag[rt] == -1)
            return;                    // 节点不存在
        pair<ll, Node> cur(0, pt[rt]); // 计算当前节点的距离
        for (int i = 0; i < K; i++)
        {
            cur.first += dis_sqr(pt[rt].a[i], nd.a[i]);
        }
        int dim = dept % K; // 随机选择超平面
        // int dim = pt[rt].way;                        //方差选择超平面
        bool fg = 0; // 判断右儿子是否存在
        int lc = rt << 1;
        int rc = rt << 1 | 1;
        if (nd.a[dim] >= pt[rt].a[dim])
            swap(lc, rc); // nd在当前分维上的大小大于等于rt在当前分维上的大小
        if (~flag[lc])
            query(nd, m, lc, dept + 1); // lc != -1
        if (pq.size() < m)
        {
            pq.push(cur);
            fg = 1;
        } // 队列未满
        else
        {
            if (cur.first < pq.top().first)
            { // 当前节点更优
                pq.pop();
                pq.push(cur);
            }
            if (dis_sqr(nd.a[dim], pt[rt].a[dim]) < pq.top().first)
            { // 右儿子内可能存在更优点
                fg = 1;
            }
        }
        if (~flag[rc] && fg)
        { // 访问右儿子
            query(nd, m, rc, dept + 1);
        }
    }
    // example
    void solve()
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++)
        { // 输入原有的n个点
            for (int j = 0; j < 3; j++)
            {
                cin >> p[i].a[j];
            }
            p[i].id = i;
        }
        build(0, n - 1, 1, 0); // 建树
        while (m--)
        { // 对于新的m个点查询
            while (!pq.empty())
                pq.pop();
            Node nd;
            cin >> nd.a[0] >> nd.a[1] >> nd.a[2];
            query(nd, 1, 1, 0);
            nd = pq.top().second;
            cout << nd.a[0] << ' ' << nd.a[1] << ' ' << nd.a[2] << '\n';
        }
    }
}
```

