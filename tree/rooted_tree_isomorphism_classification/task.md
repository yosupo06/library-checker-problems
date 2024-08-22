## @{keyword.statement}

@{lang.en}

Given a rooted tree with $N$ vertices. The root of tree is the vertex $0$ . A parent of the vertex $i$ is $p _ i$ . You will get $N$ rooted subtrees by choosing a root. Classify them by isomorphism of rooted trees.

Now print a number of distinct subtrees $K$ and an integer seqence $a _ 0 , a _ 1 , \ldots , a _ {N-1}$ that satisfy the following conditions.

- $0 \leq a _ i \lt K$
- $a _ i = a _ j$ if and only if the $2$ subtrees whose roots are $i$ and $j$ are isomorphic.

@{lang.ja}

$N$ 頂点の根付き木が与えられる。根は頂点 $0$ である。頂点 $i$ の親は $p _ i$ である。ある頂点を根とする部分木（全部で $N$ 個）について、根付き木の同型性で分類せよ。

このとき部分木の種類数 $K$ と、次の条件を満たす整数列 $a _ 0 , a _ 1 , \ldots , a _ {N-1}$ を出力せよ。

- $0 \leq a _ i \lt K$
- 頂点 $i$ , $j$ をそれぞれ根とする部分木が同型であるならば、またその時に限り $a _ i = a _ j$ 。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq p _ i \lt i$

## @{keyword.input}

~~~
$N$
$p _ 1$ $p _ 2$ $\ldots$ $p _ {N-1}$
~~~

## @{keyword.output}

~~~
$K$
$a _ 0$ $a _ 1$ $\ldots$ $a _ {N-1}$
~~~


@{lang.en}
If there are multiple solutions, print any of them.
@{lang.ja}
正しい出力が複数存在する場合は、どれを出力しても構わない。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
