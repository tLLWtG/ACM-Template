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

#include <sys/time.h>
// millisecond
// you should include <sys/time.h> before use it

int getSeed()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// better randint

int randint(int l, int r = 0)
{
    // static mt19937 eng(time(0));
    static mt19937 eng(getSeed());
    if (l > r)
        swap(l, r);
    uniform_int_distribution<int> dis(l, r);
    return dis(eng);
}

// Example

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;

    int N = randint(1, 10);
    cout << N << endl;
    for (int i = 1; i <= N; ++i)
    {
        int x = randint(1, 10);
        cout << x << ' ';
    }
    cout << endl;
    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
