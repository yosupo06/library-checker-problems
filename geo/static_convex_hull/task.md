## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.

Given $N$ 2D points $(x _ i , y _ i)$ ($0\leq i\leq N - 1$), let $P$ be the convex hull of them. Output the coordinates of the vertices of $P$ in counterclockwise order.

For a more detailed definition, please see the following note.

Note:

- For a (multi-)set of 2D points $S$, denote the convex hull of $S$ as $\mathrm{conv}(S)$.
- Define $P$ as $P=\mathrm{conv}(\lbrace (x _ i, y _ i) \mid 0\leq i\leq N - 1\rbrace)$.
- We can prove that there exists the minimum set $S'$ satisfying $\mathrm{conv}(S')=P$. The vertices of $P$ are defined as the elements of $S'$.
- When $|S'|\leq 2$, output the points of $S'$ in any order. When $|S'|\geq 3$, we can prove that $P$ is a convex polygon and $S'$ are its vertices, and we can define its counterclockwise order. We can rotate the order, and any of them is accepted if it is counterclockwise.
- According to the above definitions, you should not output a point of $S$ on an edge of $P$ if it is not a vertex.
- The input may contain multiple points with the same coordinates, but your output should not contain multiple points with the same coordinates.

@{lang.ja}
この問題は $T$ ケースあります．

座標平面上の $N$ 個の点 $(x _ i, y _ i)$ ($0\leq i\leq N - 1$) が与えられます．$P$ をその凸包とするとき，$P$ の頂点の座標を反時計回り順に出力してください．

より詳細な定義については以下の注意を確認してください．

注意：

- 座標平面上の点の（多重）集合 $S$ に対し，その凸包を $\mathrm{conv}(S)$ と書くことにします．
- $P=\mathrm{conv}(\lbrace (x _ i, y _ i) \mid 0\leq i\leq N - 1\rbrace)$ と定義します．
- 点集合 $S'$ であって $\mathrm{conv}(S')=P$ を満たすもののうち最小のものが存在することが証明できます．$P$ の頂点を $S'$ の要素のことと定義します．
- $|S'|\leq 2$ のときには $S'$ の点を任意の順序で出力してください．$|S'|\geq 3$ のときには $P$ は凸多角形で $S'$ はその頂点全体に一致することが証明できます．したがって $S'$ に反時計回り順が定義できます．その順序を rotate することは可能ですが，反時計回り順でありさえすれば正答となります．
- 上の定義から，$S$ の点のうち $P$ の辺上にあるものであっても，$P$ の頂点でない場合には出力すべきではありません．
- 入力は同一座標の頂点を複数含む可能性がありますが，出力には同一座標の頂点を複数含めてはいけません．
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1\leq T\leq 10^5$
- $0 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $x_i, y_i$ are integers.
- The sum of $N$ over all test cases does not exceed $@{param.SUM_N_MAX}$

@{lang.ja}
- $1\leq T\leq 10^5$
- $0 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $x_i, y_i$ は整数.
- 全てのテストケースに対する $N$ の総和は $@{param.SUM_N_MAX}$ を超えない

@{lang.end}

## @{keyword.input}

```
$T$
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
$\vdots$
```

## @{keyword.output}

@{lang.en}

For each testcase, print the coordinates in the following format. 

@{lang.ja}

各テストケースに対して頂点の座標を以下の形式で出力してください．

@{lang.end}


```
$M$
$x'_0$ $y'_0$
$x'_1$ $y'_1$
:
$x'_{M - 1}$ $y'_{M - 1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
