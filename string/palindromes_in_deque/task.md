## @{keyword.statement}

@{lang.en}
There is an initially empty string $s$. Process $Q$ queries.

- `0 $c$`: Add a character $c$ to the beginning of the string $s$.
- `1 $c$`: Add a character $c$ to the end of the string $s$.
- `2`: Remove the character at the beginning of the string $s$.
- `3`: Remove the character at the end of the string $s$.

After processing each query, output the following $3$ parameters.

* Number of distinct palindromic substring of $s$
* Length of the longest palindromic prefix of $s$
* Length of the longest palindromic suffix of $s$

If $s$ is a empty string, output `0 0 0` instead.

@{lang.ja}
はじめ、空文字列 $s$ があります。$Q$ 個のクエリを処理してください。

- `0 $c$`: 文字列 $s$ の先頭に文字 $s$ を追加する
- `1 $c$`: 文字列 $s$ の末尾に文字 $s$ を追加する
- `2`: 文字列 $s$ の先頭の文字を削除する
- `3`: 文字列 $s$ の末尾の文字を削除する

各クエリを処理した後に、以下の $3$ つのパラメータを出力してください。

* $s$ の相異なる回文部分文字列の個数
* $s$ の最長の回文接頭辞の長さ
* $s$ の最長の回文接尾辞の長さ

$s$ が空文字列のときは、代わりに `0 0 0` を出力してください。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $c$ is a lowercase English letter.
- The string $s$ is not empty when query $2$ or query $3$ comes.

@{lang.ja}

- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $c$ は英小文字。
- クエリ $2$ またはクエリ $3$ が来るとき、文字列 $s$ は空ではない

@{lang.end}

## @{keyword.input}

```
$Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
