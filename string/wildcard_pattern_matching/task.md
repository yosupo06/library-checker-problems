## @{keyword.statement}

@{lang.en}
Given strings $S$ and $T$ consisting of lowercase English letters and asterisks (`*`).

We say that strings $S'$ and $T'$ are matched if they satisfy one of:

* $S'_i$ = $T'_i$
* $S'_i$ = `*`
* $T'_i$ = `*`

for each $0\leq i<|S'|$.

For each $0\leq i\leq|S|-|T|$, find if $S[i,i+|T|)$ and $T$ are matched.
@{lang.end}
@{lang.ja}
英小文字とアスタリスク（`*`）からなる文字列 $S$, $T$ が与えられます。

文字列 $S'$ と $T'$ が各 $0\leq i<|S'|$ について

* $S'_i$ =$T'_i$
* $S'_i$ = `*`
* $T'_i$ = `*`

のいずれかを満たす時，$S'$ と $T'$ はマッチすると呼ぶことにします。

各 $0\leq i\leq|S|-|T|$ について $S[i,i+|T|)$ と $T$ がマッチしているかを求めてください。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq |T| \leq |S| \leq @{param.S_LEN_MAX}$
- Each character of $S$ and $T$ is lowercase English letters or asterisks.
@{lang.end}
@{lang.ja}
- $1 \leq |T| \leq |S| \leq @{param.S_LEN_MAX}$
- $S,T$ は英小文字とアスタリスクからなる。
@{lang.end}

## @{keyword.input}

```
$S,T$
```

## @{keyword.output}
@{lang.en}
```
$W_0, W_1, \dots, W_{|S|-|T|}$
```
Here, $W_i$ is $1$ if $S[i,i+|T|)$ and $T$ are matched, $0$ otherwise.
@{lang.end}
@{lang.ja}
```
$W_0, W_1, \dots, W_{|S|-|T|}$
```
ただし，$W_i$ は $S[i,i+|T|)$ と $T$ がマッチしている時に $1$，そうでない時に $0$ とする．
@{lang.end}
## @{keyword.sample}

@{example.example_00}