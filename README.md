# Library Checker Problems

![CI](https://github.com/yosupo06/library-checker-problems/workflows/CI/badge.svg)
[![Gitter](https://badges.gitter.im/library-checker-problems/community.svg)](https://gitter.im/library-checker-problems/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Source code of [https://judge.yosupo.jp](https://judge.yosupo.jp)

このリポジトリのコードを動かすことで、問題のテストケースを手元に生成することができます。

## Requirements

- Linux / OS X / Windows(MinGW64)
- python3.5+
- g++ / clang++ (--std=c++14, __int128_tが使える必要あり)

### (需要と余力があれば)対応予定

- MSVC++
- __int128_tの除去

## How to Use

```sh
cd /path/to/library-checker-problems

pip3 install -r requirements.txt
# or pip3 install toml colorlog markdown jinja2

ulimit -s unlimited # for linux (doesn't need for OS X and WSL)

./generate.py -p unionfind # generate testcases of unionfind
# or ./generate.py datastructure/unionfind/info.toml
ls datastructure/unionfind/in/ # testcases of unionfind
ls datastructure/unionfind/out/ # solutions of unionfind
file datastructure/unionfind/checker # binary of output checker
```

### For developer

```
./generate.py -p unionfind --dev # developer mode
./generate.py -p unionfind --test # test mode (for developer, run this before pull request)
cat datastructure/unionfind/unionfind.html # statement

./generate.py $(find . -name "info.toml" -not -path "./test/*") # generate all testcases
```

## ローカルでのテスト

手元でジャッジをしたい場合, [online-judge-tools](https://github.com/kmyk/online-judge-tools) がサポートしてくれています

また、CIに組み込みたい場合は

- [How to run CI on your library for competitive programming (Japanese)](https://online-judge-tools.readthedocs.io/en/master/run-ci-on-your-library.ja.html) (同じく [online-judge-tools](https://github.com/kmyk/online-judge-tools)) が役に立つでしょう。実際にCIに組み込む例として、[library-checker-ci-example](https://github.com/yosupo06/library-checker-ci-example) を用意しています
- 簡単にCIに組み込むためのスクリプトとして [online-judge-verify-helper](https://github.com/kmyk/online-judge-verify-helper) が開発されています

## Contributing(バグ報告などしていただける方へ)

不具合(テストケースが弱い, ジャッジが異常な挙動をする, 問題文にtypoを発見, などなど)を発見したとき、報告していただけるととっても助かります。
問題の追加要望などもなんでも歓迎です。

- issueを立てる(推奨): githubにはissueというTODOやバグなどをメモっておく機能があります。上の Issues → New issueから作成できます。
- pull requestを送る(推奨): 実際に自分でコードを変更していただける場合、[CONTRIBUTING](docs/CONTRIBUTING.md) を参考にしていただけるととても助かります(熱意がある人向け)
- [gitter](https://gitter.im/library-checker-problems/community) というチャットみたいなものを用意しています。ここに書き込んでくれても大丈夫です
- [twitter](https://twitter.com/yosupot) に直接 リプライ / DM でも大丈夫です

競プロerは必ずしもgithubに慣れているとは限らず、issue / pull request を送ったことがない人も少なくはないというのを理解しています。どれだけめちゃくちゃなものを送ってきても怒ったりこのリポジトリが壊れたりすることはないので、githubの練習がてら挑戦してみるというのもアリです(頑張ってサポートします)。

## フォルダ構成

各種コンフィグファイルの仕様などは、[guideline](docs/guideline.md) にまとまっています

## library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

## Thanks

checker, validatorなどに [testlib](https://github.com/MikeMirzayanov/testlib) を使用しています。
