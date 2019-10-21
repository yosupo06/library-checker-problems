# Output Checker 仕様

[testlib](https://github.com/MikeMirzayanov/testlib) を読み解いたメモ

## 実行方法

```
./checker <input> <contestant-output> <judge-output>
```

と起動する。引数が4個以上でも動くっぽいが未検証


## 返り値

- 0: AC
- 1: WA
- 2: PE
- 3: Fail

となっている。

その他4, 7, 8も何らかの意味がありそう？
