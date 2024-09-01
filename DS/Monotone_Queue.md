### Monotone_Queue

```cpp
int arr[MAXN], k;
deque<int> q;

void func()
{
    for (int i = 1; i <= MAXN; ++i)
    {
        if (!q.empty() && i - q.front() >= k)
            q.pop_front();
        while (!q.empty() && arr[q.back()] < arr[i])
            q.pop_back();
        q.push_back(i);
        if (i >= k)
            cout << q.front() << endl;
    }
}
```

