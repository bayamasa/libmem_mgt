# libmem_mgt

C言語のmallocで確保したメモリを管理してくれるツールです。<br>
これを使えば**100%メモリリークが起きません！**

# 機能

- mallocで確保したメモリの情報を記憶＆表示
- プログラム終了時にメモリリークの検出＆未解放のメモリを解放
- プログラムの任意のタイミングで未解放のメモリの検出
- プログラムの任意のタイミングで未解放のメモリを解放
- 指定したサイズよりも多くメモリを確保した場合にエラー終了
- メモリの確保上限を超えた場合にエラー終了

# 使い方

1. リポジトリをgit clone

	作業ディレクトリ内にリポジトリをcloneします。
	```
	git clone https://github.com/kiri-42/libmem_mgt.git
	```
1. makeの実行

	cloneしたディレクトリに移動し、makeコマンドを実行します。
	```
	cd libmem_mgt
	make
	```
1. ヘッダーファイルをインクルード

	管理したいプログラムにmem_mgt.hとreplace_mem_mgt.hをインクルードします。
	```
	#include "libmem_mgt/mem_mgt.h"
	#include "libmem_mgt/replace_mem_mgt.h"
	```
1. mem_mgt_init()を呼び出し

	main関数の最初の行にmem_mgt_init();を追記します。<br>
	特定の行でメモリ未開放領域を確認したいときは、その行にmem_mgt_check();を追記してください。<br>
	特定の行でメモリ未開放領域をfreeしたいときは、その行にmem_mgt_free_all();を追記してください。
1. コンパイルして実行

	2.で作成したlibmem_mgt.aを含めてコンパイルして実行すればメモリリークの情報を標準出力に検出してくれます。

# 注意事項

プログラムはexitで終了してください。<br>
main関数のreturn終了やCtrl + Cには対応していません。
