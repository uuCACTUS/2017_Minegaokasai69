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
using static General.Define;
using System.Diagnostics;
using SettingForms;
using System.Drawing.Drawing2D;

namespace MainForms
{
    public partial class Form1 : Form
    {
        private List<GameInfo> gl = new List<GameInfo>();
        private GameDetailForm gdform;
        private int page = 1;
        private int maxPage = 1;

        private List<System.Windows.Forms.Button> game = new List<System.Windows.Forms.Button>();
        private List<System.Windows.Forms.PictureBox> pictureBox = new List<System.Windows.Forms.PictureBox>();
        private List<System.Windows.Forms.PictureBox> kankyo = new List<System.Windows.Forms.PictureBox>();
        private List<System.Windows.Forms.Label> title = new List<System.Windows.Forms.Label>();
        private List<System.Windows.Forms.Label> genre = new List<System.Windows.Forms.Label>();
        private List<System.Windows.Forms.Label> ver = new List<System.Windows.Forms.Label>();
        private System.Windows.Forms.Button previous;
        private System.Windows.Forms.Button next;

        public Form1()
        {
            InitializeComponent();

            this.AutoScaleMode = AutoScaleMode.None;
            this.MouseDown += Form1_MouseDown;
            this.MouseMove += Form1_MouseMove;
            Bitmap icon = (Bitmap)Image.FromFile(GameInfo.appPath + "\\Icon\\vapor.png");
            this.pictureBox1.BackgroundImage = icon;

            XmlRegister xmlctl = new XmlRegister(GameInfo.appPath + "\\vapor.config");
            gl.AddRange(xmlctl.ReadXml());

            maxPage = gl.Count / GAME_NUM_IN_PAGE;
            if (gl.Count % GAME_NUM_IN_PAGE > 0) maxPage++;

            prepareUI();
            drawColor();
            UpdateScreen();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.ClientSize = new System.Drawing.Size(768, 432);
            this.AutoScaleMode = AutoScaleMode.None;
        }

