## @{keyword.statement}

@{lang.en}
Given a simple undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $\lbrace u_i, v_i\rbrace$。

Calculate the chromatic number $C$.

@{lang.ja}
$N$ 頂点 $M$ 辺の単純な無向グラフが与えられる。 $i$ 番目の辺は $\lbrace u_i, v_i\rbrace$ である。

彩色数 $C$ を出力してください。
@{lang.end}

## @{keyword.constraints}

- $@{param.MIN_N} \leq N \leq @{param.MAX_N}$
- $0 \leq M \leq \frac{N(N-1)}{2}$
- $0 \leq u_i, v_i < N$
- $u_i \neq v_i$
- $\lbrace u_i, v_i\rbrace \neq \lbrace u_j, v_j\rbrace$

## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{M - 1}$ $v_{M - 1}$
~~~

## @{keyword.output}

~~~
$C$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
