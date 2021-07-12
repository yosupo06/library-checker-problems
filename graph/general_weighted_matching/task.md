## @{keyword.statement}

@{lang.en}

Given a simple weighted undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(u_i, v_i)$ with a weight $w_i$.
Calculate the matching in which the sum of weights is maximized.

@{lang.ja}
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 500$
- $0 \leq M \leq \frac{N(N-1)}{2}$
- $0 \leq u_i, v_i < N$
- $1 \leq w_i \leq 1\,000\,000$

## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$ $w_0$
$u_1$ $v_1$ $w_1$
:
$u_{M - 1}$ $v_{M - 1}$ $w_{M-1}$
~~~

## @{keyword.output}

~~~
$X$ $W$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{X - 1}$ $b_{X - 1}$
~~~

@{lang.en}

$X$ is the size of the maximum matching.
$W$ is the maximum matching weight.

@{lang.ja}

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
