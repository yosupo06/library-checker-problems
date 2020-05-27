## @{keyword.statement}

$N$ 頂点の木があります。辺は $(a_i, b_i)$ です。各 $i = 1, 2, \cdots, N - 1$ について、$\mathrm{dist}(u, v) = i$ となる頂点対 $u, v (u < v)$ の個数 $x_i$ を求めてください。

$\mathrm{dist}(u, v)$ は頂点 $u, v$ をつなぐパスの辺数です。

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $a_i \neq b_i$

## @{keyword.input}

```
$N$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{N-2}$ $b_{N-2}$
```

## @{keyword.output}

```
$x_1$ $x_2$ $\ldots$ $x_{N-1}$
```

## @{keyword.sample}

@{example.example_00}
