### Sort

1. Quicksort

> Quicksort can find the k-th element

```cpp
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
```

1. Merge sort

> Merge sort can count Inversions

```cpp
int arr[MAXN], brr[MAXN];

void msort(int b, int e)
{
    if (b == e)
        return;
    int mid = (b + e) / 2, i = b, j = mid + 1, k = b;
    msort(b, mid), msort(mid + 1, e);
    while (i <= mid && j <= e)
    {
        if (arr[i] <= arr[j])
            brr[k++] = arr[i++];
        else
            brr[k++] = arr[j++];
    }
    while (i <= mid)
        brr[k++] = arr[i++];
    while (j <= e)
        brr[k++] = arr[j++];
    for (int l = b; l <= e; ++l)
        arr[l] = brr[l];
}
```

