## @{keyword.statement}
@{lang.en}

You are given an initial multiset of $N$ weighted points, $P = (P_0, P_1, \dots, P_{N - 1})$, on a two-dimensional plane. Each point $P_i$ ($0 \leq i < N$) is located at $(x_i, y_i)$ and has an associated weight $w_i$. Process $Q$ queries of the following types. For the $i$-th ($0\leq i < Q$) query:

- `0 $x$ $y$ $w$`: Append a new point with weight $w$ at coordinates $(x, y)$. Let $k = |P|$ before the addition, then refer to this point as $P_k$. If a point already exists at these coordinates, add the new point as a separate instance.
- `1 $x$ $w$`: Update the weight of point $P_x$ to $w$. (i.e., $w_x \gets w$)

- `2 $l$ $d$ $r$ $u$`: Calculate the sum of weights modulo $@{param.MOD}$ for all points where $l \leq x_i < r$ and $d \leq y_i < u$.

- `3 $l$ $d$ $r$ $u$ $a$ $b$`: For each $i$ such that $l \leq x_i < r$ and $d \leq y_i < u$, apply the transformation $w_i \gets a \cdot w_i + b$.

@{lang.ja}

座標平面上の $N$ 個の点 $P = (P_0, P_1, \dots, P_{N - 1})$ が与えられます．各 $P_i$ は $(x_i, y_i)$ にあり，重み $w_i$ が定まっています．点の座標が相異なるとは限りません．

$Q$ 個のクエリを処理してください．$i$ 番目のクエリ（$0\leq i<Q$）は次の形式です．

- `0 $x$ $y$ $w$`: 新たに重み $w$ の点を $(x,y)$ に追加する．追加前に $k=|P|$ とするとき，この点を $P_k$ と呼ぶ．

- `1 $x$ $w$`: $P_x$ の重みを $w$ に変更する（つまり $w_x \gets w$）．

- `2 $l$ $d$ $r$ $u$`: $l \leq x_i < r$ かつ $d \leq y_i < u$ を満たすようなすべての点 $P_i$ の重み $w_i$ の和を $@{param.MOD}$ で出力せよ．

- `3 $l$ $d$ $r$ $u$ $a$ $b$`: $l \leq x_i < r$ and $d \leq y_i < u$ を満たすようなすべての点 $P_i$ の重み $w_i$ を $w_i \gets a \cdot w_i + b$ と変更する．
@{lang.end}

## @{keyword.constraints}
@{lang.en}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq x_i, y_i \leq @{param.COORD_MAX}$
- $0 \leq w_i < @{param.MOD}$

For each query type:
- Type `0`: $0 \leq x, y \leq @{param.COORD_MAX}$, $0 \leq w < @{param.MOD}$
- Type `1`: $0\leq x < |P|, 0\leq w < @{param.MOD}$
- Type `2`: $0 \leq l < r \leq @{param.COORD_MAX}$, $0 \leq d < u \leq @{param.COORD_MAX}$
- Type `3`: $0 \leq l < r \leq @{param.COORD_MAX}$, $0 \leq d < u \leq @{param.COORD_MAX}$, $0 \leq a, b < @{param.MOD}$

@{lang.ja}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq x_i, y_i \leq @{param.COORD_MAX}$
- $0 \leq w_i < @{param.MOD}$

各クエリについて，
- Type `0`: $0 \leq x, y \leq @{param.COORD_MAX}$, $0 \leq w < @{param.MOD}$
- Type `1`: $0\leq x < |P|, 0\leq w < @{param.MOD}$
- Type `2`: $0 \leq l < r \leq @{param.COORD_MAX}$, $0 \leq d < u \leq @{param.COORD_MAX}$
- Type `3`: $0 \leq l < r \leq @{param.COORD_MAX}$, $0 \leq d < u \leq @{param.COORD_MAX}$, $0 \leq a, b < @{param.MOD}$

@{lang.end}

## @{keyword.input}
~~~
$N$ $Q$
$x_0$ $y_0$ $w_0$
$x_1$ $y_1$ $w_1$
$x_2$ $y_2$ $w_2$
$\hspace{17pt} \vdots$
$x_{N - 1}$ $y_{N - 1}$ $w_{N - 1}$
$\mathrm{Query}_0$
$\mathrm{Query}_1$
$\mathrm{Query}_2$
$\hspace{13pt} \vdots$
$\mathrm{Query}_{Q - 1}$
~~~

@{example.example_00}
