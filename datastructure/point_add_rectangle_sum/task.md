## @{keyword.statement}
@{lang.en}
You are given $N$ weighted points on two-dimensional plane. $i$-th is at ($x_i$, $y_i$) and has a weight of $w_i$.
Process the following queries in order.

 - `0 $x$ $y$ $w$` : Add a new point with weight $w_i$ at $(x, y)$. If there is another point at the same coordinates, add as a distinct point.
 - `1 $l$ $d$ $r$ $u$` : Find the sum of weight of points that $l \leq x < r$, $d \leq y < u$ is satisfied.

@{lang.ja}
$2$ 次元平面上に重み付きの点が $N$ 個あります。 $i$ 個目の座標は$(x_i, y_i)$で重みは$w_i$です。
以下の $2$ 種類のクエリ $Q$ 個を処理してください

 - `0 $x$ $y$ $w$` : $(x, y)$に重み$w$の点を追加する。既に同じ位置に点があっても別の点として追加する
 - `1 $l$ $d$ $r$ $u$` : $l \leq x < r$, $d \leq y < u$ を満たす点について、重みの総和を求める
@{lang.end}

## @{keyword.constraints}
@{lang.en}

 - $1 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le x_i, y_i \le @{param.COORD_MAX}$
 - $0 \le w_i \le @{param.WEIGHT_MAX}$
 - For queries of type `0 $x$ $y$ $w$`
     - $0 \le x, y \le @{param.COORD_MAX}$
     - $0 \le w \le @{param.WEIGHT_MAX}$
 - For queries of type `1 $l$ $d$ $r$ $u$`
     - $0 \le l \lt r \le @{param.COORD_MAX}$
     - $0 \le d \lt u \le @{param.COORD_MAX}$

@{lang.ja}

 - $1 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le x_i, y_i \le @{param.COORD_MAX}$
 - $0 \le w_i \le @{param.WEIGHT_MAX}$
 - `0 $x$ $y$ $w$`形式のクエリについて
     - $0 \le x, y \le @{param.COORD_MAX}$
     - $0 \le w \le @{param.WEIGHT_MAX}$
 - `1 $l$ $d$ $r$ $u$`形式のクエリについて
     - $0 \le l \lt r \le @{param.COORD_MAX}$
     - $0 \le d \lt u \le @{param.COORD_MAX}$

@{lang.end}

## @{keyword.input}
~~~
$N$ $Q$
$x_1$ $y_1$ $w_1$
$x_2$ $y_2$ $w_2$
$x_3$ $y_3$ $w_3$
$\hspace{17pt} \vdots$
$x_N$ $y_N$ $w_N$
$\mathrm{Query}_0$
$\mathrm{Query}_1$
$\mathrm{Query}_2$
$\hspace{13pt} \vdots$
$\mathrm{Query}_{Q - 1}$
~~~

@{example.example_00}
