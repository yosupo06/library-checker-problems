## @{keyword.statement}

@{lang.en}
A Sequence of triples of integers $\bigl((p_i, a_i, b_i)\bigr)_{0\leq i < N}$ is given. 
Process $Q$ queries as follows:

- `0 $i$ $p$ $a$ $b$`: change $(p_i,a_i,b_i) \gets (p,a,b)$.
- `1 $l$ $r$ $x$`: print $f_{r-1}(f_{r-2}(...f_l(x))) \bmod @{param.MOD}$, where $f_i(x) := a_ix + b_i$.
- `2 $l$ $r$`: Sort $\bigl((p_i, a_i, b_i)\bigr)_{l\leq i < r}$ so that $p_i$ is **increasing**. 
- `3 $l$ $r$`: Sort $\bigl((p_i, a_i, b_i)\bigr)_{l\leq i < r}$ so that $p_i$ is **decreasing**. 

@{lang.ja}
整数の $3$ つ組の列 $\bigl((p_i, a_i, b_i)\bigr)_{0\leq i < N}$ が与えられます。
次の $Q$ 個のクエリを処理してください。

- `0 $i$ $p$ $a$ $b$`: $(p_i, a_i, b_i)$ を $(p, a, b)$ に変更する。
- `1 $l$ $r$ $x$`: $f_i(x) = a_ix + b_i$ とするとき、$f_{r-1}(f_{r-2}(...f_l(x))) \bmod @{param.MOD}$ を出力する。
- `2 $l$ $r$`：$\bigl((p_i, a_i, b_i)\bigr)_{l\leq i < r}$ を $p_i$ が**昇順**に並ぶようにソートする。
- `3 $l$ $r$`：$\bigl((p_i, a_i, b_i)\bigr)_{l\leq i < r}$ を $p_i$ が**降順**に並ぶようにソートする。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq i < N$
- $@{param.P_MIN} \leq p_i, p \leq @{param.P_MAX}$
- All values $p_i, p$ (initial values and values given in query 0) are distinct. 
- $1 \leq a_i, a < @{param.MOD}$
- $0 \leq b_i, b < @{param.MOD}$
- $0 \leq x < @{param.MOD}$
- $0 \leq l < r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$p_0$ $a_0$ $b_0$
$\vdots$
$p_{N-1}$ $a_{N-1}$ $b_{N-1}$
$\textrm{Query}_0$
$\vdots$
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}

@{example.example_01}
