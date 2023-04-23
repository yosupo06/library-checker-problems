## @{keyword.statement}

@{lang.en}

You are given

- a tree with $N$ vertices,
- $N$ integers $a _ 0, a _ 1, \ldots, a _ {N-1}$ ,
- $N-1$ integers $b _ 0, b _ 1, \ldots, b _ {N-2}$ , and
- $N-1$ integers $c _ 0, c _ 1, \ldots, c _ {N-2}$ .

Edge $i$ connects vertices $u_i$ and $v_i$ bidirectionally.

For an integer $e$ that satisfies $0 \leq e \leq N-2$ , let $f _ e(x) = b _ e x + c _ e$ .

Let $e _ 0, e _ 1, \ldots, e _ k$ be the edges on the simple path from vertex $x$ to vertex $y$ in order, and define $P(x, y) = f_{e _ 0}(f _ {e _ 1}(\ldots f _ {e _ k}(a _ y) \ldots ))$ .

Find $\sum _ {y=0} ^ {N-1} P(x, y)$ modulo $@{param.MOD}$ for each vertex $x$ .

@{lang.ja}

- $N$ 頂点の木、
- $N$ 個の整数 $a _ 0 , a _ 1 , \ldots , a _ {N-1}$ 、
- $N-1$ 個の整数 $b _ 0 , b _ 1 , \ldots , b _ {N-2}$ 、
- $N-1$ 個の整数 $c _ 0 , c _ 1 , \ldots , c _ {N-2}$

が与えられます。辺 $i$ は頂点 $u _ i$ と頂点 $v _ i$ を双方向に結びます。

$0\leq e \leq N-2$ を満たす整数 $e$ について、 $f _ e (x) = b _ e x + c _ e$ とします。

頂点 $x$ から頂点 $y$ までの単純パスに含まれる辺を順に $e _ 0,e _ 1, \ldots , e _ k$ として、 $P(x,y)=f_{e_0}(f_{e_1}( \ldots f_{e_k}( a_y ) \ldots ))$ とします。

各頂点 $x$ について $\sum_{y=0}^{N-1} P(x,y)$ を $@{param.MOD}$ で割ったあまりを求めてください。 

@{lang.end}

## @{keyword.constraints}

@{lang.en}
- All input are integers.
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq u _ i, v _ i \leq N - 1$
- $u _ i \neq v _ i$
- $@{param.A_MIN} \leq a _ i \leq @{param.A_MAX}$
- $@{param.B_MIN} \leq b _ i \leq @{param.B_MAX}$
- $@{param.C_MIN} \leq c _ i \leq @{param.C_MAX}$

@{lang.ja}
- 入力は全て整数である
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq u _ i, v _ i \leq N - 1$
- $u _ i \neq v _ i$
- $@{param.A_MIN} \leq a _ i \leq @{param.A_MAX}$
- $@{param.B_MIN} \leq b _ i \leq @{param.B_MAX}$
- $@{param.C_MIN} \leq c _ i \leq @{param.C_MAX}$

@{lang.end}

## @{keyword.input}

```
$N$
$a _ 0$ $a _ 1$ $\ldots$ $a _ {N-1}$
$u _ 0$ $v _ 0$ $b _ 0$ $c _ 0$
$u _ 1$ $v _ 1$ $b _ 1$ $c _ 1$
$\vdots$
$u _ {N-2}$ $v _ {N-2}$ $b _ {N-2}$ $c _ {N-2}$
```

## @{keyword.output}

```
$q _ 0$ $q _ 1$ $\ldots$ $q _ {N-1}$
```
@{lang.en}
$q _ i$ is the answer where $x = i$ .

@{lang.ja}
$q _ i$ は $x = i$ のときの答えです。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