        // 画像・文の配置
        private void UpdateScreen()
        {
            for(int i = 0; i < game.Count; i++)
            {
                // アイコンの表示
                Bitmap icon = (Bitmap)Image.FromFile(GameInfo.appPath + @"\" + gl[i + ((page - 1) * GAME_NUM_IN_PAGE)].Icon);
                pictureBox[i].BackgroundImage = icon;

                // タイトルの表示
                title[i].Text = gl[i + ((page - 1) * GAME_NUM_IN_PAGE)].Title;

                // WINアイコンの表示
                icon = (Bitmap)Image.FromFile(GameInfo.appPath + @"\Icon\Windows.png");
                kankyo[i].BackgroundImage = icon;

                // フォントとサイズ要調整
                genre[i].Text = gl[i + ((page - 1) * GAME_NUM_IN_PAGE)].Genre;

                // バージョン
                ver[i].Text = gl[i + ((page - 1) * GAME_NUM_IN_PAGE)].Version;

                // tabの更新
                game[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
                title[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
                pictureBox[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
                genre[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
                ver[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
                kankyo[i].TabIndex = i + ((page - 1) * GAME_NUM_IN_PAGE);
            }

            
        }

        

        private void left(object sender, EventArgs e)
        {
            if (--page < 1) page = 1;

            prepareUI();
            drawColor();
            UpdateScreen();
        }

        private void right(object sender, EventArgs e)
        {
            if (++page > maxPage) page = maxPage;

            prepareUI();
            drawColor();
            UpdateScreen();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            SettingForm setform = new SettingForm();
            setform.Show();
        }

        private void button1_Click(object sender, EventArgs e) => GameStart((page-1) * GAME_NUM_IN_PAGE);

        private void game2_Click(object sender, EventArgs e) => GameStart((page - 1) * GAME_NUM_IN_PAGE + 1);

        private void game3_Click(object sender, EventArgs e) => GameStart((page-1) * GAME_NUM_IN_PAGE + 2);

        private void mouseHoverLabel(object sender, EventArgs e)
        {
            Label l;
            l = (Label)sender;
            gdform = new GameDetailForm(this, gl[l.TabIndex]);
            gdform.Show();
        }

        private void mouseHoverPictureBox(object sender, EventArgs e)
        {
            PictureBox p;
            p = (PictureBox)sender;
            gdform = new GameDetailForm(this, gl[p.TabIndex]);
            gdform.Show();
        }

        private void mouseHoverButton(object sender, EventArgs e)
        {
            Button b;
            b = (Button)sender;
            gdform = new GameDetailForm(this, gl[b.TabIndex]);
            gdform.Show();
        }
        private void mouseLeave(object sender, EventArgs e)
        {
            if (gdform != null)
                gdform.Close();
        }
        private void buttonEnterGame1(object sender, EventArgs e)
        {
            game[0].GetType().InvokeMember("OnMouseEnter",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[0],
            new object[] { EventArgs.Empty });
        }
        private void buttonEnterGame2(object sender, EventArgs e)
        {
            game[1].GetType().InvokeMember("OnMouseEnter",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[1],
            new object[] { EventArgs.Empty });
        }
        private void buttonEnterGame3(object sender, EventArgs e)
        {
            game[2].GetType().InvokeMember("OnMouseEnter",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[2],
            new object[] { EventArgs.Empty });
        }
        private void buttoLeaveGame1(object sender, EventArgs e)
        {
            game[0].GetType().InvokeMember("OnMouseLeave",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[0],
            new object[] { EventArgs.Empty });
        }
        private void buttoLeaveGame2(object sender, EventArgs e)
        {
            game[1].GetType().InvokeMember("OnMouseLeave",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[1],
            new object[] { EventArgs.Empty });
        }
        private void buttoLeaveGame3(object sender, EventArgs e)
        {
            game[2].GetType().InvokeMember("OnMouseLeave",
            System.Reflection.BindingFlags.InvokeMethod |
            System.Reflection.BindingFlags.NonPublic |
            System.Reflection.BindingFlags.Instance,
            null,
            game[2],
            new object[] { EventArgs.Empty });
        }
        private void drawColor()
        {
            // フォームの背景
            Bitmap canvas = new Bitmap(this.Width, this.Height);
            Graphics g = Graphics.FromImage(canvas);
            LinearGradientBrush gb = new LinearGradientBrush(
                g.VisibleClipBounds,
                Color.FromArgb(FORM_TOP_COLOR_R, FORM_TOP_COLOR_G, FORM_TOP_COLOR_B),
                Color.FromArgb(FORM_BUTTOM_COLOR_R, FORM_BUTTOM_COLOR_G, FORM_BUTTOM_COLOR_B),
                LinearGradientMode.Vertical);
            g.FillRectangle(gb, g.VisibleClipBounds);

            this.BackgroundImage = canvas;

            foreach (var obj in game)
            {
                obj.BackColor = Color.FromArgb(BUTTON_LEAVE_COLOR_R, BUTTON_LEAVE_COLOR_G, BUTTON_LEAVE_COLOR_B);
                obj.FlatStyle = FlatStyle.Flat;
                obj.FlatAppearance.BorderColor = Color.FromArgb(BUTTON_LEAVE_COLOR_R, BUTTON_LEAVE_COLOR_G, BUTTON_LEAVE_COLOR_B);
            }

            gb.Dispose();
            g.Dispose();

            if(next != null) next.BackColor = Color.FromArgb(BUTTON_LEAVE_COLOR_R, BUTTON_LEAVE_COLOR_G, BUTTON_LEAVE_COLOR_B);
            if (previous != null) previous.BackColor = Color.FromArgb(BUTTON_LEAVE_COLOR_R, BUTTON_LEAVE_COLOR_G, BUTTON_LEAVE_COLOR_B);

            close.BackColor = Color.FromArgb(BUTTON_LEAVE_COLOR_R, BUTTON_LEAVE_COLOR_G, BUTTON_LEAVE_COLOR_B);
        }

        // コントロールの配置
        private void prepareUI()
        {
            // 初期化
            foreach (var obj in this.game)  if(obj != null) obj.Dispose();
            foreach (var obj in this.pictureBox) if(obj != null) obj.Dispose();
            foreach (var obj in this.title) if (obj != null) obj.Dispose();
            foreach (var obj in this.kankyo) if (obj != null) obj.Dispose();
            foreach (var obj in this.genre) if (obj != null) obj.Dispose();
            foreach (var obj in this.ver) if (obj != null) obj.Dispose();
            this.game.Clear();
            this.pictureBox.Clear();
            this.title.Clear();
            this.kankyo.Clear();
            this.genre.Clear();
            this.ver.Clear();
            if (this.previous != null) this.previous.Dispose();
            if (this.next != null) this.next.Dispose();


            // ページ内の表示数を計算
            int gameNum = gl.Count - ((page-1) * GAME_NUM_IN_PAGE);
            if (gameNum > 3) gameNum = 3;

            // ボタンとアイコンの表示
            for (int i = 0; i < gameNum; i++)
            {

                this.game.Add(new System.Windows.Forms.Button());
                this.pictureBox.Add(new System.Windows.Forms.PictureBox());
                this.title.Add(new System.Windows.Forms.Label());
                this.genre.Add(new System.Windows.Forms.Label());
                this.kankyo.Add(new System.Windows.Forms.PictureBox());
                this.ver.Add(new System.Windows.Forms.Label());

                // ボタン
                this.game[i].Location = 
                    new System.Drawing.Point(BUTTON_FIRST_X + (i * BUTTON_MARGIN_X), BUTTON_FIRST_Y + (i * BUTTON_MARGIN_Y));
                this.game[i].Name = $"game{i+1}";
                this.game[i].Size = new System.Drawing.Size(BUTTON_WIDTH, BUTTON_HEIGHT);
                this.game[i].TabIndex = i;
                this.game[i].TabStop = false;
                this.game[i].UseVisualStyleBackColor = true;
                
                // アイコン
                ((System.ComponentModel.ISupportInitialize)(this.pictureBox[i])).BeginInit();
                this.pictureBox[i].Location = 
                    new System.Drawing.Point(PICBOX_FIRST_X + (i * PICBOX_MARGIN_X), PICBOX_FIRST_Y + (i * PICBOX_MARGIN_Y));
                this.pictureBox[i].Name = $"pictureBox{i+1}";
                this.pictureBox[i].Size = new System.Drawing.Size(PICBOX_WIDTH, PICBOX_HEIGHT);
                this.pictureBox[i].TabIndex = i;
                this.pictureBox[i].TabStop = false;
                ((System.ComponentModel.ISupportInitialize)(this.pictureBox[i])).EndInit();

                //タイトル
                this.title[i].BackColor = Color.Transparent;//FromArgb(Define.BUTTON_LEAVE_COLOR_R, Define.BUTTON_LEAVE_COLOR_G, Define.BUTTON_LEAVE_COLOR_B);
                this.title[i].Font = new System.Drawing.Font(TITLE_FONT, 14F);
                this.title[i].ForeColor = System.Drawing.Color.White;
                this.title[i].Location =
                    new System.Drawing.Point(TITLE_FIRST_X + (i * TITLE_MARGIN_X), TITLE_FIRST_Y + (i * TITLE_MARGIN_Y));
                this.title[i].Margin = new System.Windows.Forms.Padding(0);
                this.title[i].Name = $"title{i + 1}"; 
                this.title[i].Size = new System.Drawing.Size(TITLE_WIDTH, TITLE_HEIGHT);
                this.title[i].TabIndex = i;　//ゲームインデックス
                this.title[i].TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
                this.title[i].TabStop = false;  

                //ジャンル
                this.genre[i].BackColor = Color.Transparent;//FromArgb(Define.BUTTON_LEAVE_COLOR_R, Define.BUTTON_LEAVE_COLOR_G, Define.BUTTON_LEAVE_COLOR_B);
                this.genre[i].Font = new System.Drawing.Font(GENRE_FONT, 12F);
                this.genre[i].ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
                this.genre[i].Location =
                    new System.Drawing.Point(GENRE_FIRST_X + (i * GENRE_MARGIN_X), GENRE_FIRST_Y + (i * GENRE_MARGIN_Y));
                this.genre[i].Margin = new System.Windows.Forms.Padding(0);
                this.genre[i].Name = $"genre{i + 1}"; 
                this.genre[i].Size = new System.Drawing.Size(GENRE_WIDTH, GENRE_HEIGHT);
                this.genre[i].TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
                this.genre[i].TabIndex = i;
                this.genre[i].TabStop = false;

                //実行環境
                this.kankyo[i].Location =
                    new System.Drawing.Point(KANKYO_FIRST_X + (i * KANKYO_MARGIN_X), KANKYO_FIRST_Y + (i * KANKYO_MARGIN_Y));
                this.kankyo[i].BackColor = Color.Transparent;//FromArgb(Define.BUTTON_LEAVE_COLOR_R, Define.BUTTON_LEAVE_COLOR_G, Define.BUTTON_LEAVE_COLOR_B);
                this.kankyo[i].Name = $"kankyo{i + 1}";
                this.kankyo[i].Size = new System.Drawing.Size(KANKYO_WIDTH, KANKYO_HEIGHT);
                this.kankyo[i].TabStop = false;
                this.kankyo[i].TabIndex = i;
                this.kankyo[i].TabStop = false;

                //バージョン
                this.ver[i].BackColor = Color.Transparent;//FromArgb(Define.BUTTON_LEAVE_COLOR_R, Define.BUTTON_LEAVE_COLOR_G, Define.BUTTON_LEAVE_COLOR_B);
                this.ver[i].Font = new System.Drawing.Font(VER_FONT, 12F);
                this.ver[i].ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
                this.ver[i].Location =
                    new System.Drawing.Point(VER_FIRST_X + (i * VER_MARGIN_X), VER_FIRST_Y + (i * VER_MARGIN_Y));
                this.ver[i].Name = $"ver{i + 1}";
                this.ver[i].Size = new System.Drawing.Size(VER_WIDTH, VER_HEIGHT);
                this.ver[i].TabIndex = i;
                this.ver[i].TabStop = false;
                this.ver[i].Text = "lavel";
                this.ver[i].TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
                this.ver[i].Margin = new System.Windows.Forms.Padding(0);

                this.Controls.Add(this.pictureBox[i]);
                this.Controls.Add(this.game[i]);
                this.Controls.Add(this.kankyo[i]);
                
                ButtonAdd(game[i], title[i]);
                ButtonAdd(game[i], kankyo[i]);
                ButtonAdd(game[i], genre[i]);
                ButtonAdd(game[i], ver[i]);

            }

            // ボタンのイベント設定
            this.game[0].Click += new System.EventHandler(this.button1_Click);
            this.game[0].MouseHover += new EventHandler(mouseHoverButton);
            this.game[0].MouseLeave += new EventHandler(mouseLeave);
            if (this.game.Count > 1)
            {
                this.game[1].Click += new System.EventHandler(this.game2_Click);
                this.game[1].MouseHover += new EventHandler(mouseHoverButton);
                this.game[1].MouseLeave += new EventHandler(mouseLeave);
                if (this.game.Count > 2)
                {
                    this.game[2].Click += new System.EventHandler(this.game3_Click);
                    this.game[2].MouseHover += new EventHandler(mouseHoverButton);
                    this.game[2].MouseLeave += new EventHandler(mouseLeave);
                }
            }

            AddButtonEvent(title);
            AddButtonEvent(kankyo);
            AddButtonEvent(genre);
            AddButtonEvent(ver);

            // ページスクロールボタン         

            if (page != 1)
            {
                this.previous = new System.Windows.Forms.Button();
                this.previous.Location = new System.Drawing.Point(PREVIOUS_X, PREVIOUS_Y);
                //this.previous.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
                this.previous.Name = "button2";
                this.previous.Size = new System.Drawing.Size(PREVIOUS_WIDTH, PREVIOUS_HEIGHT);
                this.previous.TabIndex = 2;
                this.previous.Text = "↑";
                this.previous.UseVisualStyleBackColor = true;
                this.previous.Click += new System.EventHandler(this.left);
                this.previous.FlatStyle = FlatStyle.Flat;
                this.previous.ForeColor = Color.White;
                this.Controls.Add(this.previous);
            }

            if(page != maxPage)
            {
                this.next = new System.Windows.Forms.Button();
                this.next.Location = new System.Drawing.Point(NEXT_X, NEXT_Y);
                //this.next.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
                this.next.Name = "button3";
                this.next.Size = new System.Drawing.Size(NEXT_WIDTH, NEXT_HEIGHT);
                this.next.TabIndex = 3;
                this.next.Text = "↓";
                this.next.UseVisualStyleBackColor = true;
                this.next.Click += new System.EventHandler(this.right);
                this.next.FlatStyle = FlatStyle.Flat;
                this.next.ForeColor = Color.White;
                this.Controls.Add(this.next);
            }



        }

        private void GameStart(int index)
        {
            Process p = new Process();
            p.StartInfo.FileName = GameInfo.appPath + @"\" + gl[index].ExeName;
            p.StartInfo.WorkingDirectory = GameInfo.appPath + @"\Game\" + gl[index].Folder;
            try
            {
                p.Start();
            }
            catch(System.ComponentModel.Win32Exception)
            {
                return;
            }
           
        }

        private void close_Click(object sender, EventArgs e) => Application.Exit();

        private void ButtonAdd(Button b, Label l)
        {
            b.Controls.Add(l);
            l.Top = l.Top - b.Top;
            l.Left = l.Left - b.Left;
        }
        private void ButtonAdd(Button b, PictureBox p)
        {
            b.Controls.Add(p);
            p.Top = p.Top - b.Top;
            p.Left = p.Left - b.Left;
        }

        private void AddButtonEvent(List<System.Windows.Forms.Label> b)
        {
            b[0].Click += new System.EventHandler(this.button1_Click);
            b[0].MouseEnter += new System.EventHandler(this.buttonEnterGame1);
            b[0].MouseLeave += new System.EventHandler(this.buttoLeaveGame1);
            b[0].MouseHover += new EventHandler(mouseHoverLabel);
            b[0].MouseLeave += new EventHandler(mouseLeave);
            if (this.game.Count > 1)
            {
                
                b[1].Click += new System.EventHandler(this.game2_Click);
                b[1].MouseEnter += new System.EventHandler(this.buttonEnterGame2);
                b[1].MouseLeave += new System.EventHandler(this.buttoLeaveGame2);
                b[1].MouseHover += new EventHandler(mouseHoverLabel);
                b[1].MouseLeave += new EventHandler(mouseLeave);
                if (this.game.Count > 2)
                {
                    b[2].Click += new System.EventHandler(this.game3_Click);
                    b[2].MouseEnter += new System.EventHandler(this.buttonEnterGame3);
                    b[2].MouseLeave += new System.EventHandler(this.buttoLeaveGame3);
                    b[2].MouseHover += new EventHandler(mouseHoverLabel);
                    b[2].MouseLeave += new EventHandler(mouseLeave);
                }
            }
        }

        private void AddButtonEvent(List<System.Windows.Forms.PictureBox> p)
        {
            p[0].Click += new System.EventHandler(this.button1_Click);
            p[0].MouseEnter += new System.EventHandler(this.buttonEnterGame1);
            p[0].MouseLeave += new System.EventHandler(this.buttoLeaveGame1);
            p[0].MouseHover += new EventHandler(mouseHoverPictureBox);
            p[0].MouseLeave += new EventHandler(mouseLeave);
            if (this.game.Count > 1)
            {

                p[1].Click += new System.EventHandler(this.game2_Click);
                p[1].MouseEnter += new System.EventHandler(this.buttonEnterGame2);
                p[1].MouseLeave += new System.EventHandler(this.buttoLeaveGame2);
                p[1].MouseHover += new EventHandler(mouseHoverPictureBox);
                p[1].MouseLeave += new EventHandler(mouseLeave);
                if (this.game.Count > 2)
                {
                    p[2].Click += new System.EventHandler(this.game3_Click);
                    p[2].MouseEnter += new System.EventHandler(this.buttonEnterGame3);
                    p[2].MouseLeave += new System.EventHandler(this.buttoLeaveGame3);
                    p[2].MouseHover += new EventHandler(mouseHoverPictureBox);
                    p[2].MouseLeave += new EventHandler(mouseLeave);
                }
            }
        }

        //マウスのクリック位置を記憶
        private Point mousePoint;

        //Form1のMouseDownイベントハンドラ
        //マウスのボタンが押されたとき
        private void Form1_MouseDown(object sender,
            System.Windows.Forms.MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                //位置を記憶する
                mousePoint = new Point(e.X, e.Y);
            }
        }

        //Form1のMouseMoveイベントハンドラ
        //マウスが動いたとき
        private void Form1_MouseMove(object sender,
            System.Windows.Forms.MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                this.Left += e.X - mousePoint.X;
                this.Top += e.Y - mousePoint.Y;
            }
        }
    }
}

