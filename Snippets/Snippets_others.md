## Node.js

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

## Python

```Python

```

## Java

```Java

```