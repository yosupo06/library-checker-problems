## @{keyword.statement}

@{lang.en}
Given a size $N$ sequence of linear functions $f_0, f_1, ..., f_{N-1}$. Initially, $f_i(x)=x$ For all $i$. Process $Q$ queries as follows:

- `0 $p$ $c$ $d$`: change $f_p \gets cx + d$.
- `1 $l$ $r$ $x$`: print $f_{r-1}(f_{r-2}(...f_l(x))) \bmod @{param.MOD}$.

@{lang.ja}
長さ $N$ の(一次)関数列 $f_0, f_1, ..., f_{N-1}$ が与えられる。
はじめすべての $i$ について $f_i(x)=x$ である。$Q$ 個のクエリが飛んできます。処理してください。

- `0 $p$ $c$ $d$`: $f_p \gets cx + d$ に変更
- `1 $l$ $r$ $x$`: $f_{r-1}(f_{r-2}(...f_l(x))) \bmod @{param.MOD}$ を出力する。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $1 \leq a_i, c < @{param.MOD}$
- $0 \leq b_i, d, x < @{param.MOD}$
- $0 \leq p < N$
- $0 \leq l < r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
