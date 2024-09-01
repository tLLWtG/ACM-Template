### Binary_Search

1. `[left, right)` version

```cpp
int binary_search1(int l, int r, int key)
{
    ++r;
    int res = -1, mid;
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        if (arr[mid] < key)
            l = mid + 1;
        else if (arr[mid] > key)
            r = mid;
        else
        {
            res = mid;
            break; // r = mid or l = mid + 1
        }
    }
    return res;
}

int binary_ans1(int l, int r)
{
    ++r;
    int res = -1, mid;
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        if (check(arr[mid]))
        {
            res = mid;
            l = mid + 1;
        }
        else
            r = mid;
    }
    return res;
}
```

2. `[left, right]` version

```cpp
int binary_search2(int l, int r, int key)
{
    int res = -1, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (arr[mid] < key)
            l = mid + 1;
        else if (arr[mid] > key)
            r = mid - 1;
        else
        {
            res = mid;
            break; // r = mid - 1 or l = mid + 1
        }
    }
    return res;
}

int binary_ans2(int l, int r)
{
    int res = -1, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (check(arr[mid]))
        {
            res = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return res;
}
```

