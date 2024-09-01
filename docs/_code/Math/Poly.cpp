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

// 求原根

namespace Root
{
    ll pow(const ll x, const ll n, const ll p)
    {
        ll ans = 1;
        for (ll num = x, tmp = n; tmp; tmp >>= 1, num = num * num % p)
            if (tmp & 1)
                ans = ans * num % p;
        return ans;
    }
    ll root(const ll p)
    {
        for (int i = 2; i <= p; i++)
        {
            int x = p - 1;
            bool flag = false;
            for (int k = 2; k * k <= p - 1; k++)
                if (x % k == 0)
                {
                    if (pow(i, (p - 1) / k, p) == 1)
                    {
                        flag = true;
                        break;
                    }
                    while (x % k == 0)
                        x /= k;
                }
            if (!flag && (x == 1 || pow(i, (p - 1) / x, p) != 1))
            {
                return i;
            }
        }
        throw;
    }
}

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> poly;

const int FFTN = 1 << 22, mod = 998244353; // FFTN最大值(1 << 23), mod-1 = 119 * (1 << 23)

int qpow(int a, int t, int p = mod)
{
    int s = 1;
    for (; t; t >>= 1, a = (ll)a * a % p)
        if (t & 1)
            s = (ll)s * a % p;
    return s;
}

// FNTT

namespace FFT
{
    int w[FFTN + 5], W[FFTN + 5], R[FFTN + 5];

