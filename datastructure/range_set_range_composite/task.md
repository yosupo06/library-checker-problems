## @{keyword.statement}

@{lang.en}
Given a size $N$ sequence of linear functions $f _ 0, f _ 1, ..., f _ {N-1}$. For all $i$, $f _ i(x) = a _ i x + b _ i$. Process $Q$ queries as follows:

- `0 $l$ $r$ $b$ $c$`: For each $i = l, l+1, \dots, {r - 1}$, $f _ i \gets cx + d$.
- `1 $l$ $r$ $x$`: Print $f _ {r-1}(f _ {r-2}(...f _ l(x))) \bmod @{param.MOD}$.
@{lang.ja}
長さ $N$ の(一次)関数列 $f _ 0, f _ 1, ..., f _ {N-1}$ が与えられる。$f _ i(x) = a _ i x + b _ i$ である。 $Q$ 個のクエリが飛んできます。処理してください。

- `0 $l$ $r$ $b$ $c$`: 各 $i = l, l+1, \dots, {r - 1}$ について、$f _ i \gets cx + d$ に変更
- `1 $l$ $r$ $x$`: $f _ {r-1}(f _ {r-2}(...f _ l(x))) \bmod @{param.MOD}$ を出力する。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $1 \leq a _ i, c < @{param.MOD}$
- $0 \leq b _ i, d, x < @{param.MOD}$
- $0 \leq l < r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$a _ 0$ $b _ 0$
$a _ 1$ $b _ 1$
:
$a _ {N - 1}$ $b _ {N - 1}$
$\textrm{Query} _ 0$
$\textrm{Query} _ 1$
:
$\textrm{Query} _ {Q - 1}$
~~~

@{example.example_00}
