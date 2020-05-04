## @{keyword.statement}
$N$ 頂点 $M$ 辺の有向グラフが与えられる。$i$ 番目の辺は頂点 $a_i$ から $b_i$ に貼られている。

頂点 $S$ を根とする dominator tree を求めよ。


## @{keyword.constraints}

- $1 \leq N \leq 200,000$
- $0 \leq M \leq 200,000$
- $0 \leq S, a_i, b_i < N$

## @{keyword.input}

~~~
$N$ $M$ $S$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{M - 1}$ $b_{M - 1}$
~~~

## @{keyword.output}

~~~
$p_0$ $p_1$ $p_2$ ... $p_{N - 1}$
~~~

$p_i$ は頂点 $i$ の親である。頂点 $S$ から頂点 $i$ へ到達できない場合、$-1$ を出力。また、$p_S = S$ とすること。


## @{keyword.sample}

@{example.example_00}

@{example.example_01}
