## @{keyword.statement}

@{lang.en}
There is an initially empty sequence of linear functions $f = ()$. Process $Q$ queries.

- `0 $a$ $b$`: Add a linear function $\lambda x. ax + b$ to the beginning of the sequence $f$.
- `1 $a$ $b$`: Add a linear function $\lambda x. ax + b$ to the end of the sequence $f$.
- `2`: Remove the linear function at the beginning of the sequence $f$.
- `3`: Remove the linear function at the end of the sequence $f$.
- `4 $x$`: Let $f = (f_{l}, \dots, f_{r - 1})$, output $f _ {r - 1}(f _ {r - 2}(\dots (f _ l(x)) \dots)) \bmod 998244353$. Output $x$ if $f = ()$.
@{lang.ja}
長さ $0$ (一次)関数の列 $f = ()$ があります。$Q$ 個のクエリが飛んできます。処理してください。

- `0 $a$ $b$`: 列 $f$ の先頭に一次関数 $\lambda x. ax + b$ を追加する
- `1 $a$ $b$`: 列 $f$ の末尾に一次関数 $\lambda x. ax + b$ を追加する
- `2`: 列 $f$ の先頭の一次関数を削除する
- `3`: 列 $f$ の末尾の一次関数を削除する
- `4 $x$`: $f = (f_{l}, \dots, f_{r - 1})$ として $f _ {r - 1}(f _ {r - 2}(\dots (f _ l(x)) \dots)) \bmod 998244353$ を出力する。$f = ()$ の場合は $x$
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq Q \leq 500,000$
- $1 \leq a \lt 998244353$
- $0 \leq b, x \lt 998244353$
- The sequence $f$ is not empty when query $2$ or query $3$ comes.
@{lang.ja}
- $1 \leq Q \leq 500,000$
- $1 \leq a \lt 998244353$
- $0 \leq b, x \lt 998244353$
- クエリ $2$ またはクエリ $3$ が来るとき、列 $f$ は空ではない
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

@{example.example_01}
