## @{keyword.statement}

@{lang.en}
This problem has $T$ cases. 

You are given a **directed** graph $G$, consisting of $N$ vertices and $M$ edges. The $i$-th edge is directed from $u_i$ to $v_i$. 

An **eulerian trail** of $G$ is a pair of sequence of vertices $(v_0,\ldots,v_M)$ and sequence of edges $(e_0,\ldots,e_{M-1})$ satisfying following conditions. 

- $(e_0,\ldots,e_{M-1})$ is a permutation of $(0, \ldots, M-1)$. 
- For $0\leq i < M-1$, the edge $e_i$ is directed from $v_i$ to $v_{i+1}$. 

Determine if an eulerian trail of $G$ exists, and output if it exists. 

@{lang.ja}
この問題は $T$ ケースあります．

$N$ 頂点 $M$ 辺の**有向**グラフ $G$ が与えられます．$i$ 番目の辺は頂点 $u_i$ から頂点 $v_i$ に向けて張られています．

$G$ の**オイラー路**とは，頂点の列 $(v_0,\ldots,v_{M})$ と辺の列 $(e_0,\ldots,e_{M-1})$ の組であって以下の条件を満たすもののことをいいます．

- $(e_0,\ldots,e_{M-1})$ は $(0, \ldots, M-1)$ の順列．
- $0\leq i < M-1$ に対して辺 $e_i$ は $v_i$ から $v_{i+1}$ に向けて張られている．

$G$ のオイラー路が存在するか否かを判定し，含む場合にはそのひとつを求めてください．
@{lang.end}


## @{keyword.constraints}
@{lang.ja}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq u_i, v_i \lt N$
- The sum of $N$ over all test cases does not exceed $@{param.N_MAX}$. 
- The sum of $M$ over all test cases does not exceed $@{param.N_MAX}$. 

@{lang.en}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq u_i, v_i \lt N$
- 全てのテストケースに対する $N$ の総和は $@{param.N_MAX}$ を超えない．
- 全てのテストケースに対する $M$ の総和は $@{param.M_MAX}$ を超えない．

@{lang.end}

## @{keyword.input}

~~~
$T$
$N$ $M$
$u_0$ $v_0$
$\vdots$
$u_{M-1}$ $v_{M-1}$
$N$ $M$
$u_0$ $v_0$
$\vdots$
$u_{M-1}$ $v_{M-1}$
$vdots$
~~~

## @{keyword.output}

@{lang.en}

If there exists no eulerian trail, print `No`. Otherwise, print an eulerian trail in the following format. 

@{lang.ja}

オイラー路が存在しない場合には `No` を出力してください．オイラー路が存在する場合には，それを次の形式で出力してください．

@{lang.end}

~~~
Yes
$v_0$ $\ldots$ $v_{M}$
$e_0$ $\ldots$ $e_{M-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
