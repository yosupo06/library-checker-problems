Problem Statement (Japanese) / 問題文 (日本語)
---------


$N$ 頂点の空グラフが与えられる。頂点 $i$ には値 $a_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。

- `0 u v` : 頂点uと頂点vを繋ぐ辺を張る (このクエリの前、頂点uと頂点vは辺で結ばれてない事が保証されます)
- `1 u v` : 頂点uと頂点vを繋ぐ辺を削除する (このクエリの前、頂点uと頂点vは辺で結ばれている事が保証されます)
- `2 $v$ $x$` : $a_v \gets a_v + x$
- `3 v`   : 頂点iとの間にpathが存在する頂点に書かれた値の総和を出力




Constraints / 制約
---------

- $1 \leq N, Q \leq 200,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq u_i, v_i < N$
- $u_i \neq v_i$
- クエリ処理後もグラフが単純グラフであることが保証される

Input / 入力
---------

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
