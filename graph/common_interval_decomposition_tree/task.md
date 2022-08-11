## @{keyword.statement}
@{lang.en}
Given a size $N$ permutation $P_0, P_1, \cdots, P_{N-1}$
Output the **common interval decomposition tree** corresponding to this permutation. However, in this question, the words and phrases are defined as follows.

- **interval** is a set that can be expressed as $\lbrace i\in \mathbb{Z}\ |\ l \leq i \leq r\rbrace $ for some integers $l$,$r$ ($\ 0 \leq l \leq r <N$). However, we denote such a **interval** by **interval** $\[l, r\]$.
- **connected interval** is an **interval** $\[l, r\]$ where $\lbrace P_i\ |\ l \leq i \leq r\rbrace$ is also an **interval**.
- **strong interval** is a **connected interval** $I$ for which any **connected interval** $J$ either $I \subset J$ , $J \subset I$ , $I \cap J =\emptyset$ is true.
- **common interval decomposition tree** is a rooted tree shown by the Hasse diagram for semi-ordering by inclusion of the whole of a **strong interval**.
- **linear node** is when the child sequences are arranged in ascending order of the left end $l$ of the **interval**, the vertex for which the union set of any continuous subsequence is a **connected interval**.
- **prime node** is a vertex that is not a **linear node**.


@{lang.ja}
長さ $N$ の順列 $P_0, P_1, \cdots, P_{N-1}$ が与えられる。この順列に対応する **common interval decomposition tree** を出力せよ。ただし、本問において下記の様に語句を定義する。

- **interval** は ある整数 $l$,$r$ ($\ 0 \leq l \leq r <N$) に対して、$\lbrace i\in \mathbb{Z}\ |\ l \leq i \leq r \rbrace $ と表せる集合とする。この様な **interval** を **interval** $\[l, r\]$ と表す。
- **connected interval** は **interval** $\[l, r\]$ であって $\lbrace P_i\ |\ l \leq i \leq r\rbrace$ もまた **interval** となるものである。
-  **strong interval** とは **connected interval** $I$ の内、任意の **connected interval** $J$ に対して $I \subset J$ , $J \subset I$ , $I \cap J =\emptyset$ のいずれかが成り立つもののことをいう。
- **common interval decomposition tree** は **strong interval** 全体の包含による半順序についてのハッセ図 が示す根付き木である。
- **linear node** は子の列を区間の左端 $l$ の昇順に並べた時、どの連続部分列の和集合も **connected interval** となる頂点である。
- **prime node** は **linear node** でない頂点である。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq P_i < N$
- $P_i \neq P_j (i \neq j)$

## @{keyword.input}

~~~
$N$
$P_0\ P_1\ P_2\ \cdots P_{N-1}$
~~~

## @{keyword.output}

~~~
$X$
$p_0\ l_0\ r_0\ S_0$
$p_1\ l_1\ r_1\ S_1$
$\vdots$
$p_2\ l_{X-1}\ r_{X-1}\ S_{X-1}$
~~~

@{lang.en}
$X$ is the number of vertices in the **common interval decomposition tree**.$p_i$( $p_i < i$ ) is the number of the vertex that is the parent of the $i$-th vertex, but $p_i=-1$ when the $i$-th vertex is a tree root. $\[l_i,r_i\]$ is the **interval** corresponding to the $i$-th vertex, and $S_i$ is "linear" if the $i$-th vertex is a **linear node** or "prime" if it is a **prime node**.

@{lang.ja}
$X$ は **common interval decomposition tree** の頂点数。$p_i$( $p_i < i$ ) は $i$ 番目の頂点の親となる頂点の番号、ただし $i$ 番目の頂点が木の根である時、 $p_i=-1$。 $\[l_i,r_i\]$ は $i$ 番目の頂点に対応する **interval** とし、$S_i$ は $i$ 番目の頂点が **linear node** なら "linear" 、**prime node** なら "prime"。

@{lang.end}

@{example.example_00}

@{example.example_01}

@{example.example_02}