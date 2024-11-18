## @{keyword.statement}

@{lang.en}
You are given a set of non-negative integers $S = \lbrace a_0, \ldots, a_{N-1} \rbrace$.
Please process the following $Q$ queries:

- 0 $x$: If $x \notin S$, insert $x$ into $S$. If $x \in S$, do nothing.
- 1 $x$: If $x \in S$, remove $x$ from $S$. If $x \notin S$, do nothing.
- 2 $x$: Output the $x$-th smallest element of $S$ in ascending order. If $|S| < x$, output $-1$.
- 3 $x$: Output the number of elements in $S$ that are less than or equal to $x$.
- 4 $x$: Output the largest element in $S$ that is less than or equal to $x$ (or $-1$ if no such element exists).
- 5 $x$: Output the smallest element in $S$ that is greater than or equal to $x$ (or $-1$ if no such element exists).


@{lang.ja}
非負整数からなる集合 $S = \lbrace a_0,\ldots,a_{N-1}\rbrace$ が与えられます．
以下のクエリを $Q$ 回処理してください．

- 0 $x$ : $x\notin S$ ならば $x$ を $S$ に挿入する．$x\in S$ ならば何もしない．
- 1 $x$ : $x\in S$ ならば $x$ を $S$ から取り除く．$x\notin S$ ならば何もしない．
- 2 $x$ : $S$ の要素のうち昇順 $x$ 番目のものを出力する．$|S|<x$ ならば $-1$ を出力する．
- 3 $x$ : $S$ の $x$ 以下の要素の個数を出力する．
- 4 $x$ : $S$ の $x$ 以下の要素のうち最大のもの（存在しないならば $-1$）を出力する．
- 5 $x$ : $S$ の $x$ 以上の要素のうち最小のもの（存在しないならば $-1$）を出力する．
@{lang.end}

## @{keyword.constraints}
@{lang.en}
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq a _ 0 < \cdots < a _ {N-1} \leq @{param.A_MAX}$
- $0\leq x \leq @{param.A_MAX}$
- $1\leq x$ if $t = 2$
@{lang.ja}
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq a _ 0 < \cdots < a _ {N-1} \leq @{param.A_MAX}$
- $0\leq x \leq @{param.A_MAX}$
- $t=2$ ならば $1\leq x$
@{lang.end}

## @{keyword.input}

```
$N$ $Q$
$a_0$ $\cdots$ $a_{N-1}$
$t$ $x$
$\vdots$
$t$ $x$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
