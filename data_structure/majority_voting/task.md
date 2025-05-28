## @{keyword.statement}

@{lang.en}
TODO
@{lang.ja}
長さ $N$ の整数列 $A_0, A_1, \dots, A_{N - 1}$ が与えられます。
$i=0,1,\ldots ,Q-1$ についてクエリを処理してください。

- `0 $p$ $x$`: $A _ {p} \gets x$
- `1 $l$ $r$`: $A _ {l} \ldots A _ {r-1}$ に過半数を占める要素があればそれを、なければ $-1$ を出力
@{lang.end}

## @{keyword.constraints}

@{lang.en}
TODO
@{lang.ja}
$t _ i$ を、 $i$ 番目のクエリの種類とします ($0\leq i \lt Q$ , $t _ i\in\lbrace 0,1\rbrace$)。

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq p < N$
- $0 \leq x \leq @{param.A_MAX}$
- $0 \leq l < r \leq N$
@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$A _ 0$ $A _ 1$ ... $A _ {N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}

@{example.example_01}
