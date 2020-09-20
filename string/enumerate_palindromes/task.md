## @{keyword.statement}

@{lang.en}

Given a length $N$ string $S$ .

There are $2N-1$ ways to decide the center of the palindromes in $S$ : characters and middles of two continuous characters.

Define $L_i$ as the length of the maximum palindrome which center is the $i$-th (If the palindrome does not exist, $L_i=0$ ) . Calculate array $L_0,L_1,...,L_{2N-2}$ .

@{lang.ja}

長さ $N$ の文字列 $S$ が与えられます。

$S$ に含まれる回文の中心として考えられる位置は文字、文字と文字の間の $2N-1$ 通りあります。
 
それぞれ左から $i+1$ 番目を位置 $i$ とするとき、文字列中で位置 $i$ を中心とする最長の回文の長さ $L_i$ を出力してください。(存在しない場合は $L_i=0$ とします)

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq N \leq 500,000$
- Each character of $S$ is lowercase English letters.

@{lang.ja}

- $1 \leq N \leq 500,000$
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
