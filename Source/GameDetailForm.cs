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

namespace MainForms
{
    public partial class GameDetailForm : Form
    {
        Form parent;
        GameInfo gi;

        public GameDetailForm()
        {
            InitializeComponent();
        }

        public GameDetailForm(Form f, GameInfo g)
        {
            InitializeComponent();

            parent = f;
            gi = g;
        }

        private void GameDetailForm_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.FromArgb(FORM_TOP_COLOR_R, FORM_TOP_COLOR_G, FORM_TOP_COLOR_B);
            this.label1.BackColor = Color.FromArgb(BUTTON_HOVER_COLOR_R, BUTTON_HOVER_COLOR_G, BUTTON_HOVER_COLOR_B); 
            SetLocation();
            UpdateWindow();
        }

        private void SetLocation()
        {
            var pLocation = parent.Bounds; ;
            var myLocation = new Point();

            myLocation.X = pLocation.X + pLocation.Width;
            myLocation.Y = (pLocation.Y + (pLocation.Height / 2)) - (this.Height / 2);

            this.Location = myLocation;
        }

        private void UpdateWindow()
        {
            Bitmap thum = (Bitmap)Image.FromFile(GameInfo.appPath + @"\" + gi.Thumbnail);
            pictureBox1.BackgroundImage = thum;

            label1.Text = gi.Info;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
