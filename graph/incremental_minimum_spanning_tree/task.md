## @{keyword.statement}

@{lang.en}

Given a weighted undirected graph with $N$ vertices and $0$ edges.
Insert $M$ edges $(u_i,v_i,w_i)$ in order and maintain the minimum spanning tree (MST) of the graph.

After each insertion, print the id of the edge that is removed from the MST.
If no edge is removed from the MST, print -1.

@{lang.ja}

TBD

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
