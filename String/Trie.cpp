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

// 1. characters

class Trie
{
private:
    Trie* son[26];
    bool exist;
public:
    Trie()
    {
        exist = false;
        for (int i = 0; i < 26; i++)
            son[i] = nullptr;
    }
    ~Trie()
    {
        for (int i = 0; i < 26; i++)
            if (son[i] != nullptr)
                delete son[i];
    }
    void insert(string &word)
    {
        Trie* root = this;
        for (char x: word)
        {
            int cur = x - 'a';
            if (root->son[cur] == nullptr)
                root->son[cur] = new Trie();
            root = root->son[cur];
        }
        root->exist = true;
    }
    bool find(string &word)
    {
        Trie* root = this;
        for (char x : word)
        {
            int cur = x - 'a';
            if (root->son[cur] == nullptr)
                return false;
            root = root->son[cur];
        }
        return root->exist;
    }
};

// MAXN = N * len

#define MAXN 100005

struct Trie1
{
    int nex[MAXN][26], cnt;
    bool exist[MAXN];

    void insert(string &s)
    {
        int p = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            if (!nex[p][c])
                nex[p][c] = ++cnt;
            p = nex[p][c];
        }
        exist[p] = 1;
    }
    bool find(string &s)
    {
        int p = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            if (!nex[p][c])
                return 0;
            p = nex[p][c];
        }
        return exist[p];
    }
};

// 2. 01

struct Trie_01
{
    int nex[MAXN][2], cnt;
    bool exist[MAXN];

    void insert(int x)
    {
        int p = 0;
        for (int i = 30; i >= 0; --i)
        {
            int cur = (x >> i) & 1;
            if (!nex[p][cur])
                nex[p][cur] = ++cnt;
            p = nex[p][cur];
        }
        exist[p] = 1;
    }
    bool find(int x)
    {
        int p = 0;
        for (int i = 30; i >= 0; --i)
        {
            int cur = (x >> i) & 1;
            if (!nex[p][cur])
                return 0;
            p = nex[p][cur];
        }
        return exist[p];
    }
};