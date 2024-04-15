## @{keyword.statement}

@{lang.en}

Given an integer $M$, an $N$-variable polynomial $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} a _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ and a sequence $(w _ 0, \ldots, w _ {2 ^ N - 1})$ of elements of $\mathbb{F} _ {@{param.MOD}}$. Here, $i_k$ represents the number in the $2 ^ k$'s place when $i$ is expressed in binary.

For $m=0,1,\ldots,M-1$, compute $\sum _ {i=0} ^ {2 ^ N - 1} w_ib_i$, where $b_i$ is defined by $s(x _ 0, x _ 1, \dots, x _ {N - 1})^m = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$. 

@{lang.ja}

整数 $M$ および，$N$ 変数多項式 $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} a _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ および $\mathbb{F} _ {@{param.MOD}}$ の元の列 $(w _ 0, \ldots, w _ {2 ^ N - 1})$ が与えられます. ただし, $i _ k$ は $i$ を $2$ 進法で表した時の $2 ^ k$ の位の値を表します. 

各 $m=0,1,\ldots,M-1$ に対して $s(x _ 0, x _ 1, \dots, x _ {N - 1})^m = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$ により $b _ i$ を定めたときの $\sum _ {i=0} ^ {2 ^ N - 1} w _ ib _ i$ を求めてください.

@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, w_i \lt @{param.MOD}$

## @{keyword.input}

```
$N$ $M$
$a _ 0$ $a _ 1$ $\cdots$ $a _ {2^N-1}$
$w _ 0$ $w _ 1$ $\cdots$ $w _ {2^N-1}$
```

## @{keyword.output}

```
$\mathrm{ans}_0$ $\mathrm{ans}_1$ $\cdots$ $\mathrm{ans}_{M-1}$
```

## @{keyword.sample}

@{example.example_00}
