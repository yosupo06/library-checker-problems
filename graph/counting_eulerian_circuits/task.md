## @{keyword.statement}

@{lang.en}
You are given a **directed** graph $G$, consisting of $N$ vertices and $M$ edges. The $i$-th edge is directed from $u_i$ to $v_i$. 

An **eulerian circuit** of $G$ is a pair of sequence of vertices $(v_0,\ldots,v_{M-1})$ and sequence of edges $(e_0,\ldots,e_{M-1})$ satisfying following conditions. 

- $(e_0,\ldots,e_{M-1})$ is a permutation of $(0, \ldots, M-1)$. 
- For $0\leq i < M-1$, the edge $e_i$ is directed from $v_i$ to $v_{i+1}$. The edge $e_{M-1}$ is directed from $v_{M-1}$ to $v_0$. 

Note that an Eulerian circuit remains an Eulerian circuit after any cyclic shift.

Find the number of Eulerian circuits of $G$, considered the same if they can be obtained from one another by a cyclic shift (in other words, the number of Eulerian circuits with $e_0 = 0$), and give the result modulo $998244353$.

@{lang.ja}
$N$ 頂点 $M$ 辺の**有向**グラフ $G$ が与えられます．$i$ 番目の辺は頂点 $u_i$ から頂点 $v_i$ に向けて張られています．

$G$ の**オイラー閉路**とは，頂点の列 $(v_0,\ldots,v_{M-1})$ と辺の列 $(e_0,\ldots,e_{M-1})$ の組であって以下の条件を満たすもののことをいいます．

- $(e_0,\ldots,e_{M-1})$ は $(0, \ldots, M-1)$ の順列．
- $0\leq i < M-1$ に対して辺 $e_i$ は $v_i$ から $v_{i+1}$ に向けて張られている．辺 $e_{M-1}$ は $v_{M-1}$ から $v_0$ に向けて貼られている. 

オイラー閉路の巡回シフトは再びオイラー閉路になることに注意してください．

巡回シフトでうつりあうオイラー閉路を同一視した場合の $G$ のオイラー閉路の個数（言い換えれば，$e_0=0$ であるようなオイラー閉路の個数）を $998244353$ で割った余りを求めてください．
@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq u_i, v_i \lt N$


## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$
$\vdots$
$u_{M-1}$ $v_{M-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
