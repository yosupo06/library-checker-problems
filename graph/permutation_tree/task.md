## @{keyword.statement}
@{lang.en}
Given a size $N$ permutation $P_0, P_1, \cdots, P_{N-1}$.
Output the common interval decomposition tree corresponding to this permutation. However, in this question, the words and phrases are defined as follows.

- connected interval is an interval $\[l, r\]$ where $\lbrace P_i\ |\ l \leq i \leq r\rbrace$ is also an interval.
- strong interval is a connected interval that does not contain or intersect one of the other connected intervals.
- common interval decomposition tree is a rooted tree shown by the Hasse diagram for semi-ordering by inclusion of the whole of a strong interval.
- linear node is when the child sequences are arranged in ascending order of the left end $l$ of the interval, the The vertex for which the union set of any continuous subsequence is a connected interval.
- prime node is a vertex that is not a linear node.


@{lang.ja}
長さ $N$ の順列 $P_0, P_1, \cdots, P_{N-1}$. が与えられる。この順列に対応するcommon interval decomposition tree を出力せよ。ただし、本問において下記の様に語句を定義する。

- connected interval は 区間 $\[l, r\]$ であって $\lbrace P_i\ |\ l \leq i \leq r\rbrace$ もまた区間となる物。
- strong interval は connected interval であって、他の connected interval に対してどちらかがもう一方を包含している、または交わらない物。
- common interval decomposition tree は connected interval 全体の包含による半順序についてのハッセ図 が示す根付き木。
- linear node は子の列を区間の左端 $l$ の昇順に並べた時、どの連続部分列の和集合も connected interval となる頂点。
- prime node は linear node でない頂点。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq P_i < N$
- $P_i \neq P_j (i \neq j)$

## @{keyword.input}

~~~
$N$
$P_0\ P_1\ P_2\ \cdots P_{N-1}$
~~~

## @{keyword.output}

~~~
$X$
$l_0\ r_0\ S_0$
$l_1\ r_1\ S_1$
$\vdots$
$l_{X-1}\ r_{X-1}\ S_{X-1}$
~~~

@{lang.en}
$X$ is the number of vertices in the common interval decomposition tree. $\[l_i,r_i\]$ is the interval corresponding to the $i$-th vertex, and $S_i$ is "linear" if the $i$-th vertex is a linear node or "prime" if it is a prime node. However, the order of the vertices is the preoder of the children in ascending order of the left end $l$.

@{lang.ja}
$X$ は common interval decomposition tree の頂点数。$\[l_i,r_i\]$ は $i$ 番目の頂点に対応する区間とし、$S_i$ は $i$ 番目の頂点が linear node なら "linear" 、prime node なら "prime"。ただし、頂点の順番は子を左端 $l$ の昇順に並べた際の preoder。

@{lang.end}

@{example.example_00}

@{example.example_01}

@{example.example_02}