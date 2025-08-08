## @{keyword.statement}

@{lang.en}
There is an initially empty sequence of integer sequence $a=()$. Process $Q$ queries.

- `0 $x$`: Add an integer $x$ to the beginning of the sequence $a$.
- `1 $x$`: Add an integer $x$ to the end of the sequence $a$.
- `2`: Remove the integer at the beginning of the sequence $a$.
- `3`: Remove the integer at the end of the sequence $a$.
- `4 $i$`: Let $a = (a_0, \ldots, a_{n-1})$ at this time. Output $a_i$. 

@{lang.ja}
長さ $0$ の整数列 $a = ()$ があります．$Q$ 個のクエリが飛んできます．処理してください．

- `0 $x$`: 列 $a$ の先頭に整数 $x$ を追加する．
- `1 $x$`: 列 $a$ の末尾に整数 $x$ を追加する．
- `2`: 列 $a$ の先頭の整数を削除する
- `3`: 列 $a$ の末尾の整数を削除する
- `4 $i$`: この時点で $a = (a_0, \ldots, a_{n-1})$ であるとして，$a_i$ を出力する．
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $@{param.MIN_Q} \leq Q \leq @{param.MAX_Q}$
- $@{param.MIN_X} \leq x \leq @{param.MAX_X}$
- The sequence $a$ is not empty when query $2$ or query $3$ or query $4$ comes.
- $0\leq i < |a|$ holds when query $4$ comes.
@{lang.ja}
- $@{param.MIN_Q} \leq Q \leq @{param.MAX_Q}$
- $@{param.MIN_X} \leq x \lt @{param.MAX_X}$
- クエリ $2$ またはクエリ $3$ またはクエリ $4$ が来るとき，列 $a$ は空ではない．
- クエリ $4$ において $0\leq i<|a|$ が成り立つ．
@{lang.end}

## @{keyword.input}

~~~
$Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
