## @{keyword.statement}

@{lang.en}
You are given a graph, consisting of $N$ vertices and $M$ edges.

The $i$-th edge is directed from vertex $u_i$ to vertex $v_i$.

Find the cycle in given graph, or report that no such cycle exists.

If there are multiple cycles, print any of them.
@{lang.ja}
$N$ 頂点 $M$ 辺の有向グラフが与えられます。$i$ 番目の辺は頂点 $u_i$ から頂点 $v_i$ に向けて張られています。

与えられたグラフにサイクルが含まれるならば、1 つ見つけてください。存在しないならばその旨を報告してください。サイクルが複数含まれるならばどれを出力しても構いません。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq u_i \lt N$
- $0 \leq v_i \lt N$
- $u_i \neq v_i$


## @{keyword.input}

```
$N$ $M$
$u_0$ $v_0$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_{M-1}$ $v_{M-1}$
```

## @{keyword.output}

@{lang.en}
If there are no cycles, output ```-1```.

Otherwise, output one of the cycles in the following format. $e_i$ denotes the ID of $i$-th edge to use. Note that $(e_0, e_1, \ldots, e_{L-1})$ must be a cycle, and $e_i$ must not be equal to $e_j$ if $i \neq j$.

@{lang.ja}
サイクルが存在しない場合、```-1``` を出力してください。

そうでない場合、以下の形式で出力してください。ここで、$e_i$ は $i$ 番目に通る辺の番号を表し、$(e_0, e_1, \ldots, e_{L-1})$ は、この順に辺を通るときにサイクルを成さなければならず、$e_i \neq e_j$ $(i \neq j)$ でなければなりません。
@{lang.end}
```
$L$
$e_0$
$e_1$
$\vdots$
$e_{L-1}$
```

## @{keyword.sample}

@{example.example_00}

@{lang.en}
For instance, $L = 2, e = (1, 4)$ is also a valid answer.

@{lang.ja}
例えば $L = 2, e = (1, 4)$ も正答になります。
@{lang.end}

@{example.example_01}

