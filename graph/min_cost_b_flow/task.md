## @{keyword.statement}

$\gdef\relmiddle#1{\mathrel{}\middle#1\mathrel{}}$

@{lang.en}
You are given a directed graph with $n$ vertices and $m$ edges, amount of supply/demand associated with each vertex, and flow lower/upper bound associated with each edge.
The $v$-th vertex has $b_v$ amount of supply if $b_v$ was positive, and $-b_v$ amount of demand otherwise.
The $e$-th edge is directed from vertex $s_e$ to $t_e$ and has flow lower bound $l_e$, flow upper bound $u_e$, and cost per a unit of flow $c_e$.

Your task is to find and print the minimum cost $\mathbf{b}$-flow value $z$, the flow $\mathbf{f}$ and its dual $\mathbf{p}$ that achives the minimum, that is, $z$, $\mathbf{f} = \lbrace f_e\rbrace _ {e = 0 \dots m-1}$, and $\mathbf{p} = \lbrace p_v\rbrace _ {v = 0 \dots n-1}$ that satisfies following constraints;

- $z = \sum_{e} c_e f_e$
- $l_e \leq f_e \leq u_e$ (Capacity constraints)
- $\sum_{e \in \delta^+(v)} f_e - \sum_{e \in \delta^-(v)} f_e = b_v$ (Flow conservation constraints)
- $f_e \gt l_e \Rightarrow c_e + p_{s_e} - p_{t_e} \le 0$ (Complementary slackness conditions)
- $f_e \lt u_e \Rightarrow c_e + p_{s_e} - p_{t_e} \ge 0$ (Complementary slackness conditions)
- $|p_v| \le @{param.P_MAX}$

where $\delta^+(v)$ is the set of edges leaving vertex $v$ and $\delta^-(v)$ is the set of edges entering vertex $v$, i.e. $\delta^+(v) = \left\lbrace e \relmiddle| s_e = v \right\rbrace$ and $\delta^-(v) = \left\lbrace e \relmiddle| t_e = v \right\rbrace$.

If there's no such values, output "infeasible" instead.

@{lang.ja}
$n$ 頂点 $m$ 辺の有向グラフ, 頂点に付随する需要/供給量, 辺に付随する流量上下限とコストが与えられます.
$v$ 番目の頂点は, $b_v$ が正のとき $b_v$ の供給点であり, そうでないとき $-b_v$ の需要点です.
また, $e$ 番目の辺は頂点 $s_e$ から頂点 $t_e$ に張られており, 流量下限 $l_e$, 流量上限 $u_e$, 単位流量あたりのコスト $c_e$ です.

このネットワーク上の最小コスト $z$, それを達成する $\mathbf{b}$-フロー $\mathbf{f}$ と双対変数 $\mathbf{p}$, すなわち次を満たす $z$, $\mathbf{f} = \lbrace f_e\rbrace _ {e = 0 \dots m-1}$ と $\mathbf{p} = \lbrace p_v\rbrace _ {v = 0 \dots n-1}$ を求めて出力して下さい.
そのようなものが存在しないならば, "infeasible" と出力してください.

- $z = \sum_{e} c_e f_e$
- $l_e \leq f_e \leq u_e$ (容量制約)
- $\sum_{e \in \delta^+(v)} f_e - \sum_{e \in \delta^-(v)} f_e = b_v$ (フロー整合性条件)
- $f_e \gt l_e \Rightarrow c_e + p_{s_e} - p_{t_e} \le 0$ (相補性条件)
- $f_e \lt u_e \Rightarrow c_e + p_{s_e} - p_{t_e} \ge 0$ (相補性条件)
- $|p_v| \le @{param.P_MAX}$

ここで, $\delta^+(v)$ は $v$ から出る辺全体の集合 $\left\lbrace e \relmiddle| s_e = v \right\rbrace$, $\delta^-(v)$ は $v$ へ入る辺全体の集合 $\left\lbrace e \relmiddle| t_e = v \right\rbrace$ です.
@{lang.end}

## @{keyword.constraints}

- $0 \le n \leq @{param.N_MAX}$
- $0 \le m \leq @{param.M_MAX}$
- $0 \le s_e \lt n$
- $0 \le t_e \lt n$
- $|b_v| \le @{param.U_MAX}$
- $|l_e| \le @{param.U_MAX}$
- $|u_e| \le @{param.U_MAX}$
- $|c_e| \le @{param.C_MAX}$
- $l_e \le u_e$
- All of the values are integral

Note that

- the input graph may contain self loops,
- and the result value may exceed $2^{64}$.


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
If the problem was infeasible output a single line
```
infeasible
```
. Otherwise,
```
$z$
$p_0$
 $\vdots$
$p_{n-1}$
$f_0$
 $\vdots$
$f_{m-1}$
```

## @{keyword.sample}

@{example.example_00}
@{example.example_01}
@{example.example_02}
