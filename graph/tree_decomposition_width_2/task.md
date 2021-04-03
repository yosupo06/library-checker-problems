## @{keyword.statement}

$N$ 頂点 $M$ 辺の単純な無向グラフが与えられる。辺は $(u_i, v_i)$。

木幅が $2$ 以下か判定し、$2$ 以下の場合は木幅が $2$ 以下の木分解を構成してください。

つまり、以下の条件を満たす $K$ 頂点の木と、その各頂点にバッグ(=元のグラフの頂点の部分集合) $B_0, B_1, \cdots, B_{K - 1}$ を構築してください。

- $0 \leq K \leq 10N + M + 10$
- すべての辺 $(u_i, v_i)$ について、$u_i, v_i$ を両方含むバッグが存在する
- 元のグラフの各頂点 $i$ について、バッグに頂点 $i$ を含むような木の頂点のみを取り出すと、この頂点らは連結になっている

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq M \leq @{param.M_MAX}$
- グラフは単純

## @{keyword.input}

入出力は [PACE 2017 Track A](https://pacechallenge.wordpress.com/pace-2017/track-a-treewidth/) で使用されたフォーマットで与えられる。
サンプルも参考にせよ


```
p tw $N$ $M$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_M$ $v_M$
```

$u_i, v_i$ は **1-indexed** なことに注意せよ

## @{keyword.output}

木幅が $3$ 以上の場合は最初の行に $-1$ を出力してください。(これは PACE 2017 Track Aのフォーマットではないです)

そうでない場合以下の形式で出力してください。

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

- $K$ は木の頂点数
- $a_i$, $b_i$ は木の辺。**1-indexed** なことに注意せよ
- $w$ は $2$ 以下の整数。木分解のサイズを表す。$2$ を出力しておけば問題ないが、(たとえばより強いライブラリのテストのために) $0, 1$ を出力しても良い。
- $1 + i$ 行目はバッグの情報を表す。$v$ は **1-indexed** の元のグラフの頂点番号、各行ごとに $v$ の個数は $w + 1$ 個以下

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
