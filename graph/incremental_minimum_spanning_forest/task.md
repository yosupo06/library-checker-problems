## @{keyword.statement}

@{lang.en}

Given a weighted undirected graph with $N$ vertices and $0$ edges, insert $M$ edges $e_i = (u_i,v_i,w_i)$ in order and maintain the minimum spanning forest (MSF) of the graph. Note that the MSF is unique due to the constraints.

Let $F_{-1}$ be the forest with $0$ edges, and $F_i$ be the MSF after adding edge $e_i$. It can be proven that one of the following holds.

- $F_{i}=F_{i-1}+e_i$
- $F_{i}=(F_{i-1}+e_i)\setminus e_j$ for some $j$.

In the first case, output $-1$, and in the second case, output $j$.

@{lang.ja}

$N$ 頂点 $0$ 辺のグラフがあります．このグラフに $M$ 個の辺 $e_i = (u_i,v_i,w_i)$ を順に挿入しながら，その最小全域森 (MSF) を管理してください．なお制約により MSF は一意です．

Let $F_{-1}$ be the forest with $0$ edges, and $F_i$ be the MSF after adding edge $e_i$. It can be proven that one of the following holds.

$F_{-1}$ を $0$ 辺からなる森，$F_i$ を $e_i$ を追加した後の MSF とするとき，次のいずれかが成り立つことが証明できます. 

- $F_{i}=F_{i-1}+e_i$
- $F_{i}=(F_{i-1}+e_i)\setminus e_j$ for some $j$. 

前者の場合 $-1$ を，後者の場合 $j$ を出力してください．

@{lang.end}

## @{keyword.constraints}

@{lang.en} 

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.M_MAX}$
- $1 \leq w_i \leq @{param.W_MAX}$
- All $w_i$ are distinct

@{lang.ja}

- TBD

@{lang.end}

## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$ $w_0$
$u_1$ $v_1$ $w_1$
:
$u_{M - 1}$ $v_{M - 1}$ $w_{M - 1}$
~~~

## @{keyword.output}

~~~
$e_0$ $e_1$ $e_2$ ... $e_{M - 1}$
~~~

@{lang.en}

$e_i$ is the id of the edge that is removed from the MST after the $i$'th insertion.

@{lang.ja}

TBD

@{lang.end}

## @{keyword.sample}

@{example.example_00}
