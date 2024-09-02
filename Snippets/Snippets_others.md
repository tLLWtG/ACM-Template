### Snippets_others

#### Node.js

```js
"use strict";

process.stdin.resume();
process.stdin.setEncoding("utf-8");

let strInput = "";
let curLine = 0;

process.stdin.on("data", (inputStdin) => {
  strInput += inputStdin;
});

process.stdin.on("end", () => {
  strInput = strInput
    .trim()
    .split("\n")
    .map((_) => {
      return _.trim();
    });
  main();
});

function readline() {
  return strInput[curLine++];
}

function main() {
  let t = parseInt(readline());
  while (t--) {

  }
}
```

#### Python

```Python
import sys
import bisect
import collections
import heapq
import math
from functools import cmp_to_key, lru_cache
from itertools import permutations, combinations
from random import getrandbits

input = lambda: sys.stdin.readline().strip()
# sys.setrecursionlimit(10**5)
T = 1
# T = int(input())


def solve():
    pass


for _ in range(T):
    solve()
```

#### Java

```Java
// TODO
```

