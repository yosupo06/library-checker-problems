# 問題の作り方

問題ごとに1つのフォルダが対応します。パスは`library-checker-problems/{ジャンル}/{問題ID}`で、例えば`sample/aplusb`や`datastructure/unionfind`などです。

自分で問題を準備する場合は問題ID(例: `unionfind`) は既に決まっているはずです。ジャンルは重要なものではないので、それっぽいところに適当に入れてください。

## 問題ごとのファイル構造

問題ごとのフォルダは、以下のような構造になっています。

- aplusb/
  - info.toml 問題の情報
  - checker.cpp 出力チェッカー
  - verifier.cpp 入力チェッカー
  - hash.json 入出力ファイルのハッシュ
  - (params.h 定数が格納されたファイル, 自動生成)
  - sol/
    - correct.cpp 想定解
    - wa.cpp
    - ...
  - gen/
    - example_00.in サンプル
    - random.cpp
    - ...
  - (in/) デフォルトでは存在しない、生成された入力ファイルが入る
    - example_00.in
    - random_00.in
    - ...
  - (out/) デフォルトでは存在しない、生成された出力ファイルが入る
    - example_00.out

準備する必要があるものは以下の物です。

- フォルダの作成
- info.toml
- task.md(問題文)
- sol/correct.cpp(想定解)
- verifier.cpp(input checker)
- checker.cpp(output checker)
- gen/example_00.in, gen/example_01.in, gen/random.cppなど(テストケースジェネレーター)

### info.toml

問題の様々な情報が入ってます。[toml](https://github.com/toml-lang/toml)についてはフィーリングでもなんとかなると思います。

```toml
timelimit = 2.0

[[tests]]
    name = "example.in"
    number = 2
[[tests]]
    name = "random.cpp"
    number = 10

[[solutions]]
    name = "wa.cpp"
    wrong = true

[params]
    A_AND_B_MAX = 1_000_000_000
```

- `timelimit`: 時間制限(秒) aplusbは2secですが大体5secです
- `[[tests]]`: それぞれが1つのテストケースジェネレーターに対応する
  - `name`: ファイル名　拡張子が`.in`のものは生ファイルに対応する
  - `number`: このジェネレーターから生成するケース数
- `[[solutions]]`: それぞれが1つの解答ファイルに対応する
  - `name`: ファイル名
  - `wrong`: WAが想定かどうか 指定しない場合もあり、false(=正しい解答)として扱う
  - `allow_tle`: TLEを許可するかどうか これを指定してTLEしなくても許される
- `[params]`: 各種定数、この情報は自動的に`params.h`に出力される
  - `task.md`からは`@{param.A_AND_B_MAX}`のように使う

## task.md(問題文)

markdown + mathjax形式です。他のtask.mdをコピペして弄ればいいと思います。
伝わればいいので、細かいところは気にしないで大丈夫です。

いくつか拡張されています

- @{lang.en}, @{lang.ja}, @{lang.end} : このブロックで囲んだところは対応する言語にしか見えなくなります
- @{example.example_00} : `gen/example_00.in`を埋め込みます
- @{param.A_AND_B_MAX} : info.tomlで指定した`[params]`を埋め込みます

## sol/correct.cpp(想定解)

想定解です。

普通の競プロと全く同じように、標準入力から受け取って標準出力に書くのを書けば大丈夫です。

コーディング規約は以下です。守らないとCI(pull requestを送った時に走る自動テスト)で割と落ちます。

- 言語はC++
- 普段使いのテンプレートとかはOK、でも使ってないテンプレートが100行貼ってあるとかはやめてほしい
- `cin / cout`ではなく`scanf / printf`を使う(高速入出力ライブラリも可、`cin / cout + ios::... + cin.tie` は macOS で非常に低速になるので不可)
- 警告を無視しない
- `params.h`など、外部のファイルを(std以外)使わない
- 環境依存性がない(=Windows, mac, linux全てで同じように動く) これはCIがチェックするのでそれを見ればいいです
  - `bits/stdc++.h`を使わない
  - 環境依存性があるものを使わない: `rand()`, `uniform_int_distribution`, `shuffle`, ...
    - `sort`は同じ大きさの物の順序が未定義だが、それらの物の順序で出力が変わらないか(特に構築)

## verifier.cpp(input checker)

入力が、制約を満たしているかを確認するコードです。
[https://codeforces.com/blog/entry/18426](https://codeforces.com/blog/entry/18426) や、他の様々な問題の`verifier.cpp`が参考になると思います。よっぽど変な制約じゃ無い場合そんなに難しくないと思います。

- windowsの改行コードの都合で `readEoln()` ではなく `readChar('\n')` を使う 

## checker.cpp(output checker)

参加者の出力が、条件を満たしているか判定するコードです。

ジャッジ内容が完全一致の場合、`library-checker-problems/sample/aplusb/checker.cpp` をコピーするだけで終わりです。

スペシャルジャッジの場合は大変です。[https://codeforces.com/blog/entry/18431](https://codeforces.com/blog/entry/18431) を参考に書いてください。

- `%lld`はquitfでは使えないです
  - `quitf(_wa, "long long value(%lld)", x)`は`quitf(_wa, "long long value(" I64 ")", x)`としてください


## gen/example_00.in, gen/example_01.in, gen/random.cppなど(ジェネレーター)

テストケースです。[テストケースの作り方](generator.md)を参考にすると追加できます。

- example_00.in は欲しい(サンプルは1個は欲しい)
- random.cpp という名前でランダムケースが3個ぐらい欲しい
- 後は適当に(テストケースはどんどん追加していく想定なんで、弱くていいです)
- 最初の段階なら嘘解法はいらないです

あたりが注意点です

## 実際に動かす

準備が無事にできたら、手元で動かしてみることができます。

```sh
./generate.py sample/aplusb/info.toml --dev
```

### hash.json(自動生成)

```json
{
  "example_00.in": "346a847f5875beb74d494de0680a81fc2ff840b12f79de30dc7ef3a798d23c28",
  "example_00.out": "d6e0da7b83d84fac4d6a6bd11ad0b0e6ea72351748b4f6a277b9762d9d0eb159",
  "example_01.in": "0073cf03577a737756752129cc3abcb9f5a4069c705321ee2115574cc31c59f9",
  "example_01.out": "6f2264250160ee91b20af64f30128e3787fcf641f1c504f7ac752597e7d2cc09"
}
```

無事動かせると上記のようなファイルが生まれているはずです。テストケースのハッシュ(sha256)が保存されていて、これもcommitする必要があります(CIでもテストケースを作って、ハッシュがpushされたものと一致してるか確認する)。
