////////////////////////////////////////////////////////////////
//                     ver1.02 2017/11/23                     //
////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MainForms
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }


    }
}

namespace General
{
    public class GameInfo
    {
        public static string appPath = Application.StartupPath;

        // TODO: 空白の禁止などの処理
        public string Title { get; set; }
        public string Genre { get; set; }
        public string Info { get; set; }
        public string Thumbnail { get; set; }
        public string Folder { get; set; }
        public string ExeName { get; set; }
        public string Icon { get; set; }
        public string Version { get; set; }

        public GameInfo() { }
        public GameInfo(string title, string genre, string info, string thumbnail, string folder, string exeName, string icon, string version)
        {
            Title = title;
            Genre = genre;
            Info = info;
            Thumbnail = thumbnail;
            Folder = folder;
            ExeName = exeName;
            Icon = icon;
            Version = version;
        }

    }


    // Xmlファイルの操作を行うクラス
    public class XmlRegister
    {
        // configファイルパス
        private string _fname;

        // コンストラクタ
        // fname:ファイルパス
        public XmlRegister(string fname) { _fname = fname; }

        // configファイルからGameInfoを読み込む
        // 戻り値:読み込み先
        // TODO: ファイルが無い場合の初期動作
        public List<GameInfo> ReadXml()
        {
            System.Xml.Serialization.XmlSerializer serializer2 =
            new System.Xml.Serialization.XmlSerializer(typeof(List<GameInfo>));

            // ファイルが存在している場合
            if (System.IO.File.Exists(_fname))
            {
                // usingによって確実にファイルクローズを行う
                using (System.IO.StreamReader sr = new System.IO.StreamReader(
                _fname, new System.Text.UTF8Encoding(false)))
                {
                    // GameInfoを復元
                    return (List<GameInfo>)serializer2.Deserialize(sr);
                }
            }

            // 存在しない場合nullを返却
            return null;
        }

        // configファイルにGameInfoを保存
        // gameList:保存するリスト
        public void WriteXml(List<GameInfo> gameList)
        {
            System.Xml.Serialization.XmlSerializer serializer1 =
            new System.Xml.Serialization.XmlSerializer(typeof(List<GameInfo>));

            // usingによって確実にファイルクローズを行う
            using (System.IO.StreamWriter sw = new System.IO.StreamWriter(
                _fname, false, new System.Text.UTF8Encoding(false)))
            {
                //GameInfoを保存
                serializer1.Serialize(sw, gameList);
            }

        }
    }
    
    static class Define
    {
        public const int BUTTON_WIDTH = 700;
        public const int BUTTON_HEIGHT = 100;
        public const int BUTTON_FIRST_X = 34;
        public const int BUTTON_FIRST_Y = 60;
        public const int BUTTON_MARGIN_X = 0;
        public const int BUTTON_MARGIN_Y = 106;

        public const int PICBOX_WIDTH = 200;
        public const int PICBOX_HEIGHT = 100;
        public const int PICBOX_FIRST_X = 34;
        public const int PICBOX_FIRST_Y = 60;
        public const int PICBOX_MARGIN_X = 0;
        public const int PICBOX_MARGIN_Y = 106;

        public const int PREVIOUS_WIDTH = 468;
        public const int PREVIOUS_HEIGHT = 50;
        public const int PREVIOUS_X = 150;
        public const int PREVIOUS_Y = 5;

        public const int NEXT_WIDTH = 468;
        public const int NEXT_HEIGHT = 50;
        public const int NEXT_X = 150;
        public const int NEXT_Y = 377;

        public const int TITLE_WIDTH = 400;
        public const int TITLE_HEIGHT = 40;
        public const int TITLE_FIRST_X = 261;
        public const int TITLE_FIRST_Y = 60;
        public const int TITLE_MARGIN_X = 0;
        public const int TITLE_MARGIN_Y = 106;
        public const string TITLE_FONT = "Meiryo UI";

        public const int KANKYO_WIDTH = 24;
        public const int KANKYO_HEIGHT = 24;
        public const int KANKYO_FIRST_X = 261;
        public const int KANKYO_FIRST_Y = 100;
        public const int KANKYO_MARGIN_X = 0;
        public const int KANKYO_MARGIN_Y = 106;

        public const int GENRE_WIDTH = 400;
        public const int GENRE_HEIGHT = 36;
        public const int GENRE_FIRST_X = 261;
        public const int GENRE_FIRST_Y = 124;
        public const int GENRE_MARGIN_X = 0;
        public const int GENRE_MARGIN_Y = 106;
        public const string GENRE_FONT = "Meiryo UI";

        public const int VER_WIDTH = 80;
        public const int VER_HEIGHT = 100;
        public const int VER_FIRST_X = 659;
        public const int VER_FIRST_Y = 60;
        public const int VER_MARGIN_X = 0;
        public const int VER_MARGIN_Y = 106;
        public const string VER_FONT = "Meiryo UI";

        //色情報
        public const int FORM_TOP_COLOR_R = 50;
        public const int FORM_TOP_COLOR_G = 80;
        public const int FORM_TOP_COLOR_B = 105;
        public const int FORM_BUTTOM_COLOR_R = 30;
        public const int FORM_BUTTOM_COLOR_G = 52;
        public const int FORM_BUTTOM_COLOR_B = 66;

        public const int BUTTON_LEAVE_COLOR_R = 32;
        public const int BUTTON_LEAVE_COLOR_G = 54;
        public const int BUTTON_LEAVE_COLOR_B = 71;
        public const int BUTTON_HOVER_COLOR_R = 179;
        public const int BUTTON_HOVER_COLOR_G = 214;
        public const int BUTTON_HOVER_COLOR_B = 234;

        public const int GAME_NUM_IN_PAGE = 3;
    }


}