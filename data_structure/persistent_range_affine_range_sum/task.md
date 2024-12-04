## @{keyword.statement}

@{lang.en}
Given a size $N$ interger sequence $a _ 0, a _ 1, \dots, a _ {N - 1}$.
Let $A _ {-1}$ be the sequence $(a _ 0, a _ 1, \dots, a _ {N - 1})$.

Process $Q$ queries as follows:

- `0 $k _ i$ $l _ i$ $r _ i$ $b _ i$ $c _ i$`: Make a copy of $A _ {k _ i}$ as $A _ i$ . For each $j = l, l+1, \dots, {r - 1}$ , on $A _ i$ , $a _ j \gets b _ i \times a _ j + c _ i$.
- `1 $k _ i$ $s _ i$ $l _ i$ $r _ i$`: Make a copy of $A _ {k _ i}$ as $A _ i$ . For each $j = l, l+1, \dots, {r - 1}$ , on $A _ i$ , $a _ j \gets a ^ {\prime} _ j$ (where $a ^ {\prime} _ j$ is the value of $a _ j$ in $A _ {s _ i}$ ).
- `2 $k _ i$ $l _ i$ $r _ i$`: Print $\sum_{j = l} ^ {r - 1} a _ j \bmod @{param.MOD}$ from $A _ {k _ i}$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられます。
$A _ {-1}$ を数列 $(a _ 0, a _ 1, \dots, a _ {N - 1})$ とします.

$Q$ 個のクエリが飛んできます。処理してください。

- `0 $k _ i$ $l _ i$ $r _ i$ $b _ i$ $c _ i$`: $A _ {k _ i}$ を複製して $A _ i$ とします。 $A _ i$ において、 各 $j = l, l+1, \dots, {r - 1}$ について、$a _ j \gets b \times a _ j + c$ 。
- `1 $k _ i$ $s _ i$ $l _ i$ $r _ i$`: $A _ {k _ i}$ を複製して $A _ i$ とします。 $A _ i$ において、 各 $j = l, l+1, \dots, {r - 1}$ について、$a _ j \gets a ^ {\prime} _ j$ (ここで、 $a ^ {\prime} _ j$ は $A _ {s _ i}$ における $a _ j$ とする) 。
- `2 $l _ i$ $r _ i$`: $A _ {k _ i}$ における $\sum_{j = l} ^ {r - 1} a _ j \bmod @{param.MOD}$ を出力してください。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a _ i \lt @{param.MOD}$
- $1 \leq b _ i \lt @{param.MOD}$
- $0 \leq c _ i \lt @{param.MOD}$
- $-1 \leq k _ i \lt i$
- for all $k _ i$, $k _ i = -1$ or $t _ {k _ i} \in \lbrace 0,1\rbrace$ holds.
- $0 \leq l _ i \lt r _ i \leq N$
@{lang.ja}
- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a _ i \lt @{param.MOD}$
- $1 \leq b _ i \lt @{param.MOD}$
- $0 \leq c _ i \lt @{param.MOD}$
- $-1 \leq k _ i \lt i$
- すべての $k _ i$ について、 $k _ i = -1$ または $t _ {k _ i} \in \lbrace 0,1\rbrace$ が成り立つ。
- $0 \leq l _ i \lt r _ i \leq N$
@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$a _ 0$ $a _ 1$ ... $a _ {N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}

@{example.example_01}
