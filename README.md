# nidonehsp

`nidonehsp` は ポータブルでクリーンな実装を目指したスクリプト言語です。

文法や基本的な挙動は [HSP3](https://hsp.tv/index2.html) から強く影響を受けていますが、次のよう特徴があります。

- ポータブル
  - 外部依存ライブラリが少なく、開発のための追加インストールが少ないです
  - C99 に則って実装されており、多様な環境でのコンパイルが可能です
    - ※ただし、プラットフォームに依存するAPIを使用してはいるので、WindowsAPIやPOSIXなどのAPIが必要です
- クリーン
  - nidonehsp 本体のソースコードはフルスクラッチで、ライセンスの問題がありません
  - 組み込みライブラリも基本的には PublicDomain またはそれに準ずるもののみを使用しています
  - 外部依存ライブラリもバイナリ化した際のライセンスが非常に緩いもの（ライセンス表記の必要がない等）を採用しています
- 開発環境
  - [VSCode](https://code.visualstudio.com/) 用の拡張機能も本体と同時に開発されており、VSCode上でのスムーズな開発が可能です

なお、実質 [neteruhsp](https://github.com/exrd/neteruhsp) の後継にも当たります。

<img src="./n2hspTopDemo.gif" width="640">

# ドキュメント

- [クイックリファレンス](./doc/quickReference.md)
  - nidonehsp の文法や基本的な仕様について説明しています。
  - HSP3 との違いについても触れられています。
- [開発環境](./doc/developEnvironment.md)
  - nidonehsp での実際のスクリプト実行の流れを説明しています。
  - 特に VSCode と連携した操作について触れています。

# デモ

- テスト用[demoスクリプト](test_world/demo)のHTML出力したもの
  - [HTML](https://exrd.github.io/nidonehsp/demos/n2demo/n2r_std.html)

# ディレクトリ構成とライセンス

nidonehsp 本体は NYSL でライセンスされます。

|ディレクトリ|内容|ライセンス|
|:--|:--|:--|
|`build`|nidonehsp 自身のビルド時に必要なリソースが格納されます|NYSL|
|`doc`|ドキュメントファイルが格納されます|NYSL|
|`external`|外部依存ライブラリが格納されます|各ライブラリのライセンスに従います|
|`nidonehsp/*` および<br>`nidonehsp/inline/*`|nidonehsp 本体と付随するサブコード|NYSL|
|`nidonehsp/embed/*`|組み込みライブラリのソースコード|各ファイル内のライセンス記述に従います|
|`src`|コマンドラインツールやユニットテストのコード|NYSL|
|`test_world`|テストコード|NYSL|
|`vscode_extension`|nidonehsp 用のVSCode拡張|NYSL|
|`./*`|CMake 用のファイルなど|NYSL|

nidonehsp のライセンス全文は `LICENSE` ファイルを参照してください。
