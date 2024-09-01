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

template <typename T>
class Balanced_Binary_Tree
{
private:
    // N + M
    static const int N = 200005;
    struct Point
    {
        T value;
        int count;
        int size;
        int son[2], fa;
        Point() { size = count = 0, fa = son[1] = son[0] = 0; }
        Point(T value)
        {
            this->value = value,
            size = count = 1, fa = son[1] = son[0] = 0;
        }
    } tree[N];
    int length, size, root;
    bool get_id(int x)
    {
        return tree[tree[x].fa].son[1] == x;
    }
    void upto(int x)
    {
        tree[x].size =
            tree[tree[x].son[0]].size + tree[tree[x].son[1]].size + tree[x].count;
    }
    void connect(int x, int y, bool id)
    {
        tree[x].fa = y, tree[y].son[id] = x;
    }
    void rotate(int x)
    {
        int m(tree[x].fa), g(tree[m].fa);
        bool id(get_id(x)), mid(get_id(m));
        connect(tree[x].son[!id], m, id), upto(m),
            connect(m, x, !id), upto(x), connect(x, g, mid);
    }
    void splay(int x, int root)
    {
        root = tree[root].fa;
        while (tree[x].fa not_eq root)
            if (tree[tree[x].fa].fa == root)
                rotate(x);
            else if (get_id(x) == get_id(tree[x].fa))
                rotate(tree[x].fa), rotate(x);
            else
                rotate(x), rotate(x);
    }
    void Splay(int x)
    {
        splay(x, root), root = x;
    }

public:
    Balanced_Binary_Tree() { size = length = 0; }
    void insert(T x)
    {
        if (not size++)
        {
            tree[root = ++length] = Point(x), connect(root, 0, 0);
            return;
        }
        for (int i(root); ++tree[i].size, true;)
        {
            if (tree[i].value == x)
            {
                ++tree[i].count, Splay(i);
                return;
            }
            else
            {
                bool id(tree[i].value < x);
                if (not tree[i].son[id])
                {
                    tree[++length] = Point(x), connect(length, i, id),
                    Splay(length);
                    return;
                }
                else
                    i = tree[i].son[id];
            }
        }
    }
    void erase(T x)
    {
        --size;
        for (
            int i(root);
            tree[i].size--;
            i = tree[i].son[x > tree[i].value])
            if (tree[i].value == x)
            {
                if (--tree[i].count)
                {
                    Splay(i);
                    return;
                }
                Splay(i);
                if (not tree[i].son[0])
                {
                    connect(root = tree[i].son[1], 0, 0);
                    return;
                }
                if (not tree[i].son[1])
                {
                    connect(root = tree[i].son[0], 0, 0);
                    return;
                }
                int j(tree[i].son[0]);
                while (tree[j].son[1])
                    j = tree[j].son[1];
                splay(j, tree[i].son[0]);
                connect(tree[i].son[1], tree[i].son[0], 1),
                    upto(tree[i].son[0]),
                    connect(root = tree[i].son[0], 0, 0);
                return;
            }
    }
    int rank(T x)
    {
        int r(1);
        for (int i(root); i;)
            if (tree[i].value == x)
            {
                Splay(i);
                return tree[tree[i].son[0]].size + 1;
            }
            else if (tree[i].value < x)
                r += tree[tree[i].son[0]].size + tree[i].count,
                    i = tree[i].son[1];
            else
                i = tree[i].son[0];
        return r;
    }
    T kth(int x)
    {
        int r(1);
        for (int i(root); true;)
        {
            if (
                r + tree[tree[i].son[0]].size <= x and x < r + tree[tree[i].son[0]].size + tree[i].count)
            {
                Splay(i);
                return tree[i].value;
            }
            else if (x < r + tree[tree[i].son[0]].size)
                i = tree[i].son[0];
            else
                r += tree[tree[i].son[0]].size + tree[i].count,
                    i = tree[i].son[1];
        }
    }
    T lower(T x)
    {
        T r;
        int li;
        for (int i(root); i;)
            if (tree[i].value >= x)
                li = i, i = tree[i].son[0];
            else
                r = tree[li = i].value, i = tree[i].son[1];
        Splay(li);
        return r;
    }
    T upper(T x)
    {
        T r;
        int li;
        for (int i(root); i;)
            if (tree[i].value <= x)
                li = i, i = tree[i].son[1];
            else
                r = tree[li = i].value, i = tree[i].son[0];
        Splay(li);
        return r;
    }
};