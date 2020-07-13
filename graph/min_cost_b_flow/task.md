## @{keyword.statement}

@{lang.en}
TODO
@{lang.ja}
$n$ 頂点 $m$ 辺のグラフ, 頂点に付随する吸込み/湧出し量, 辺に付随する流量上下限とコストが与えられます.
$v$ 番目の頂点は, $b_v$ が正のとき $b_v$ の湧出しであり, そうでないとき $-b_v$ の吸込みです.
$e$ 番目の辺は頂点 $s_e$ から頂点 $t_e$ に張られており, 流量下限 $l_e$, 流量上限 $u_e$, 単位流量あたりのコスト $c_e$ です.

このネットワーク上の最小コスト$\mathbf{b}$-フロー $\mathbf{f}$ と双対変数 $\mathbf{p}$ で大きすぎないもの, すなわち次を満たす $\mathbf{f} = \{f_e\}_{e = 0 \dots m-1}$ と $\mathbf{p} = \{p_v\}_{v = 0 \dots n-1}$ を求めて出力して下さい.
そのようなものが存在しないならば, その旨を報告して下さい.

- $l_e \leq f_e \leq u_e$ (容量制約)
- $\sum_{e \in \delta^+(v)} f_e - \sum_{e \in \delta^-(v)} f_e = b_v$ (フロー整合性条件)
- $f_e \gt l_e \Rightarrow c_e + p_{s_e} - p_{t_e} \le 0$ (相補性条件)
- $f_e \lt u_e \Rightarrow c_e + p_{s_e} - p_{t_e} \ge 0$ (相補性条件)
- $|p_v| \le @{param.P_MAX}$

ここで, $\delta^+(v)$ は $v$ から出る辺全体の集合 $\left\{ e | s_e = v \right\}$, $\delta^-(v)$ は $v$ へ入る辺全体の集合 $\left\{ e | t_e = v \right\}$ です.
@{lang.end}

## @{keyword.constraints}

- $0 \le n \leq @{param.N_MAX}$
- $0 \le m \leq @{param.M_MAX}$
- $0 \le s_e \lt n$
- $0 \le t_e \lt m$
- $|b_v| \le @{param.U_MAX}$
- $|l_v| \le @{param.U_MAX}$
- $|u_v| \le @{param.U_MAX}$
- $|c_e| \le @{param.C_MAX}$
- all of the values are integral


## @{keyword.input}

```
$n$ $m$
$b_0$
 $\vdots$
$b_{n-1}$
$s_0$ $t_0$ $l_0$ $u_0$ $c_0$
 $\vdots$
$s_{m-1}$ $t_{m-1}$ $l_{m-1}$ $u_{m-1}$ $c_{m-1}$
```

## @{keyword.output}

```
$p_0$
 $\vdots$
$p_{n-1}$
$f_0$
 $\vdots$
$f_{m-1}$
```

## @{keyword.sample}

@{example.example_00}
