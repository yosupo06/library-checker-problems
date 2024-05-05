## @{keyword.statement}

@{lang.en}
@{lang.end}
@{lang.ja}
英小文字とアスタリスク（`*`）からなる文字列 $S$, $T$ が与えられます。

文字列 $S'$ と $T'$ が各 $0\leq i<|S'|$ について
* S'_i = T'_i
* S'_i = `*`
* T'_i = `*`
のいずれかを満たす時，$S'$ と $T'$ はマッチすると呼ぶことにします。

各 $0\leq i<|S|-|T|$ について $S[i,i+|T|)$ と $T$ がマッチしているかを求めてください。
@{lang.end}

## @{keyword.constraints}

@{lang.ja}
- $1 \leq |T| \leq |S| < @{param.S_LEN_MAX}$
- $S,T$ は英小文字とアスタリスクからなる。
@{lang.end}

## @{keyword.input}

```
$S,T$
```

## @{keyword.output}
$W_i$ を $S[i,i+|T|)$ と $T$ がマッチしている時に $1$，そうでない時に $0$ として
```
$W_0, W_1, \dots, W_{|S|-|T|}$
```
## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}