## @{keyword.statement}

@{lang.en}

You are given a string $S$ of length $N$.

There are $2N-1$ positions for the center of a palindromic substring of $S$: at the character or at the middle of two adjacent characters.

For the $i$-th of them ($0$-based), define $L_i$ as the length of the maximum palindrome centered there (or $L_i = 0$ if such a palindrome does not exist). Calculate the array $L_0,L_1,\ldots,L_{2N-2}$.

@{lang.ja}

長さ $N$ の文字列 $S$ が与えられます。

$S$ に含まれる回文の中心として考えられる位置は文字、文字と文字の間の $2N-1$ 通りあります。
 
それぞれ左から $i+1$ 番目を位置 $i$ とするとき、文字列中で位置 $i$ を中心とする最長の回文の長さ $L_i$ を出力してください。(存在しない場合は $L_i=0$ とします)

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq N \leq @{param.N_MAX}$
- Each character of $S$ is a lowercase English letter.

@{lang.ja}

- $1 \leq N \leq @{param.N_MAX}$
- $S$ は英小文字からなる。

@{lang.end}

## @{keyword.input}

```
$S$
```

## @{keyword.output}

```
$L_0$ $L_1$ ... $L_{2N-2}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
