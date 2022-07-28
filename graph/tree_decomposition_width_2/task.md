## @{keyword.statement}

@{lang.en}
You are given a simple, undirected graph with $N$ vertices and $M$ edges. Its edges are $(u_i, v_i)$.

Determine whether the tree width of the graph is no more than 2. If it is, construct a tree decomposition with tree width no more than 2.

In other words, construct a tree with $K$ vertices, and the bag (subset of vertices in the original graph) $B_0, B_1, \cdots, B_{K - 1}$ on each of its vertices.

- $0 \leq K \leq 10N + M + 10$
- For each edge $(u_i, v_i)$, there is a bag that contains both $u_i, v_i$.
- For each vertex $i$ in the original graph, all vertices in the tree whose bag contains vertex $i$ are connected.
@{lang.ja}
$N$ 頂点 $M$ 辺の単純な無向グラフが与えられる。辺は $(u_i, v_i)$。

木幅が $2$ 以下か判定し、$2$ 以下の場合は木幅が $2$ 以下の木分解を構成してください。

つまり、以下の条件を満たす $K$ 頂点の木と、その各頂点にバッグ(=元のグラフの頂点の部分集合) $B_0, B_1, \cdots, B_{K - 1}$ を構築してください。

- $0 \leq K \leq 10N + M + 10$
- すべての辺 $(u_i, v_i)$ について、$u_i, v_i$ を両方含むバッグが存在する
- 元のグラフの各頂点 $i$ について、バッグに頂点 $i$ を含むような木の頂点のみを取り出すと、この頂点らは連結になっている
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq M \leq @{param.M_MAX}$
- The graph is simple.
@{lang.ja}
- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq M \leq @{param.M_MAX}$
- グラフは単純
@{lang.end}

## @{keyword.input}

@{lang.en}
Input and output are in the format used in [PACE 2017 Track A](https://pacechallenge.wordpress.com/pace-2017/track-a-treewidth/).
Also refer to the samples.
@{lang.ja}
入出力は [PACE 2017 Track A](https://pacechallenge.wordpress.com/pace-2017/track-a-treewidth/) で使用されたフォーマットで与えられる。
サンプルも参考にせよ
@{lang.end}


```
p tw $N$ $M$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_M$ $v_M$
```

@{lang.en}
Note that $u_i, v_i$ are **1-indexed**.
@{lang.ja}
$u_i, v_i$ は **1-indexed** なことに注意せよ
@{lang.end}

## @{keyword.output}

@{lang.en}
If the tree width is $3$ or larger, output $-1$ in the first line. (This is not the format used in PACE 2017 Track A)

Otherwise, output in the following format.
@{lang.ja}
木幅が $3$ 以上の場合は最初の行に $-1$ を出力してください。(これは PACE 2017 Track Aのフォーマットではないです)

そうでない場合以下の形式で出力してください。
@{lang.end}

```
s td $K$ $w$ $N$
b $1$ $v$ $\ldots$ $v$
b $2$ $v$ $\ldots$ $v$
$\vdots$
b $K$ $v$ $\ldots$ $v$
$a_1$ $b_1$
$a_2$ $b_2$
$a_{K - 1}$ $b_{K - 1}$
```

@{lang.en}
- $K$ is the number of vertices in the tree.
- $a_i$, $b_i$ are edges in the tree. Note that they are **1-indexed**.
- $w$ is an integer no more than 2. It is the size of the tree decomposition. It is acceptable to always output $2$ for it, but it is also fine to output $0, 1$ when appropriate. (For example, for testing a stronger library)
- The $1 + i$-th line contains the information of a bag. $v$ is a **1-indexed** vertex ID in the original graph. Each line contains at most $w + 1$ vertices $v$.
@{lang.ja}
- $K$ は木の頂点数
- $a_i$, $b_i$ は木の辺。**1-indexed** なことに注意せよ
- $w$ は $2$ 以下の整数。木分解のサイズを表す。$2$ を出力しておけば問題ないが、(たとえばより強いライブラリのテストのために) $0, 1$ を出力しても良い。
- $1 + i$ 行目はバッグの情報を表す。$v$ は **1-indexed** の元のグラフの頂点番号、各行ごとに $v$ の個数は $w + 1$ 個以下
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
