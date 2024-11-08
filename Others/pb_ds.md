### pb_ds

1. tree

> 平衡树，需包含头文件 <ext/pb_ds/assoc_container.hpp> 和 <ext/pb_ds/tree_policy.hpp>
>
> order_of_key 返回小于参数的元素个数，find_by_order 下标从 0 开始。 

```cpp
__gnu_pbds::tree<pii, __gnu_pbds::null_type, less<pii>,
__gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> trr;
// Mapped: 映射规则（Mapped-Policy）类型，如果要指示关联容器是集合，类似于存储元素在 std::set 中
// ，此处填入 null_type，低版本 g++ 此处为 null_mapped_type；如果要指示关联容器是 带值的集合，
// 类似于存储元素在 std::map 中，此处填入类似于 std::map<Key, Value> 的 Value 类型
map<int, int> book;
int n, opt, x;
cin >> n;
while (n--)
{
    cin >> opt >> x;
    if (opt == 1) trr.insert({x, ++book[x]});
    else if (opt == 2) trr.erase({x, book[x]--});
    else if (opt == 3) cout << trr.order_of_key({x, 0}) + 1 << endl;
    else if (opt == 4) cout << trr.find_by_order(x - 1)->fi << endl;
    else if (opt == 5) cout << trr.find_by_order(trr.order_of_key({x, 0}) - 1)->fi << endl;
    else if (opt == 6)
    {
        auto it = trr.upper_bound({x, book[x]});
        cout << it->fi << endl;
    }
}
```

2. priority_queue

> 堆，需包含头文件 <ext/pb_ds/priority_queue.hpp>
>
> 一般只用 pairing_heap_tag，其 join 是 O(1) 的

```cpp
__gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag> pq;
```

