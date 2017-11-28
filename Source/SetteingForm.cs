////////////////////////////////////////////////////////////////
//                     ver1.02 2017/11/23                     //
////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using General;

namespace SettingForms
{ 
    public partial class SettingForm : Form
    {
        private List<GameInfo> GameList = new List<GameInfo>();

        // コンストラクタ
        public SettingForm()
        {
            InitializeComponent();

            // GameListの取得
            var XmlCtl = new General.XmlRegister("vapor.config");
            
            // ListBoxの先頭は新規作成
            GameList.Add(new GameInfo("<新規作成>","","","","","","",""));

            // 以降にGameListを追加
            GameList.AddRange(XmlCtl.ReadXml());

            // ListBoxにGameListを設定
            GameListBox.DataSource = GameList;
            GameListBox.DisplayMember = ("Title");
            GameListBox.SetSelected(0, true);

            // Visual Studioの自動コード生成がクソなせいでダイアログのプロパティに
            // インスタンスのプロパティが結び付けられないのでここで追加
            OpenFolderDialog.SelectedPath = Application.StartupPath;
            OpenExeFileDialog.InitialDirectory = Application.StartupPath;
            OpenPicFileDialog.InitialDirectory = Application.StartupPath;

            // Visual Studioの自動コード生成がクソなせいで複数のイベントを
            // コントロールに結び付けられないのでここで追加
            // 注意：Xmlへの保存は全てのイベントの最後となるようにすること
            ListAddButton.Click += new System.EventHandler(GameListBox_SelectedIndexChanged);

            ListAddButton.Click += new System.EventHandler(UpdataXml);
            ListDelButton.Click += new System.EventHandler(UpdataXml);
            ListUpdateButton.Click += new System.EventHandler(UpdataXml);
        }

        // フォルダの参照イベント
        private void FolderRefButton_Click(object sender, EventArgs e)
        {
            DialogResult dr = OpenFolderDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                FolderText.Text = GetRelPath(OpenFolderDialog.SelectedPath,@"\Game\");

            }
        }

        // 実行ファイルの参照イベント
        private void ExeRefButton_Click(object sender, EventArgs e)
        {
            DialogResult dr = OpenExeFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ExeText.Text = GetRelPath(OpenExeFileDialog.FileName, @"\Game");
            }
        }

        // サムネイルの参照イベント
        private void ThumbRefButton_Click(object sender, EventArgs e)
        {
            DialogResult dr = OpenPicFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ThumbnailText.Text = GetRelPath(OpenPicFileDialog.FileName, @"\Thumbnail");
            }
        }

        // アイコンの参照イベント
        private void IconRefButton_Click(object sender, EventArgs e)
        {
            DialogResult dr = OpenPicFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                IconText.Text = GetRelPath(OpenPicFileDialog.FileName, @"\Icon");
            }

        }

        // 与えられた絶対パスをvapor.exeからの相対パスに変換
        // absPath:絶対パス
        private string GetRelPath(string absPath)
        {
            // vapor.exeのフォルダを取得
            string appPath = Application.StartupPath;
            
            Uri u1 = new Uri(appPath);
            Uri u2 = new Uri(absPath);

            //絶対Uriから相対Uriを取得する
            Uri relativeUri = u1.MakeRelativeUri(u2);

            //文字列に変換する
            string relativePath = relativeUri.ToString();

            //"/"を"\"に変換する
            relativePath = relativePath.Replace('/', '\\');

            return relativePath;
        }

        // 与えられた絶対パスをvapor.exeのフォルダ以下のaddPathからのフォルダからの相対パスに変換
        // absPath:絶対パス
        // addPath:vapor.exe以下のフォルダパス
        private string GetRelPath(string absPath, string addPath)
        {
            // vapor.exeのフォルダを取得
            string appPath = Application.StartupPath;

            Uri u1 = new Uri(appPath + addPath);
            Uri u2 = new Uri(absPath);

            //絶対Uriから相対Uriを取得する
            Uri relativeUri = u1.MakeRelativeUri(u2);

            //文字列に変換する
            string relativePath = relativeUri.ToString();

            //"/"を"\"に変換する
            relativePath = relativePath.Replace('/', '\\');

            return relativePath;
        }

        // ListBoxが選択および更新された時のイベント
        private void GameListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            // 新規作成なら追加ボタンを起動
            if (GameListBox.SelectedIndex == 0) {
                ListDelButton.Enabled = false;
                ListAddButton.Enabled = true;
                ListUpdateButton.Enabled = false;
            }
            // それ以外なら削除と修正ボタンを起動
            else
            {
                ListDelButton.Enabled = true;
                ListAddButton.Enabled = false;
                ListUpdateButton.Enabled = true;
            }

            // 選択中のGameInfoからテキストボックスに内容を反映
            GameInfo SelectedGameInfo = (GameInfo)GameListBox.SelectedItem;

            if (GameListBox.SelectedIndex == 0) TitleText.Text = "";
            else TitleText.Text = SelectedGameInfo.Title;
            GenreText.Text = SelectedGameInfo.Genre;
            InfoText.Text = SelectedGameInfo.Info;
            FolderText.Text = SelectedGameInfo.Folder;
            ExeText.Text = SelectedGameInfo.ExeName;
            ThumbnailText.Text = SelectedGameInfo.Thumbnail;
            IconText.Text = SelectedGameInfo.Icon;
            VerText.Text = SelectedGameInfo.Version;
        }

        // 追加ボタンが押された時のイベント
        // TODO: 必要項目の入力確認
        private void ListAddButton_Click(object sender, EventArgs e)
        {
            // 入力された項目からGameInfoを作成
            GameInfo NewGameInfo = new GameInfo(TitleText.Text, GenreText.Text, InfoText.Text,
                ThumbnailText.Text, FolderText.Text, ExeText.Text, IconText.Text, VerText.Text);
            // Listに加える
            GameList.Add(NewGameInfo);
            // 更新のため新しくListを作成
            List<GameInfo> tempGameList = new List<GameInfo>(GameList);
            GameListBox.DataSource = tempGameList;

        }

        // 削除ボタンが押された時のイベント
        // TODO: 確認画面の表示
        private void ListDelButton_Click(object sender, EventArgs e)
        {
            // 選択された項目を削除
            GameList.RemoveAt(GameListBox.SelectedIndex);
            // 更新のため新しくListを作成
            List<GameInfo> tempGameList = new List<GameInfo>(GameList);
            GameListBox.DataSource = tempGameList;
        }

        // 修正ボタンが押された時のイベント
        private void ListUpdateButton_Click(object sender, EventArgs e)
        {
            // 入力された項目からGameInfoを作成
            GameInfo NewGameInfo = new GameInfo(TitleText.Text, GenreText.Text, InfoText.Text,
                ThumbnailText.Text, FolderText.Text, ExeText.Text, IconText.Text, VerText.Text);
            // 参照で書き換え
            GameList[GameListBox.SelectedIndex] = NewGameInfo;
            // 修正後に選択位置が変わらないよう値を保存
            int selectedNum = GameListBox.SelectedIndex;
            // 更新のため新しくListを作成
            List<GameInfo> tempGameList = new List<GameInfo>(GameList);
            GameListBox.DataSource = tempGameList;
            GameListBox.SelectedIndex = selectedNum;
        }

        // GameInfoに変更があった場合Xmlファイルへ保存するイベント
        private void UpdataXml(object sender, EventArgs e)
        {
            var XmlCtl = new XmlRegister("vapor.config");
            // 先頭の<新規作成>は保存しない
            XmlCtl.WriteXml(GameList.Skip(1).ToList());
        }

       
    }
}
