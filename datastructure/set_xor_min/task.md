## @{keyword.statement}

@{lang.en}
Let $S$ be an empty integer set.
Process the following $Q$ queries :

 - `0 x` : insert $x$ into $S$ if it is not in $S$
 - `1 x` : remove $x$ from $S$ if it is in $S$
 - `2 x` : find $\min_{i \in S}(i \oplus x)$ where $\oplus$ denotes bitwise-xor.

@{lang.ja}
空の整数集合 $S$ があります。 以下の$Q$ 個のクエリを処理してください。

 - `0 x` : $S$ に $x$ を追加する。ただし既に $S$ に $x$ が存在する場合何もしない。
 - `1 x` : $S$ から $x$ を削除する。ただし $S$ に $x$ が存在しない場合何もしない。
 - `2 x` : $\min_{i \in S}(i \oplus x)$ を出力する。($\oplus$ は bitwise-xor)
@{lang.end}

## @{keyword.constraints}
@{lang.en}

 - $1 \leq Q \leq @{param.MAX_Q}$
 - $0 \le x \lt 2^{30}$
 - $S$ is not empty when processing queries of type `2 x`.

@{lang.ja}

 - $1 \leq Q \leq @{param.MAX_Q}$
 - $0 \le x \lt 2^{30}$
 - `2 x`形式のクエリが来る時点で $S$ は空でない

@{lang.end}

## @{keyword.input}

```
$Q$
$\mathrm{Query}_0$
$\mathrm{Query}_1$
$\mathrm{Query}_2$
$\hspace{15pt} \vdots$
$\mathrm{Query}_{Q - 1}$
```

## @{keyword.sample}

@{example.example_00}

