## @{keyword.statement}

@{lang.en}

You are given :

* a rooted tree of $N$ vertices ,
* $N$ integers $c _ 0 , c _ 1 , \dots , c _ {N-1}$ and
* $N$ integers $d _ 0 , d _ 1 , \dots , d _ {N-1}$.

The root of the tree is the vertex $0$ , and the parent of the vertex $i$ is $p _ i$ .

Find one permutation $p$ of $(0,1,\dots ,N-1)$ which satisfies following condition. If there are multiple candidates, you can choose any of them.

* If the vertex $p _ i$ is an ancestor of the vertex $p _ j$, $i \lt j$ holds.
* Among one that satisfies the condition above, the value $X=\sum _ {i=0} ^ {N-1} \sum _ {j=0} ^ {i-1} c _ i d _ j$ is minimized.

Output the minimum value of $X$ and a possible permutation $p$ with the value $X$ is minimized.

@{lang.ja}

* $N$ 頂点の根付き木、
* $N$ 個の整数 $c _ 0 , c _ 1 , \dots , c _ {N-1}$
* $N$ 個の整数 $d _ 0 , d _ 1 , \dots , d _ {N-1}$

が与えられます。
根付き木の根は頂点 $0$ で、頂点 $i$ の親は $p _ i$ です。

以下の条件を満たす $(0,1,\dots ,N-1)$ の順列 p を $1$ つ求めてください。複数ある場合はそのうちのどれでも構いません。

* 頂点 $p _ i$ が頂点 $p _ j$ の祖先ならば、 $i\lt j$ .
* 上記の条件を満たす中で、 $X=\sum _ {i=0} ^ {N-1} \sum _ {j=0} ^ {i-1} c _ i d _ j$ の最小値をとる。

$X$ の最小値と、 $X$ が最小化されるときの順列 $p$ としてありうるものを出力してください。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $0 \leq p _ i \lt i$
- $@{param.C_MIN} \leq c _ i \leq @{param.C_MAX}$
- $@{param.D_MIN} \leq d _ i \leq @{param.D_MAX}$
- $\sum _ {i=0} ^ {N-1} c _ i \leq @{param.C_SUM_MAX}$
- $\sum _ {i=0} ^ {N-1} d _ i \leq @{param.D_SUM_MAX}$

## @{keyword.input}

~~~
$N$
$p _ 1$ $p _ 2$ ... $p _ {N-1}$
$c _ 0$ $c _ 1$ ... $c _ {N-1}$
$d _ 0$ $d _ 1$ ... $d _ {N-1}$
~~~

## @{keyword.output}

~~~
$X$
$p _ 0$ $p _ 1$ $\ldots$ $p _ {N-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