    // 初始化单位根的幂
    void FFTinit()
    {
        W[0] = 1;
        W[1] = qpow(3, (mod - 1) / FFTN); // 3为原根, 若更换模数需要注意
        for (int i = 2; i <= FFTN; ++i)
            W[i] = (ll)W[i - 1] * W[1] % mod;
    }
    int FFTinit(int n)
    {
        int L = 1;
        for (; L <= n; L <<= 1)
            ;
        for (int i = 0; i <= L - 1; ++i)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (L >> 1) : 0);
        return L;
    }

    ull p[FFTN + 5];
    int A[FFTN + 5], B[FFTN + 5];

    // DFT和IDFT过程
    void DFT(int *a, int n)
    {
        for (int i = 0; i < n; ++i)
            p[R[i]] = a[i];
        for (int d = 1; d < n; d <<= 1)
        {
            int len = FFTN / (d << 1);
            for (int i = 0, j = 0; i < d; ++i, j += len)
                w[i] = W[j];
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; ++j)
                {
                    int y = p[i + j + d] * w[j] % mod;
                    p[i + j + d] = p[i + j] + mod - y;
                    p[i + j] += y;
                }
            if (d == (1 << 15))
                for (int i = 0; i < n; ++i)
                    p[i] %= mod;
        }
        for (int i = 0; i < n; ++i)
            a[i] = p[i] % mod;
    }
    void IDFT(int *a, int n)
    {
        for (int i = 0; i < n; ++i)
            p[R[i]] = a[i];
        for (int d = 1; d < n; d <<= 1)
        {
            int len = FFTN / (d << 1);
            for (int i = 0, j = FFTN; i < d; ++i, j -= len)
                w[i] = W[j];
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; ++j)
                {
                    int y = p[i + j + d] * w[j] % mod;
                    p[i + j + d] = p[i + j] + mod - y;
                    p[i + j] += y;
                }
            if (d == (1 << 15))
                for (int i = 0; i < n; ++i)
                    p[i] %= mod;
        }
        int val = qpow(n, mod - 2);
        for (int i = 0; i < n; ++i)
            a[i] = p[i] * val % mod;
    }

    // 多项式加法, Plus(poly a , poly b)返回a+b
    poly Plus(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(std::max(sza, szb) + 1);
        for (int i = 0; i <= sza; ++i)
            ans[i] = a[i];
        for (int i = 0; i <= szb; ++i)
            ans[i] = (ans[i] + b[i]) % mod;
        return ans;
    }

    // 多项式减法, Minus(poly a , poly b)返回a-b
    poly Minus(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(std::max(sza, szb) + 1);
        for (int i = 0; i <= sza; ++i)
            ans[i] = a[i];
        for (int i = 0; i <= szb; ++i)
            ans[i] = (ans[i] + mod - b[i]) % mod;
        return ans;
    }

    // 多项式乘法, Mul(poly a , poly b)返回a*b
    poly Mul(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(sza + szb + 1);
        if (sza <= 30 || szb <= 30)
        {
            for (int i = 0; i <= sza; ++i)
                for (int j = 0; j <= szb; ++j)
                    ans[i + j] = (ans[i + j] + (ll)a[i] * b[j]) % mod;
            return ans;
        }
        int L = FFTinit(sza + szb);
        for (int i = 0; i < L; ++i)
            A[i] = (i <= sza ? a[i] : 0);
        for (int i = 0; i < L; ++i)
            B[i] = (i <= szb ? b[i] : 0);
        DFT(A, L), DFT(B, L);
        for (int i = 0; i < L; ++i)
            A[i] = (ll)A[i] * B[i] % mod;
        IDFT(A, L);
        for (int i = 0; i <= sza + szb; ++i)
            ans[i] = A[i];

        return ans;
    }

    // 多项式快速幂, PolyPow(poly a , b)返回a^b
    // 注意次数为(a.size()-1)*b
    poly PolyPow(const poly &a, int b)
    {
        int sza = a.size() - 1;
        poly ans(sza * b + 1);
        int L = FFTinit(sza * b + 1);
        for (int i = 0; i < L; ++i)
            A[i] = (i <= sza ? a[i] : 0);
        DFT(A, L);
        for (int i = 0; i < L; ++i)
            A[i] = qpow(A[i], b);
        IDFT(A, L);
        for (int i = 0; i <= sza * b; ++i)
            ans[i] = A[i];

        return ans;
    }

    // % x^k
    // b 可先对 mod 取模
    // 当 a0 = 1 时， 也可转为求 e^{k*ln(a)}
    poly PolyPow(const poly &a, int b, int k)
    {
        poly res(1, 1);
        poly aa(a);
        while (b)
        {
            aa.resize(k);
            if (b & 1)
            {
                res = Mul(res, aa);
                res.resize(k);
            }
            aa = Mul(aa, aa);
            b >>= 1;
        }
        return res;
    }

    // 多项式求逆, getinv(poly a , n)返回a^(-1) mod x^n
    void Getinv(int *a, int *b, int n)
    {
        if (n == 1)
        {
            b[0] = qpow(a[0], mod - 2);
            return;
        }
        int nn = (n + 1) >> 1;
        Getinv(a, b, nn);
        int L = FFTinit(n << 1);
        for (int i = 0; i < L; ++i)
            A[i] = (i < n ? a[i] : 0);
        for (int i = 0; i < L; ++i)
            B[i] = (i < nn ? b[i] : 0);
        DFT(A, L);
        DFT(B, L);
        for (int i = 0; i < L; ++i)
            A[i] = (ll)B[i] * (2 + mod - (ll)A[i] * B[i] % mod) % mod;
        IDFT(A, L);
        for (int i = 0; i < n; ++i)
            b[i] = A[i];
    }
    poly getinv(const poly &a, int n)
    {
        int *b = new int[n], *c = new int[n], sz = a.size();
        for (int i = 0; i < n; ++i)
            b[i] = (i < sz ? a[i] : 0);
        for (int i = 0; i < n; ++i)
            c[i] = 0;

        poly ans(n);
        Getinv(b, c, n);
        for (int i = 0; i < n; ++i)
            ans[i] = c[i];
        delete[] b;
        delete[] c;
        return ans;
    }

    // 结果 %x^len
    poly derivation(const poly &a, int len)
    {
        poly ans(len, 0);
        for (int i = 0; i < len && i + 1 < a.size(); ++i)
            ans[i] = (ll)a[i + 1] * (i + 1) % mod;
        return ans;
    }

    // 注意常数项这里默认为 0
    // 结果 %x^len
    poly integral(const poly &a, int len)
    {
        poly ans(len, 0);
        for (int i = 1; i < len && i - 1 < a.size(); ++i)
            ans[i] = (ll)a[i - 1] * qpow(i, mod - 2) % mod;
        return ans;
    }

    // 模意义下当且仅当 a0 = 1 时，a 有对数多项式
    // 结果 %x^len
    poly getln(const poly &a, int len)
    {
        poly dB = Mul(derivation(a, len), getinv(a, len));
        dB.resize(len);
        return integral(dB, len);
    }

    // a0 = 0 时有意义
    // exp 结果 %x^len
    void Exp(const poly &a, poly &res, int len)
    {
        if (len == 1)
        {
            res[0] = 1;
            return;
        }
        Exp(a, res, len + 1 >> 1);
        poly F = getln(res, len);
        F[0] = (a[0] + 1 - F[0] + mod) % mod;
        for (int i = 1; i < len; ++i)
            F[i] = (a[i] - F[i] + mod) % mod;
        poly t(res.begin(), res.begin() + len);
        t = Mul(t, F);
        for (int i = 0; i < len; ++i)
            res[i] = t[i];
    }
    poly exp(const poly &a, int len)
    {
        poly res(len, 0);
        Exp(a, res, len);
        return res;
    }
}

// example

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;

    FFT::FFTinit(); // 必需
    int n, m, k;
    cin >> n >> m >> k;
    poly f(k + 1);
    ll C = 1;
    for (int i = 0; i <= k; ++i)
    {
        // debug(C);
        if (i % 2 == 0)
            f[i] = C;
        C = C * (n - i) % mod;
        C = C * qpow(i + 1, mod - 2) % mod;
    }
    poly g(1, 1);
    int ans = qpow(2, m);
    while (m)
    {
        f.resize(k + 1);
        if (m & 1)
        {
            g = FFT::Mul(g, f);
            g.resize(k + 1);
        }
        f = FFT::Mul(f, f);
        m >>= 1;
    }
    ans = 1ll * g[k] * ans % mod;
    cout << ans << endl;

    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
