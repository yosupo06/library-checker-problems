## @{keyword.statement}

@{lang.en}

You are given a sequence $A = (a_0, a_1, \dots, a _ {N-1})$ of distinct integers.
Construct the Cartesian tree derived from this sequence $A$.
The smallest element becomes the root.

@{lang.ja}
長さ $N$ の distinct な数列 $A = (a_0, a_1, \dots, a _ {N-1})$ が与えられる。
この数列 $A$ から誘導される Cartesian tree を求めよ。
ただし、最も小さい要素が根である。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.A_MIN} \leq a_i \leq @{param.A_MAX}$
- $i \ne j$ implies $a_i \ne a_j$
- all values are integers

## @{keyword.input}

~~~
$N$
$a_0$ $a_1$ ... $a _ {N - 1}$
~~~

## @{keyword.output}

~~~
$p_0$ $p_1$ $p_2$ ... $p_{N - 1}$
~~~

@{lang.en}
$p_i$ is the parent of vertex $i$. $p_r = r$ for the root node $r$ of the tree.
@{lang.ja}
$p_i$ は頂点 $i$ の親である。また、根である頂点 $r$ については $p_r = r$ とすること。
@{lang.end}


## @{keyword.sample}

@{example.example_00}

@{example.example_01}
