### Monotone_Stack

```cpp
int arr[MAXN], ans[MAXN];
stack<int> st;

void func()
{
    for (int i = 1; i <= MAXN; ++i)
    {
        while (!st.empty() && arr[i] > arr[st.top()])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}
```

