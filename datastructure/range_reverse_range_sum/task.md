## @{keyword.statement}

@{lang.en}
You are given a sequence $a _ 0, a _ 1, ..., a _ {N - 1}$, consisting of $N$ integers.

Process $Q$ queries of the following types in order :

 - `0 $l$ $r$` : Reverse $a _ l, a _ {l + 1}, \dots, a _ {r - 1}$.
 - `1 $l$ $r$` : Print $\sum _ {i = l} ^ {r - 1} a _ i$.

@{lang.ja}
長さ $N$ の数列 $a _ 0, a _ 1, ..., a _ {N-1}$ が与えられます。
以下で説明されるクエリを順に $Q$ 回処理してください。

 - `0 $l$ $r$` : $a _ l, a _ {l + 1}, \dots, a _ {r - 1}$ を反転する。
 - `1 $l$ $r$` : $\sum _ {i = l} ^ {r - 1} a _ i$ を出力する。

@{lang.end}


## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a _ i \leq @{param.A_MAX}$
- $0 \leq l _ j \leq r _ j \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$a _ 0$ $a _ 1$ $\cdots$ $a _ {N - 1}$
$t _ 0$ $l _ 0$ $r _ 0$
$t _ 1$ $l _ 1$ $r _ 1$
$\vdots$
$t _ {Q - 1}$ $l _ {Q - 1}$ $r _ {Q - 1}$
~~~

## @{keyword.sample}

@{example.example_00}
