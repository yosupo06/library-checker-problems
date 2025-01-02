## @{keyword.statement}

@{lang.en}
Given a size $N$ interger sequence $a _ 0, a _ 1, \dots, a _ {N - 1}$.
Let $A _ {-1}$ be the sequence $(a _ 0, a _ 1, \dots, a _ {N - 1})$.

For $i=0,1,\ldots ,Q-1$ , process a query as follows:

- `0 $k$ $l$ $r$ $b$ $c$`: Make a copy of $A _ {k}$ as $A _ i$ . For each $j = l, l+1, \dots, {r - 1}$ , on $A _ i$ , $a _ j \gets b \times a _ j + c$.
- `1 $k$ $s$ $l$ $r$`: Make a copy of $A _ {k}$ as $A _ i$ . For each $j = l, l+1, \dots, {r - 1}$ , on $A _ i$ , $a _ j \gets a ^ {\prime} _ j$ (where $a ^ {\prime} _ j$ is the value of $a _ j$ in $A _ {s}$ ).
- `2 $k$ $l$ $r$`: Print $\sum_{j = l} ^ {r - 1} a _ j \bmod @{param.MOD}$ from $A _ {k}$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられます。
$A _ {-1}$ を数列 $(a _ 0, a _ 1, \dots, a _ {N - 1})$ とします.

$i=0,1,\ldots ,Q-1$ についてクエリを処理してください。

- `0 $k$ $l$ $r$ $b$ $c$`: $A _ {k}$ を複製して $A _ i$ とします。 $A _ i$ において、 各 $j = l, l+1, \dots, {r - 1}$ について、$a _ j \gets b \times a _ j + c$ 。
- `1 $k$ $s$ $l$ $r$`: $A _ {k}$ を複製して $A _ i$ とします。 $A _ i$ において、 各 $j = l, l+1, \dots, {r - 1}$ について、$a _ j \gets a ^ {\prime} _ j$ (ここで、 $a ^ {\prime} _ j$ は $A _ {s}$ における $a _ j$ とする) 。
- `2 $k$ $l$ $r$`: $A _ {k}$ における $\sum_{j = l} ^ {r - 1} a _ j \bmod @{param.MOD}$ を出力してください。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
Let $t _ i$ as the type of the $i$-th query ($0\leq i \lt Q$ , $t _ i\in\lbrace 0,1,2\rbrace$) .

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a \lt @{param.MOD}$
- $1 \leq b \lt @{param.MOD}$
- $0 \leq c \lt @{param.MOD}$
- $-1 \leq k \lt i$
- $k=-1$ or $t _ k\in \lbrace 0,1\rbrace$
- $-1 \leq s \lt i$
- $s=-1$ or $t _ s\in \lbrace 0,1\rbrace$
- $0 \leq l \lt r \leq N$
@{lang.ja}
$t _ i$ を、 $i$ 番目のクエリの種類とします ($0\leq i \lt Q$ , $t _ i\in\lbrace 0,1,2\rbrace$)。

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a \lt @{param.MOD}$
- $1 \leq b \lt @{param.MOD}$
- $0 \leq c \lt @{param.MOD}$
- $-1 \leq k \lt i$
- $k=-1$ または $t _ k\in \lbrace 0,1\rbrace$
- $-1 \leq s \lt i$
- $s=-1$ または $t _ s\in \lbrace 0,1\rbrace$
- $0 \leq l \lt r \leq N$
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
