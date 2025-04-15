## @{keyword.statement}
@{lang.en}
You are given a tree with $N$ vertices. $i$-th edge connects vertex $u_i$ and vertex $v_i$. A number $a_i$ is written on vertex $i$.

Process $Q$ queries of the following types in order :

 - `0 $u$ $v$ $w$ $x$`: remove edge $(u, v)$ and add a new edge $(w, x)$. It is guranteed that the graph remains a tree after processing.
 - `1 $v$ $p$ $x$`: focusing on edge $(v, p)$ and regarding $p$ as a parent, add $x$ to values of all vertices in the subtree of vertex $v$.
 - `2 $v$ $p$`: focusing on edge $(v, p)$ and regarding $p$ as a parent, find the sum over values of all vertices in the subtree of vertex $v$.

@{lang.ja}
$N$ 頂点の木が与えられます。$i$ 番目の辺は頂点 $u_i$ と頂点 $v_i$ を結んでいます。また、頂点 $i$ には値 $a_i$ が書かれています。

以下のクエリ $Q$ 個を処理してください。

 - `0 $u$ $v$ $w$ $x$` : 辺 $(u, v)$ を削除し、辺 $(w, x)$ を作成する。処理後もグラフが木であることが保証される。
 - `1 $v$ $p$ $x$` : 辺 $(v, p)$ について、頂点 $p$ を親としたときの頂点 $v$ の部分木に含まれる頂点の値にそれぞれ $x$ を足す。
 - `2 $v$ $p$` : 辺 $(v, p)$ について、頂点 $p$ を親としたときの頂点 $v$ の部分木に含まれる頂点の値の総和を出力する。

@{lang.end}


## @{keyword.constraints}
@{lang.en}

 - $2 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le a_i \le @{param.VAL_MAX}$
 - $0 \le u_i, v_i < N$
 - The graph is a tree
 - For queries of type `0 $u$ $v$ $w$ $x$` :
    - $0 \le u, v, w, x \lt N$
    - Edge $(u, v)$ exists when processing a query of this type
    - The graph remains a tree after processing
 - For queries of type `1 $v$ $p$ $x$` :
    - $0 \le v, p \lt N$
    - $0 \le x \le @{param.VAL_MAX}$
    - Edge $(v, p)$ exists when processing a query of this type
 - For queries of type `2 $v$ $p$` :
    - $0 \le v, p \lt N$
    - Edge $(v, p)$ exists when processing a query of this type

@{lang.ja}

 - $2 \le N \le @{param.N_MAX}$
 - $1 \le Q \le @{param.Q_MAX}$
 - $0 \le a_i \le @{param.VAL_MAX}$
 - $0 \le u_i, v_i < N$
 - 与えられるグラフは木
 - `0 $u$ $v$ $w$ $x$`形式のクエリについて
    - $0 \le u, v, w, x \lt N$
    - その時点で辺 $(u, v)$ は存在する
    - 処理後もグラフは木
 - `1 $v$ $p$ $x$`形式のクエリについて
    - $0 \le v, p \lt N$
    - $0 \le x \le @{param.VAL_MAX}$
    - その時点で辺 $(v, p)$ は存在する
 - `2 $v$ $p$`形式のクエリについて
    - $0 \le v, p \lt N$
    - その時点で辺 $(v, p)$ は存在する

@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$u_0$ $v_0$
$u_1$ $v_1$
$\hspace{11pt} \vdots$
$u_{N - 2}$ $v_{N - 2}$
$\mathrm{Query}_0$
$\mathrm{Query}_1$
$\hspace{14pt} \vdots$
$\mathrm{Query}_{Q - 1}$
~~~

@{example.example_00}
