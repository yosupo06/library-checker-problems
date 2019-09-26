# 各種仕様

## problems.toml

ここに問題のリストが入っている。
中を見ると大体想像がつくと思うが

```toml
[problems.aplusb]
    title = 'A + B'
    dir = 'sample/aplusb'
```

が1問に対応する

- `problems.aplusb`
  - aplusbが問題のID
  - 問題IDは`[a-z_]+`であることを仮定していい
  - 変更しないと仮定していい(=問題IDの変更は破壊的変更として扱う)
- `title`
  - 問題のタイトル
  - 内容は変更しうる
  - 場所ももしかしたら問題ごとの設定ファイル(後述のinfo.toml)に移動するかもしれない
- `dir`
  - 問題データの場所
  - `sample/aplusb` -> `example/aplusb` のように変更しうるが、最後が問題IDと等しいことは仮定していい

## 問題ごとのファイル構造

problems.tomlのdirで指定されたディレクトリ以下は、以下のような構造になっている

- aplusb/
  - info.toml 問題の情報
  - checker.cpp 出力チェッカー
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

### info.toml

問題の様々な情報が入る

```toml
solution = "correct.cpp"
verify = "verify.cpp"
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
```

- `solution`: **廃止の可能性あり** 想定解の名前で、内容が `correct.cpp` であることを仮定していい
- `verify`: **廃止の可能性あり** input checkerの名前で、内容が `verify.cpp` であることを仮定していい
- `timelimit`: 時間制限(秒)
- `[[tests]]`: それぞれが1つのテストケースジェネレーターに対応する
  - `name`: ファイル名　拡張子が`.in`のものは生ファイルに対応する
  - `number`: このジェネレーターから生成するケース数
- `[[solutions]]`: それぞれが1つの解答ファイルに対応する
  - `name`: ファイル名
  - `wrong`: WAが想定かどうか 指定しない場合もあり、false(=正しい解答)として扱う
- `task.md`: 問題文

### sol/correct.cpp

- 想定解
- aplusb/correct.cpp への移動を検討中

### gen/verify.cpp

- input checker(入力ファイルが制約を満たしているか確認する)
- [https://codeforces.com/blog/entry/18426](https://codeforces.com/blog/entry/18426) に従って書かれている
- aplusb/verify.cpp への移動を検討中

### gen/example_0*.in

- サンプルファイル
- 名前は`example_00.in, example_01.in, example_02.in, ...`であることを仮定していい

### gen/random.cpp(など)

- テストケースジェネレーター
- 引数にケース番号を取る `./random 3` -> random_03.in
- 環境依存性はない(=どの環境で動かしても同じケースが出てくる)ことを仮定していい

### checker.cpp

- output checker(ユーザーの出力が条件を満たしているか確認する)
- [https://codeforces.com/blog/entry/18431](https://codeforces.com/blog/entry/18431) に従って書かれている
