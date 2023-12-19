## @{keyword.statement}
@{lang.en}
You are given $N$ weighted rectangles on two-dimensional plane.
The position of $i$-th rectangle is 
$$[l_i,r_i) \times [d_i,u_i) = \{(x,y)\in \mathbb{R}^2\mid l_i\leq x<r_i, d_i\leq y<u_i\}$$
and has a weight of $w_i$. Process $Q$ queries of the following types.

 - `0 $l$ $d$ $r$ $u$ $w$` : Add a new rectangle with weight $w$ at $[l,r) \times [d,u)$. 
 - `1 $x$ $y$` : Find the sum of weight of rectangles which contain $(x,y)$. 

@{lang.ja}
$2$ 次元平面上に重み付きの長方形が $N$ 個あります．$i$ 個目の長方形の位置は
$$[l_i,r_i) \times [d_i,u_i) = \{(x,y)\in \mathbb{R}^2\mid l_i\leq x<r_i, d_i\leq y<u_i\}$$
であり，重みは $w_i$ です．以下の $2$ 種類のクエリ $Q$ 個を処理してください．

 - `0 $l$ $d$ $r$ $u$ $w$` : 新たに重み $w$ の長方形を $[l,r) \times [d,u)$ に追加する．
 - `1 $x$ $y$` : $(x,y)$ を含む長方形の重みの総和を求める．
 
 @{lang.end}

## @{keyword.constraints}
@{lang.en}

 - $1 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le l_i \lt r_i \le @{param.COORD_MAX}$
 - $0 \le d_i \lt u_i \le @{param.COORD_MAX}$
 - $0 \le w_i \le @{param.WEIGHT_MAX}$
 - For queries of type `0 $l$ $d$ $r$ $u$ $w$`
     - $0 \le l \lt r \le @{param.COORD_MAX}$
     - $0 \le d \lt u \le @{param.COORD_MAX}$
     - $0 \le w \le @{param.WEIGHT_MAX}$
 - For queries of type `1 $x$ $y$`
     - $0 \le x, y \le @{param.COORD_MAX}$

@{lang.ja}

 - $1 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le l_i \lt r_i \le @{param.COORD_MAX}$
 - $0 \le d_i \lt u_i \le @{param.COORD_MAX}$
 - $0 \le w_i \le @{param.WEIGHT_MAX}$
 - `0 $l$ $d$ $r$ $u$ $w$` 形式のクエリについて
     - $0 \le l \lt r \le @{param.COORD_MAX}$
     - $0 \le d \lt u \le @{param.COORD_MAX}$
     - $0 \le w \le @{param.WEIGHT_MAX}$
 - `1 $x$ $y$` 形式のクエリについて
     - $0 \le x, y \le @{param.COORD_MAX}$
@{lang.end}

## @{keyword.input}
~~~
$N$ $Q$
$l_0$ $d_0$ $r_0$ $u_0$ $w_0$
$\vdots$
$l_{N-1}$ $d_{N-1}$ $r_{N-1}$ $u_{N-1}$ $w_{N-1}$
$\mathrm{Query}_0$
$\vdots$
$\mathrm{Query}_{Q - 1}$
~~~

@{example.example_00}
