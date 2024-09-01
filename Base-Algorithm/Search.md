### Search

1. Meet in the middle(BFS version)

```cpp
// (a). one queue and 2 different marks
//
// (b). two queues and two maps(marks)
//      each time search the smaller size part for 1 level
//      (more optimized)
```

2. IDS(iterative deepening depth-first search)

```cpp
// for (int limit = 1; ; ++limit)
//      search
//      if found:
//          break;    
```

3. A* search algorithm

```cpp
//      each time search the smallest f(x) = g(x) + h(x)
//      with open set and closed set (?)
```

