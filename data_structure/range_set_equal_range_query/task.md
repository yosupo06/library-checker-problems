## @{keyword.statement}

@{lang.en}
Given a size $N$ sequence of linear functions $f _ 0, f _ 1, ..., f _ {N-1}$. For all $i$, $f _ i(x) = a _ i x + b _ i$. Process $Q$ queries as follows:

- `0 $l$ $r$ $c$ $d$`: For each $i = l, l+1, \dots, {r - 1}$, $f _ i \gets cx + d$.
- `1 $l$ $r$ $x$`: Print $f _ {r-1}(f _ {r-2}(...f _ l(x))) \bmod @{param.MOD}$.
@{lang.ja}
長さ $N$ の整数列 A=$(a _ 0, a _ 1, ..., a _ {n-1})$ が与えられます．
$Q$ 個を処理してください. 

- `0 $l$ $r$ $x$`: 各 $i = l, l+1, \dots, {r - 1}$ について，$a _ i$ を $x$ に変更する．
- `2 $i$`: $a_i$ の値および，$l\leq i < r$ かつ $a _ l = \cdots = a _ {r-1}$ を満たすような極大な区間を答える．後者はより形式的には，次によって一意に定まる $(l,r)$ である. 
    - $l\leq i < r$ かつ $a _ l = \cdots = a _ {r-1}$
    - $l=0$ または $a_{l-1}\neq a_i$
    - $r=N$ または $a_{r}\neq a_i$
@{lang.end}

## @{keyword.constraints}

- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $1 \leq a _ i, c < @{param.MOD}$
- $0 \leq b _ i, d, x < @{param.MOD}$
- $0 \leq l < r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$a _ 0$ $a _ 1$ $\cdots$ $a _ {N-1}$
$\textrm{Query} _ 0$
$\textrm{Query} _ 1$
:
$\textrm{Query} _ {Q - 1}$
~~~

## @{keyword.output}

~~~
$a _ i$ $l$ $r$
$\vdots$
$a _ i$ $l$ $r$
~~~

@{example.example_00}
