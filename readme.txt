////////////////////////////////////////////////////////////////////////////////////////////////////

                                           Vapor  ver1.02                                          
               
////////////////////////////////////////////////////////////////////////////////////////////////////

■概要
VaporはWindows向けゲームランチャーです。複数のゲームを紹介文や画像とともに登録することが出来ます。

同梱内容
-Vapor.exe(ランチャー本体)
-GameSetting.exe
-vaopr.config
-Gameフォルダ
-Iconフォルダ
-Thumbnailフォルダ
-Source.zip(開発者向け)


■インストール・アンインストール方法
zipを解凍するだけで使用できます。
削除したいときはフォルダごと削除してください。


■使い方
ゲームの設定をした後、Vapor.exeを起動してください。


■設定方法
GameSetting.exeを起動してください。

新規作成、修正、削除、どれもGameSetting.exeを閉じたときに内容が反映されます。

 □新規作成
   左のリストボックスから<新規作成>を選んだまま、右の各ボックスに情報を入力し、
   「追加」ボタンを押してください。

   -タイトル
    ゲームのタイトルを入力してください。
   -ジャンル
    ゲームのジャンルを入力してください
   -説明文
    遊びたくなるような説明文を入力してください。目安として、16〜99文字の文章が良いです。
   -バージョン
    ゲームのバージョンを入力してください。
   -作業フォルダ
    ゲームの実行ファイル(.exe)が存在するディレクトリを入力してください。
    Vapor\Gameフォルダ内に存在しない場合正しく起動できません。
    「参照」ボタンから参照することも出来ます。
   -exeファイルパス
    ゲームの実行ファイル(.exe)のパスを入力してください。
    「参照」ボタンから参照することも出来ます。
   -アイコンファイル
    ゲームの紹介に使うアイコン画像を入力してください。
    Vapor\Iconフォルダ内に存在しない場合正しく表示できません。
    「参照」ボタンから参照することも出来ます。
   -サムネイルファイル
    ゲームの紹介に使うサムネイル画像を入力してください。
    Vapor\Thumbnailフォルダ内に存在しない場合正しく表示できません。
    「参照」ボタンから参照することも出来ます。
    
 □修正
   左のリストボックスから内容を修正したいゲームを選択し、右のボックスの内容を変更してください。
   その後、「修正」ボタンを押すことで内容が修正されます。
   
 □削除
   左のリストボックスから内容を修正したいゲームを選択し、「削除」ボタンを押すと登録から削除されます。
   
   
※推奨されるアイコン画像は「サイズ200*100、"bmp","png","jpg"」です。
※推奨されるサムネイル画像は「サイズ320*240、"bmp","png","jpg"」です。

■更新履歴
2017/11/23 ver1.02
保守用にソースコードの調整

2017/11/18 ver1.01
アイコン画像にサムネ画像が設定されるバグを修正

2017/11/18 ver1.00 (t152910C,t152951A 共同製作)
 第69回峰ヶ丘祭にて公開


////////////////////////////////////////////////////////////////////////////////////////////////////

                                          開発者向け  情報                                          

////////////////////////////////////////////////////////////////////////////////////////////////////

■ソースコード
ソースコードをSource.Zipに同梱しています。

-Form1.cs(Vapor本体)
-Form1.Designer.cs(Vapor本体のデザイン)
-GameDetailForm.cs(ゲームの詳細情報を表示するサブウィンドウ)
-GameDetailForm.Designer(サブウィンドウのデザイン)
-Program.cs(エントリポイントを含む共通部分の記述)
-SetteingForm.cs(設定アプリケーション)
-SetteingForm.Designer.cs(設定アプリケーションのデザイン)


■開発環境
OS:Windows7, 8.1
言語:C#(.NET Framework 4.6.1)
IDE:VisualStudio2015 Community


■定義済み情報
program.cs内、General::Defineクラスにて定義しています。
ウィンドウサイズや文字列のフォントなどの情報を定義しています。

アプリケーションの情報は\Properties\AssemblyInfo.cs内に定義されています。


■作成者
(初版)
t152910C 井上
t152951A 谷口

2017/9より製作開始
2017/11/18 ver1.00公開





