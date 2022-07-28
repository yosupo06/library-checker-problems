## @{keyword.statement}

@{lang.en}
Given $N \times M$ matrix $A$ and $M \times K$ matrix $B$, print $C = AB \bmod @{param.MOD}$.
@{lang.ja}
$N \times M$ 行列 $A$ と $M \times K$ 行列 $B$ が与えられます。 $C = A B \bmod @{param.MOD}$を求めてください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N,M,K \leq @{param.N_MAX}$
- $0 \leq a_{ij},b_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N\ M\ K$
$a_{11}$ $a_{12}$ ... $a_{1M}$
$a_{21}$ $a_{22}$ ... $a_{2M}$
:
$a_{N1}$ $a_{N2}$ ... $a_{NM}$
$b_{11}$ $b_{12}$ ... $b_{1K}$
$b_{21}$ $b_{22}$ ... $b_{2K}$
:
$b_{M1}$ $b_{M2}$ ... $b_{MK}$
```

## @{keyword.output}
```
$c_{11}$ $c_{12}$ ... $c_{1K}$
$c_{21}$ $c_{22}$ ... $c_{2K}$
:
$c_{N1}$ $c_{N2}$ ... $c_{NK}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
