## @{keyword.statement}

@{lang.en}
Find a basis of the intersection of two $\mathbb{F} _ 2$-vector spaces $X, Y$. Specifically, find a set of vectors $B = \{w_0, \ldots, w_{k-1}\}$ that is:
- linearly independent (for any subset $S = \{s_0, \ldots, s_{l-1}\}\subseteq B$, $s_0 \oplus \cdots \oplus s_{l-1} = 0$ implies $S = \emptyset$.)
- spans $X \cap Y$ (for any $a \in X \cap Y$, there exists a subset $S = \{s_0, \ldots, s_{l-1}\} \subseteq B$ such that $s_0 \oplus \cdots \oplus s_{l-1} = a$ holds.)

Each test consists of $T$ cases.

@{lang.ja}

xor に関する $\mathbb{F} _ 2$ ベクトル空間 $X, Y$ の共通部分の基底を一組出力してください。つまり、ベクトルの集合 $B = \{w_0, \ldots, w_{k-1}\}$ であって以下を満たすものを見つけてください:
- 線型独立である (任意の $S = \{s_0, \ldots, s_{l-1}\}\subseteq B$ に対して, $s_0 \oplus \cdots \oplus s_{l-1} = 0$ であれば $S = \emptyset$ である。)
- $X \cap Y$ を張る (任意の $a \in X \cap Y$ に対して、 ある部分集合 $S = \{s_0, \ldots, s_{l-1}\} \subseteq B$ が存在して、 $s_0 \oplus \cdots \oplus s_{l-1} = a$ が成立する。)

この問題は $T$ ケースあります。

@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq @{param.T_MAX}$
- $1 \leq n, m \leq @{param.NM_MAX}$
- $0 \leq u_i, v_i \leq @{param.XY_MAX}$

## @{keyword.input}

```
$T$
$n$ $u_0$ $u_1$ $\cdots$ $u_{n - 1}$
$m$ $v_0$ $v_1$ $\cdots$ $v_{m - 1}$
$:$
$n$ $u_0$ $u_1$ $\cdots$ $u_{n - 1}$
$m$ $v_0$ $v_1$ $\cdots$ $v_{m - 1}$
```

## @{keyword.output}

```
$k$ $w_0$ $w_1$ $\cdots$ $w_{k - 1}$
$:$
$k$ $w_0$ $w_1$ $\cdots$ $w_{k - 1}$
```

## @{keyword.sample}

@{example.example_00}
