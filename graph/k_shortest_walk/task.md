## @{keyword.statement}

頂点数 $N$、辺数 $M$ の単純とは限らないグラフが与えられる。$i$番目の辺は頂点$a_i$から$b_i$にはられており、重さ$c_i$である。

頂点$s$から頂点$t$への$1$番目から$K$番目に短いウォークの長さをそれぞれ出力してください。その様な経路が存在しない場合は-1を出力してください。

## @{keyword.constraints}

- $@{param.N_AND_M_MIN} \leq N, M \leq @{param.N_AND_M_MAX}$
- $@{param.K_MIN} \leq K \leq @{param.K_MAX}$
- $0 \leq s, t < N$
- $0 \leq u_i, v_i < N$
- $@{param.C_MIN} \leq c_i \leq @{param.C_MAX}$

## @{keyword.input}

~~~
$N~M~K$
$s~t$
$u_0~v_0~c_0$
$u_1~v_1~c_1$
$u_2~v_2~c_2$
:
$u_{M-1}~v_{M-1}~c_{M-1}$
~~~

@{example.example_00}
