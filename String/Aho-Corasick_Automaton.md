### Aho-Corasick_Automaton

1. normal version

```cpp
class AC
{
private:
    const static int N = 500005;
    int tr[N][26], val[N], fail[N], cnt;
    queue<int> q;

public:
    void insert(const string &s)
    {
        int cur = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            int v = s[i] - 'a';
            if (!tr[cur][v])
                tr[cur][v] = ++cnt;
            cur = tr[cur][v];
        }
        ++val[cur];
    }
    void build()
    {
        for (int i = 0; i < 26; ++i)
            if (tr[0][i])
                q.push(tr[0][i]);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i)
                if (tr[u][i])
                    fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
                else
                    tr[u][i] = tr[fail[u]][i];
        }
    }
    int query(const string &s)
    {
        int cur = 0, ans = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            cur = tr[cur][s[i] - 'a'];
            for (int t = cur; t && ~val[t]; t = fail[t])
                ans += val[t], val[t] = -1;
        }
        return ans;
    }
};
```

2. improved with topo

```cpp
class AC_topo
{
private:
    const static int maxn = 5000005;
    int cnt;
    int indeg[maxn];
    queue<int> q;
    struct trie_node
    {
        int son[27];
        int fail;
        int flag;
        int ans;
        void init()
        {
            memset(son, 0, sizeof(son));
            ans = fail = flag = 0;
        }
    } trie[maxn];

public:
    int vis[maxn], rev[maxn];
    void init(int n)
    {
        for (int i = 0; i <= cnt; ++i)
            trie[i].init();
        for (int i = 1; i <= n; ++i)
            vis[i] = 0;
        cnt = 1;
    }
    void insert(const string &s, int num)
    {
        int u = 1;
        for (int i = 0; i < s.size(); ++i)
        {
            int v = s[i] - 'a';
            if (!trie[u].son[v])
                trie[u].son[v] = ++cnt;
            u = trie[u].son[v];
        }
        if (!trie[u].flag)
            trie[u].flag = num;
        rev[num] = trie[u].flag;
        return;
    }
    void build()
    {
        for (int i = 0; i < 26; ++i)
            trie[0].son[i] = 1;
        q.push(1);
        trie[1].fail = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            int Fail = trie[u].fail;
            for (int i = 0; i < 26; ++i)
            {
                int v = trie[u].son[i];
                if (!v)
                {
                    trie[u].son[i] = trie[Fail].son[i];
                    continue;
                }
                trie[v].fail = trie[Fail].son[i];
                ++indeg[trie[Fail].son[i]];
                q.push(v);
            }
        }
    }
    void topo()
    {
        for (int i = 1; i <= cnt; ++i)
            if (!indeg[i])
                q.push(i);
        while (!q.empty())
        {
            int fr = q.front();
            q.pop();
            vis[trie[fr].flag] = trie[fr].ans;
            int u = trie[fr].fail;
            trie[u].ans += trie[fr].ans;
            if (!(--indeg[u]))
                q.push(u);
        }
    }
    void query(const string &s)
    {
        int u = 1;
        for (int i = 0; i < s.size(); ++i)
            u = trie[u].son[s[i] - 'a'], ++trie[u].ans;
    }
};

// example

AC_topo ac;

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;
    int n;
    string s;
    cin >> n;
    ac.init(n);
    for (int i = 1; i <= n; ++i)
        cin >> s, ac.insert(s, i);
    ac.build();
    cin >> s;
    ac.query(s);
    ac.topo();
    for (int i = 1; i <= n; ++i)
        cout << ac.vis[ac.rev[i]] << endl;
    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
```

