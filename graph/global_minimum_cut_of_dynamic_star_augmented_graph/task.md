## @{keyword.statement}

@{lang.en}
You are given a simple weighted undirected graph $G$, consisting of $N$ vertices and $M$ edges.
The $i$-th edge is $\lbrace u_i, v_i \rbrace$ and has a weight of $w_i$.

Let $H$ be a graph obtained by adding a new vertex $N$ to $G$ together with new $N$ edges.
The $i$-th edge is $\lbrace i, N \rbrace$ and has a weight of $a_i$.

Process the following $Q$ queries in order:

- change a weight of an edge $\lbrace x_i,N \rbrace$ to $y_i$ and print a global minmum cut size in $H$.

@{lang.ja}
$N$ 頂点 $M$ 辺の単純重み付き無向グラフ $G$ が与えられる．$i$ 番目の辺は頂点 $u_i$,$v_i$ 間に張られており，重みは $w_i$ である．

$G$ に新たな頂点 $N$ を追加して，頂点 $i$,$N$ 間に重み $a_i$ の辺を張ることによって得られるグラフを $H$ とする．

以下の $Q$ 個のクエリを処理せよ．

- $H$ 上の頂点 $x_i$,$N$ 間に張られている辺の重みを $y_i$ に変更して，$H$ の全域最小カットの重みを出力する．

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$
- $@{param.M_MIN} \le M \le \min ( \frac{N(N-1)}{2} , @{param.M_MAX} )$
- $@{param.Q_MIN} \le Q \le @{param.Q_MAX}$
- $0 \le a_i \le @{param.W_MAX}$
- $0 \le u_i, v_i \lt N$
- $u_i \neq v_i$
- $\lbrace u_i, v_i \rbrace \neq \lbrace u_j, v_j \rbrace \  (i \neq j)$
- $1 \le w_i \le @{param.W_MAX}$
- $0 \le x_i \lt N$
- $0 \le y_i \le @{param.W_MAX}$

## @{keyword.input}

~~~
$N$ $M$ $Q$
$a_0$ $a_1$ $\ldots$ $a_{N-1}$
$u_0$ $v_0$ $w_0$
$u_1$ $v_1$ $w_1$
$\vdots$
$u_{M-1}$ $v_{M-1}$ $w_{M-1}$
$x_0$ $y_0$
$x_1$ $y_1$
$\vdots$
$x_{Q-1}$ $y_{Q-1}$
~~~

## @{keyword.sample}

@{example.example_00}
@{example.example_01}
