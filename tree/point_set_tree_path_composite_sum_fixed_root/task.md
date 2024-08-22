## @{keyword.statement}

@{lang.en}

You are given

- a tree with $N$ vertices,
- $N$ integers $a _ 0, a _ 1, \ldots, a _ {N-1}$ ,
- $N-1$ integers $b _ 0, b _ 1, \ldots, b _ {N-2}$ , and
- $N-1$ integers $c _ 0, c _ 1, \ldots, c _ {N-2}$ .

Edge $i$ connects vertices $u _ i$ and $v _ i$ bidirectionally.

For an integer $e$ that satisfies $0 \leq e \leq N-2$ , let $f _ e(x) = b _ e x + c _ e$ .

Let $e _ 0, e _ 1, \ldots, e _ k$ be the edges on the simple path from vertex $0$ to vertex $y$ in order, and define $P(y) = f _ {e _ 0}(f _ {e _ 1}(\ldots f _ {e _ k}(a _ y) \ldots ))$ .

Process $Q$ queries in the order they are given. There are two types of queries:

- `0 w x` : Update $a_w$ to $x$ and then print $\left(\sum_{v=0}^{N-1} P(v)\right) \bmod @{param.MOD}$.
- `1 e y z` : Update $(b_e, c_e)$ to $(y, z)$ and then print $\left(\sum_{v=0}^{N-1} P(v)\right) \bmod @{param.MOD}$.


@{lang.ja}

- $N$ 頂点の木、
- $N$ 個の整数 $a _ 0 , a _ 1 , \ldots , a _ {N-1}$ 、
- $N-1$ 個の整数 $b _ 0 , b _ 1 , \ldots , b _ {N-2}$ 、
- $N-1$ 個の整数 $c _ 0 , c _ 1 , \ldots , c _ {N-2}$

が与えられます。辺 $i$ は頂点 $u _ i$ と頂点 $v _ i$ を双方向に結びます。

$0\leq e \leq N-2$ を満たす整数 $e$ について、 $f _ e (x) = b _ e x + c _ e$ とします。

頂点 $0$ から頂点 $y$ までの単純パスに含まれる辺を順に $e _ 0,e _ 1, \ldots , e _ k$ として、 $P(y) = f _ {e _ 0}(f _ {e _ 1}(\ldots f _ {e _ k}(a _ y) \ldots ))$ とします。

$Q$ 個のクエリを与えられる順に処理してください。各クエリは次の $2$ 種類のいずれかです。

- `0 w x` : $a_w$ を $x$ に更新して、その後 $\left(\sum_{v=0}^{N-1} P(v)\right) \bmod @{param.MOD}$ を出力する。
- `1 e y z` : $(b_e, c_e)$ を $(y, z)$ に更新して、その後 $\left(\sum_{v=0}^{N-1} P(v)\right) \bmod @{param.MOD}$ を出力する。

@{lang.end}

## @{keyword.constraints}

@{lang.en}
- All input are integers.
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq u _ i, v _ i \leq N - 1$
- $@{param.A_MIN} \leq a _ w \lt @{param.MOD}$
- $@{param.B_MIN} \leq b _ e \lt @{param.MOD}$
- $@{param.C_MIN} \leq c _ e \lt @{param.MOD}$
- $0 \leq w \leq N - 1$
- $0 \leq e \leq N - 2$
- $@{param.A_MIN} \leq x \lt @{param.MOD}$
- $@{param.B_MIN} \leq y \lt @{param.MOD}$
- $@{param.C_MIN} \leq z \lt @{param.MOD}$

@{lang.ja}
- 入力は全て整数である
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq u _ i, v _ i \leq N - 1$
- $@{param.A_MIN} \leq a _ w \lt @{param.MOD}$
- $@{param.B_MIN} \leq b _ e \lt @{param.MOD}$
- $@{param.C_MIN} \leq c _ e \lt @{param.MOD}$
- $0 \leq w \leq N - 1$
- $0 \leq e \leq N - 2$
- $@{param.A_MIN} \leq x \lt @{param.MOD}$
- $@{param.B_MIN} \leq y \lt @{param.MOD}$
- $@{param.C_MIN} \leq z \lt @{param.MOD}$

@{lang.end}

## @{keyword.input}

@{lang.en}

$\mathrm{Query}_i$ represents the $i$-th query.

@{lang.ja}

$\mathrm{Query}_i$ は $i$ 番目のクエリを意味する。

@{lang.end}

```
$N$ $Q$
$a _ 0$ $a _ 1$ $\ldots$ $a _ {N-1}$
$u _ 0$ $v _ 0$ $b _ 0$ $c _ 0$
$u _ 1$ $v _ 1$ $b _ 1$ $c _ 1$
$\vdots$
$u _ {N-2}$ $v _ {N-2}$ $b _ {N-2}$ $c _ {N-2}$
$\mathrm{Query}_0$
$\mathrm{Query}_1$
$\vdots$
$\mathrm{Query}_{Q-1}$
```

## @{keyword.output}

@{lang.en}

$p_i$ represents the answer to the $i$-th query.

@{lang.ja}

$p_i$ は $i$ 番目のクエリへの答えを意味する。

@{lang.end}

```
$p_0$
$p_1$ 
$\vdots$
$p_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
