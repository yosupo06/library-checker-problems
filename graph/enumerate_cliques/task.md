## @{keyword.statement}

@{lang.en}
You are given a simple undirected graph $G$, consisting of $N$ vertices and $M$ edges.
The $i$-th edge of $G$ is $\lbrace u_i, v_i \rbrace$.
Each vertex of $G$ has an integer value, and the value of $i$ th vertex is $x_i$.

Find the sum of $\displaystyle \prod_{i \in C} x_i$ over all non-empty cliques $C$ of $G$, and print the sum modulo $@{param.MOD}$ .

@{lang.ja}
$N$ 頂点 $M$ 辺の単純無向グラフ $G$ が与えられます。
$i$ 番目の辺は $\lbrace u_i, v_i \rbrace$ です。
$G$ の各頂点 $i$ には整数 $x_i$ が割り当てられています。

$G$ の空でないクリーク $C$ すべてに対する $\displaystyle \prod_{i \in C} x_i$ の総和を $998244353$ で割った余りを求めてください。 

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$
- $@{param.M_MIN} \le M \le @{param.M_MAX}$
- $0 \le x_i \lt @{param.MOD}$
- $0 \le u_i \lt N$
- $0 \le v_i \lt N$
- $u_i \neq v_i$
- $\lbrace u_i, v_i \rbrace \neq \lbrace u_j, v_j \rbrace \  (i \neq j)$

## @{keyword.input}

```
$N$ $M$
$x_0$ $x_1$ $\ldots$ $x_{N-1}$
$u_0$ $v_0$
$u_1$ $v_1$
$\vdots$
$u_{M-1}$ $v_{M-1}$
```

## @{keyword.output}

```
$A$
```

## @{keyword.sample}

@{example.example_00}

@{lang.en}
$(0), (1), (2), (0, 1), (1, 2)$ are cliques of $G$.
Print $14$, which is the result of $1 + 2 + 3 + 1 \cdot 2 + 2 \cdot 3 \bmod @{param.MOD}$ .

@{lang.ja}
$(0), (1), (2), (0, 1), (1, 2)$ がグラフ $G$ のクリークです。

よって、$1 + 2 + 3 + 1 \cdot 2 + 2 \cdot 3$ を $998244353$ で割った余りである $14$ を出力します。

@{lang.end}

@{example.example_01}
