## @{keyword.statement}

@{lang.en}
You are given a simple undirected graph, consisting of $N$ vertices and $M$ edges.
The $i$-th edge is $\lbrace u_i, v_i \rbrace$.
Each vertex has an integer value, and the value of $i$ th vertex is $x_i$.

Three vertices $a, b, c (a \lt b \lt c)$ connected by three edges $\lbrace a, b \rbrace, \lbrace a, c \rbrace, \lbrace b, c \rbrace$ are called triangle.
Find the sum of $x_a x_b x_c$ over all triangles, and print the sum modulo $@{param.MOD}$ .

@{lang.ja}
$N$ 頂点 $M$ 辺の単純無向グラフが与えられます。
$i$ 番目の辺は $\lbrace u_i, v_i \rbrace$ です。
各頂点 $i$ には整数 $x_i$ が割り当てられています。

3 頂点 $a, b, c (a \lt b \lt c)$ であって辺 $\lbrace a, b \rbrace, \lbrace a, c \rbrace, \lbrace b, c \rbrace$ が全て存在するものを triangle と呼びます。
全ての triangle についての $x_a x_b x_c$ の和を $@{param.MOD}$ で割った余りを求めてください。

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
$0, 2, 3$ and $1, 2, 3$ are triangles.
Print $36$, which is the result of $1 \cdot 3 \cdot 4 + 2 \cdot 3 \cdot 4 \bmod @{param.MOD}$ .

@{lang.ja}
$0, 2, 3$ 及び $1, 2, 3$ が triangle です。
$1 \cdot 3 \cdot 4 + 2 \cdot 3 \cdot 4$ を $@{param.MOD}$ で割った余りである $36$ を出力します。

@{lang.end}
