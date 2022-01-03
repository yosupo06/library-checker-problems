## @{keyword.statement}
@{lang.en}
Given a size $N$ permutation $P_0, P_1, \cdots, P_{N-1}$.
Calculate the permutation tree.

@{lang.ja}
長さ $N$ の順列 $P_0, P_1, \cdots, P_{N-1}$. が与えられる。
Permutation tree を preorder で出力して下さい。


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
$l_0\ r_0\ S_0$
$l_1\ r_1\ S_1$
\vdots
$l_{X-1}\ r_{X-1}\ S_{X-1}$
~~~

@{lang.en}
$X$ is vertex size of permutation tree, and $\[l_i,r_i-1\]$ is the interval on P corresponding to the i-th node of the permutation tree.
S_i is "join" if the i-th node of the permutation tree is join node and "cut" otherwise.

@{lang.ja}
$X$ は permutation tree の頂点数です。 $\[l_i,r_i-1\]$ は permutation tree の $i$ 番目の頂点に対応する順列 $P$ 上の区間です。
$S_i$ は permutation tree の $i$ 番目の頂点が join node なら "join" 、cut node なら "cut" です。

@{lang.end}

@{example.example_00}

@{example.example_01}

@{example.example_02}