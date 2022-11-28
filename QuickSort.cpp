#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

/*-------------------------------------------*/

#define MAXN 100005
int arr[MAXN];

void myqsort(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, mid = arr[l + r >> 1];
    while (i < j)
    {
        do
            ++i;
        while (arr[i] < mid);
        do
            --j;
        while (arr[j] > mid);
        if (i < j)
            swap(arr[i], arr[j]);
    }
    myqsort(arr, l, j);
    myqsort(arr, j + 1, r);
}
