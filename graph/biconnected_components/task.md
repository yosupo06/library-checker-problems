## @{keyword.statement}

@{lang.en}

Given a undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(a _ i, b _ i)$. This graph may not be simple but never has a self-loop.
Please decompose this graph into biconnected components.

@{lang.ja}

$N$ 頂点 $M$ 辺の無向グラフが与えられる。 $i$ 番目の辺は $(a _ i, b _ i)$ である。このグラフは単純とは限らないが、自己ループは含まれない。
このグラフを二重連結成分分解してください。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a _ i, b _ i \lt N$
- $a _ i \neq b _ i$

## @{keyword.input}

~~~
$N$ $M$
$a _ 0$ $b _ 0$
$a _ 1$ $b _ 1$
:
$a _ {M-1}$ $b _ {M-1}$
~~~

## @{keyword.output}

@{lang.en}

Print the number of biconnected components $K$ in the first line.
Following $K$ lines, print as follows. $l$ is the number of edges of biconnected components and $e _ i$ is an edge index.

@{lang.ja}

最初の行には $K$ を出力する。その後 $K$ 行では以下のように出力する。$l$ は二重連結成分の辺数であり、$e _ i$ はその辺番号である。

@{lang.end}

~~~
$l$ $e _ 0$ $e _ 1$ ... $e _ {l-1}$
~~~

@{lang.en}
If there is multiple solutions, print any of them.
@{lang.ja}
正しい出力が複数存在する場合は、どれを出力しても構わない。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
