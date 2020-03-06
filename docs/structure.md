# 各種仕様

## 問題ごとのファイル構造

問題ごとのディレクトリは、以下のような構造になっている

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
  - in/ デフォルトでは存在しない、生成された入力ファイルが入る
    - example_00.in
    - random_00.in
    - ...
  - out/ デフォルトでは存在しない、生成された出力ファイルが入る
    - example_00.out

### aplusb/info.toml

問題の様々な情報が入る

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

- `timelimit`: 時間制限(秒)
- `[[tests]]`: それぞれが1つのテストケースジェネレーターに対応する
  - `name`: ファイル名　拡張子が`.in`のものは生ファイルに対応する
  - `number`: このジェネレーターから生成するケース数
- `[[solutions]]`: それぞれが1つの解答ファイルに対応する
  - `name`: ファイル名
  - `wrong`: WAが想定かどうか 指定しない場合もあり、false(=正しい解答)として扱う
  - `allow_tle`: TLEを許可するかどうか これを指定してTLEしなくても許される
- `[params]`: 各種定数、この情報は自動的に`params.h`に出力される
  - `task.md`からは`{{param A_AND_B_MAX}}`のように使う
  - 想定解(`correct.cpp`)からは使わない

### aplusb/sol/correct.cpp

- 想定解
- ~~aplusb/correct.cpp への移動を検討中~~
- `params.h`などは使わず、「そのままジャッジに提出してACが取れる」コードになっている

### aplusb/verifier.cpp

- input checker(入力ファイルが制約を満たしているか確認する)
- [https://codeforces.com/blog/entry/18426](https://codeforces.com/blog/entry/18426) に従って書かれている

### aplusb/gen/example_0*.in

- サンプルファイル
- 名前は`example_00.in, example_01.in, example_02.in, ...`であることを仮定していい

### aplusb/gen/random.cpp(など)

- テストケースジェネレーター
- 引数にケース番号を取る `./random 3` -> random_03.in
- 環境依存性はない(=どの環境で動かしても同じケースが出てくる)ことを仮定していい

### aplusb/checker.cpp

- output checker(ユーザーの出力が条件を満たしているか確認する)
- [https://codeforces.com/blog/entry/18431](https://codeforces.com/blog/entry/18431) に従って書かれている

### aplusb/hash.json

```json
{
  "example_00.in": "346a847f5875beb74d494de0680a81fc2ff840b12f79de30dc7ef3a798d23c28",
  "example_00.out": "d6e0da7b83d84fac4d6a6bd11ad0b0e6ea72351748b4f6a277b9762d9d0eb159",
  "example_01.in": "0073cf03577a737756752129cc3abcb9f5a4069c705321ee2115574cc31c59f9",
  "example_01.out": "6f2264250160ee91b20af64f30128e3787fcf641f1c504f7ac752597e7d2cc09"
}
```

- 上記のようなjsonファイル
- テストケース名とそのテストケースのsha256が格納されている
