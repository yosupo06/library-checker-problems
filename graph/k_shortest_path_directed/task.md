## @{keyword.statement}

@{lang.en}
You are given a weighted directed graph consisting of $N$ vertices and $M$ edges. The $i$-th edge is directed from the vertex $u_i$ to the vertex $v_i$ and has a weight of $c_i$. This graph may not be simple.

For $i=1,2,\ldots ,K$, output $x_i$, the length of the $i$-th shortest (simple) path from vertex $s$ to vertex $t$. If such path doesn't exist, let $x_i=-1$ .

Multiple paths with the same length are considered different paths.
@{lang.ja}
$N$ 頂点 $M$ 辺の重み付き有向グラフが与えられる。 $i$ 番目の辺は頂点 $a_i$ とから頂点 $b_i$ に向かっていて、重さは $c_i$ です。このグラフは単純とは限りません。

頂点 $s$ から頂点 $t$ への(単純な)パスのうち $i$ 番目に短いものの長さ $x_i$ を、 $i=1,2,\ldots ,K$ についてそれぞれ出力してください。パスが存在しない場合は $x_i=-1$ とします。

ただし、長さが同じパスが複数ある場合、それらは別物として考えます。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $@{param.K_MIN} \leq K \leq @{param.K_MAX}$
- $0 \leq s, t < N$
- $s \neq t$
- $0 \leq u_i, v_i < N$
- $@{param.C_MIN} \leq c_i \leq @{param.C_MAX}$

## @{keyword.input}

~~~
$N$ $M$ $s$ $t$ $K$
$u_0$ $v_0$ $c_0$
$u_1$ $v_1$ $c_1$
$\vdots$
$u _ {M-1}$ $v _ {M-1}$ $c _ {M-1}$
~~~

## @{keyword.output}

~~~
$x _ 1$
$x _ 2$
$\vdots$
$x _ K$
~~~

@{example.example_00}
