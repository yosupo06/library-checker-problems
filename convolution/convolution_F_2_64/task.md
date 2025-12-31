## @{keyword.statement}

@{lang.en}
Given sequences $a_0, a_1, ..., a_{N - 1}$ and $b_0, b_1, ..., b_{M - 1}$ of elements of $\mathbb{F} _ {2^{64}}$. Calculate a sequence $c_0, c_1, ..., c_{(N - 1) + (M - 1)}$ of elements of $\mathbb{F} _ {2^{64}}$ as follows:

$$c_k = \sum_{i+j=k} a_ib_j$$


Let $P(x) = x^{64} + x^4 + x^3 + x + 1 \in \mathbb{Z}_2[x]$ be an irreducible polynomial over $\mathbb{Z}_2$ of degree $64$.
$\mathbb{F} _ {2^{64}}$ is constructed as quotient ring $\mathbb{Z}_2[x] / (P(x))$.
Elements of $\mathbb{F} _ {2^{64}}$ can be uniquely represented by their remainders modulo $P(x)$.

Polynomials over $\mathbb{Z}_2[x]$ of degree less than 64 can be naturally identified with unsigned 64-bit integers: the $i$-th bit in the corresponding number is set if and only if the monomial $x^i$ is present in the polynomial.
This integer representation is used for input and output in this problem.

@{lang.ja}

$\mathbb{F} _ {2^{64}}$ の元からなる列 $a_0, a_1, ..., a_{N - 1}$ 、 $b_0, b_1, ..., b_{M - 1}$ が与えられます。 $\mathbb{F} _ {2^{64}}$ の元からなる列 $c_0, c_1, ..., c_{(N - 1) + (M - 1)}$ を計算してください。

ただし、

$$c_k = \sum_{i+j=k} a_ib_j$$

です。

$P(x) = x^{64} + x^4 + x^3 + x + 1 \in \mathbb{Z} _ 2[x]$ とします。これは次数 $64$ の $\mathbb{Z}_2$ 上の既約多項式です。
本問題において $\mathbb{F} _ {2^{64}}$ は、剰余環 $\mathbb{Z} _ 2[x] / (P(x))$ として構成されます。
$\mathbb{F} _ {2^{64}}$ の元は、$P(x)$ による剰余として一意に表現できます。

次数が $64$ 未満の $\mathbb{Z}_2[x]$ 上の多項式は、符号なし 64 ビット整数と自然に同一視できます。
対応する整数の $i$ 番目のビットは、その多項式に項 $x^i$ が含まれている場合に、かつその場合に限り立っているとします。
この整数表現が、本問題の入力および出力に用いられます。


@{lang.end}

## @{keyword.constraints}

- $1 \leq N, M \leq @{param.N_AND_M_MAX}$
- $0 \leq a_i, b_i < 2^{64}$

## @{keyword.input}

```
$N$ $M$
$a_0$ $a_1$ ... $a_{N-1}$
$b_0$ $b_1$ ... $b_{M-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{(N - 1) + (M - 1)}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}


## Note

The `_mm_clmulepi64_si128` intrinsic may be helpful.