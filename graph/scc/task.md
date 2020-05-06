## @{keyword.statement}

@{lang.en}

Given a directed graph with $N$ vertices and $M$ edges. $i$-th edge is $(a_i, b_i)$. This graph may not be simple.

Please decompose this graph into SCCs and print them in topological order.

@{lang.ja}

$N$ 頂点 $M$ 辺の有向グラフが与えられる。$i$ 番目の辺は $(a_i, b_i)$ である。このグラフは単純とは限らない。
このグラフを強連結成分分解し、トポロジカルソートして出力してください。

@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq 500,000$
- $1 \leq M \leq 500,000$
- $0 \leq a_i, b_i < N$

## @{keyword.input}

~~~
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{M - 1}$ $b_{M - 1}$
~~~

## @{keyword.output}

@{lang.en}

First line, print the number of SCCs $K$.
Following $K$ line, we print the information of SCC for each line as follows.
$l$ is the number of vertices of SCC, and $v_i$ is the vertex index.

@{lang.ja}

$K$ を強連結成分の行数として、$1 + K$ 行出力する。
最初の行には $K$ を出力し、その後 $K$ 行では以下のように出力する。$l$ は強連結成分の頂点数であり、$v_i$ はその頂点番号である。

@{lang.end}

~~~
$l$ $v_0$ $v_1$ ... $v_{l-1}$
~~~

@{lang.en}

For each edge $(a_i, b_i)$, the line that contains $b_i$ can not be earlier than the line that contains $a_i$.

If there is a multiple solution, print any of them.

@{lang.ja}

ここで、各辺 $(a_i, b_i)$ について、$b_i$ が $a_i$ より __先の行__ に出現してはならない。

なお、正しい出力が複数存在する場合は、どれを出力しても構わない

@{lang.end}

## @{keyword.sample}

@{example.example_00}
