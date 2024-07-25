## @{keyword.statement}

@{lang.en}
This problem has $T$ cases. 

You are given an undirected graph $G$, consisting of $N$ vertices and $M$ edges. The $i$-th edge connects vertices $u _ i$ and $v _ i$. This graph may not be simple but does not contain any self-loops.

You are also given two vertices $s$ and $t$ of $G$. 

Determine if there exists a permutation $p = (p _ 0,\ldots,p _ {N - 1})$ of the vertices satisfying the following condition, and if so, find such a permutation.

- Orient each edge of $G$ from $u _ i$ to $v _ i$ if $p _ {u _ i} < p _ {v _ i}$, or from $v _ i$ to $u _ i$ if $p _ {v _ i} < p _ {u _ i}$. Then, for any vertex $v$, there exists a path from $s$ to $t$ that passes through $v$.

@{lang.ja}
この問題は $T$ ケースあります．

$N$ 頂点 $M$ 辺の無向グラフ $G$ が与えられます．$i$ 番目の辺は頂点 $u _ i$ と頂点 $v _ i$ を結んでいます．このグラフは単純とは限りませんが，自己ループは含みません．

また，$G$ の $2$ 頂点 $s, t$ が与えられます．

$G$ の頂点の順列 $p = (p _ 0, \ldots, p _ {N - 1})$ であって，次の条件を満たすものが存在するかを判定し，存在する場合には求めてください．

- $G$ の各辺を $p _ {u _ i} \lt p _ {v _ i}$ ならば $u _ i$ から $v _ i$ へ，$p _ {v _ i} \lt p_{u _ i}$ ならば $v _ i$ から $u _ i$ へ向き付けることを考える．このとき任意の頂点 $v$ に対して，$s$ から $t$ へのパスであって $v$ を通るものが存在する．
@{lang.end}


## @{keyword.constraints}
@{lang.en}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq s, t \lt N$
- $s\neq t$
- $0 \leq u _ i, v _ i \lt N$
- $u _ i\neq v _ i$
- The sum of $N$ over all test cases does not exceed $@{param.N_MAX}$. 
- The sum of $M$ over all test cases does not exceed $@{param.M_MAX}$. 

@{lang.ja}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq s, t \lt N$
- $s\neq t$
- $0 \leq u _ i, v _ i \lt N$
- $u _ i\neq v _ i$
- 全てのテストケースに対する $N$ の総和は $@{param.N_MAX}$ を超えない．
- 全てのテストケースに対する $M$ の総和は $@{param.M_MAX}$ を超えない．

@{lang.end}

## @{keyword.input}

~~~
$T$
$N$ $M$ $s$ $t$
$u _ 0$ $v _ 0$
$\vdots$
$u _ {M - 1}$ $v _ {M - 1}$
$N$ $M$ $s$ $t$
$u _ 0$ $v _ 0$
$\vdots$
$u _ {M - 1}$ $v _ {M - 1}$
$\vdots$
~~~

## @{keyword.output}

@{lang.en}

If there exists no permutation $p$ satisfying the condition, print `No`. Otherwise, print a permutation $p$ in the following format. 

@{lang.ja}

条件を満たす順列 $p$ が存在しない場合には `No` を出力してください．存在する場合には $p$ を次の形式で出力してください．

@{lang.end}

~~~
Yes
$p _ 0$ $\ldots$ $p _ {N - 1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
