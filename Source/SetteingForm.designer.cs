namespace SettingForms
{
    partial class SettingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.GameListBox = new System.Windows.Forms.ListBox();
            this.TitleText = new System.Windows.Forms.TextBox();
            this.TitleLabel = new System.Windows.Forms.Label();
            this.GenreText = new System.Windows.Forms.TextBox();
            this.GenreLabel = new System.Windows.Forms.Label();
            this.InfoLabel = new System.Windows.Forms.Label();
            this.InfoText = new System.Windows.Forms.TextBox();
            this.FolderText = new System.Windows.Forms.TextBox();
            this.FolderLabel = new System.Windows.Forms.Label();
            this.ExeLabel = new System.Windows.Forms.Label();
            this.ExeText = new System.Windows.Forms.TextBox();
            this.ThumbnailLabel = new System.Windows.Forms.Label();
            this.ThumbnailText = new System.Windows.Forms.TextBox();
            this.OpenExeFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.ExeRefButton = new System.Windows.Forms.Button();
            this.ThumbRefButton = new System.Windows.Forms.Button();
            this.ListUpdateButton = new System.Windows.Forms.Button();
            this.ListAddButton = new System.Windows.Forms.Button();
            this.OpenFolderDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.FolderRefButton = new System.Windows.Forms.Button();
            this.OpenPicFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.ListDelButton = new System.Windows.Forms.Button();
            this.IconText = new System.Windows.Forms.TextBox();
            this.IconLabel = new System.Windows.Forms.Label();
            this.VerLabel = new System.Windows.Forms.Label();
            this.VerText = new System.Windows.Forms.TextBox();
            this.IconRefButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // GameListBox
            // 
            this.GameListBox.FormattingEnabled = true;
            this.GameListBox.ItemHeight = 12;
            this.GameListBox.Location = new System.Drawing.Point(12, 13);
            this.GameListBox.Name = "GameListBox";
            this.GameListBox.Size = new System.Drawing.Size(120, 400);
            this.GameListBox.TabIndex = 0;
            this.GameListBox.SelectedIndexChanged += new System.EventHandler(this.GameListBox_SelectedIndexChanged);
            // 
            // TitleText
            // 
            this.TitleText.Location = new System.Drawing.Point(138, 28);
            this.TitleText.Name = "TitleText";
            this.TitleText.Size = new System.Drawing.Size(148, 19);
            this.TitleText.TabIndex = 1;
            // 
            // TitleLabel
            // 
            this.TitleLabel.AutoSize = true;
            this.TitleLabel.Location = new System.Drawing.Point(138, 13);
            this.TitleLabel.Name = "TitleLabel";
            this.TitleLabel.Size = new System.Drawing.Size(40, 12);
            this.TitleLabel.TabIndex = 2;
            this.TitleLabel.Text = "タイトル";
            // 
            // GenreText
            // 
            this.GenreText.Location = new System.Drawing.Point(138, 74);
            this.GenreText.Name = "GenreText";
            this.GenreText.Size = new System.Drawing.Size(148, 19);
            this.GenreText.TabIndex = 3;
            // 
            // GenreLabel
            // 
            this.GenreLabel.AutoSize = true;
            this.GenreLabel.Location = new System.Drawing.Point(138, 59);
            this.GenreLabel.Name = "GenreLabel";
            this.GenreLabel.Size = new System.Drawing.Size(42, 12);
            this.GenreLabel.TabIndex = 4;
            this.GenreLabel.Text = "ジャンル";
            // 
            // InfoLabel
            // 
            this.InfoLabel.AutoSize = true;
            this.InfoLabel.Location = new System.Drawing.Point(138, 105);
            this.InfoLabel.Name = "InfoLabel";
            this.InfoLabel.Size = new System.Drawing.Size(41, 12);
            this.InfoLabel.TabIndex = 5;
            this.InfoLabel.Text = "説明文";
            // 
            // InfoText
            // 
            this.InfoText.Location = new System.Drawing.Point(138, 120);
            this.InfoText.Multiline = true;
            this.InfoText.Name = "InfoText";
            this.InfoText.Size = new System.Drawing.Size(234, 40);
            this.InfoText.TabIndex = 6;
            // 
            // FolderText
            // 
            this.FolderText.Location = new System.Drawing.Point(138, 235);
            this.FolderText.Name = "FolderText";
            this.FolderText.Size = new System.Drawing.Size(234, 19);
            this.FolderText.TabIndex = 7;
            // 
            // FolderLabel
            // 
            this.FolderLabel.AutoSize = true;
            this.FolderLabel.Location = new System.Drawing.Point(138, 219);
            this.FolderLabel.Name = "FolderLabel";
            this.FolderLabel.Size = new System.Drawing.Size(76, 12);
            this.FolderLabel.TabIndex = 8;
            this.FolderLabel.Text = "作業フォルダ名";
            // 
            // ExeLabel
            // 
            this.ExeLabel.AutoSize = true;
            this.ExeLabel.Location = new System.Drawing.Point(138, 266);
            this.ExeLabel.Name = "ExeLabel";
            this.ExeLabel.Size = new System.Drawing.Size(76, 12);
            this.ExeLabel.TabIndex = 9;
            this.ExeLabel.Text = "exeファイルパス";
            // 
            // ExeText
            // 
            this.ExeText.Location = new System.Drawing.Point(138, 281);
            this.ExeText.Name = "ExeText";
            this.ExeText.Size = new System.Drawing.Size(234, 19);
            this.ExeText.TabIndex = 10;
            // 
            // ThumbnailLabel
            // 
            this.ThumbnailLabel.AutoSize = true;
            this.ThumbnailLabel.Location = new System.Drawing.Point(138, 356);
            this.ThumbnailLabel.Name = "ThumbnailLabel";
            this.ThumbnailLabel.Size = new System.Drawing.Size(88, 12);
            this.ThumbnailLabel.TabIndex = 11;
            this.ThumbnailLabel.Text = "サムネイルファイル";
            // 
            // ThumbnailText
            // 
            this.ThumbnailText.Location = new System.Drawing.Point(138, 371);
            this.ThumbnailText.Name = "ThumbnailText";
            this.ThumbnailText.Size = new System.Drawing.Size(234, 19);
            this.ThumbnailText.TabIndex = 12;
            // 
            // OpenExeFileDialog
            // 
            this.OpenExeFileDialog.Filter = "実行ファイル(*.exe)|*.exe;|すべてのファイル(*.*)|*.*;";
            this.OpenExeFileDialog.RestoreDirectory = true;
            this.OpenExeFileDialog.Title = "ファイルを選択してください";
            // 
            // ExeRefButton
            // 
            this.ExeRefButton.Location = new System.Drawing.Point(378, 281);
            this.ExeRefButton.Name = "ExeRefButton";
            this.ExeRefButton.Size = new System.Drawing.Size(44, 19);
            this.ExeRefButton.TabIndex = 13;
            this.ExeRefButton.Text = "参照";
            this.ExeRefButton.UseVisualStyleBackColor = true;
            this.ExeRefButton.Click += new System.EventHandler(this.ExeRefButton_Click);
            // 
            // ThumbRefButton
            // 
            this.ThumbRefButton.Location = new System.Drawing.Point(378, 371);
            this.ThumbRefButton.Name = "ThumbRefButton";
            this.ThumbRefButton.Size = new System.Drawing.Size(44, 19);
            this.ThumbRefButton.TabIndex = 14;
            this.ThumbRefButton.Text = "参照";
            this.ThumbRefButton.UseVisualStyleBackColor = true;
            this.ThumbRefButton.Click += new System.EventHandler(this.ThumbRefButton_Click);
            // 
            // ListUpdateButton
            // 
            this.ListUpdateButton.Location = new System.Drawing.Point(347, 400);
            this.ListUpdateButton.Name = "ListUpdateButton";
            this.ListUpdateButton.Size = new System.Drawing.Size(75, 23);
            this.ListUpdateButton.TabIndex = 16;
            this.ListUpdateButton.Text = "修正";
            this.ListUpdateButton.UseVisualStyleBackColor = true;
            this.ListUpdateButton.Click += new System.EventHandler(this.ListUpdateButton_Click);
            // 
            // ListAddButton
            // 
            this.ListAddButton.Location = new System.Drawing.Point(242, 400);
            this.ListAddButton.Name = "ListAddButton";
            this.ListAddButton.Size = new System.Drawing.Size(75, 23);
            this.ListAddButton.TabIndex = 17;
            this.ListAddButton.Text = "追加";
            this.ListAddButton.UseVisualStyleBackColor = true;
            this.ListAddButton.Click += new System.EventHandler(this.ListAddButton_Click);
            // 
            // OpenFolderDialog
            // 
            this.OpenFolderDialog.Description = "フォルダを選択してください";
            // 
            // FolderRefButton
            // 
            this.FolderRefButton.Location = new System.Drawing.Point(378, 234);
            this.FolderRefButton.Name = "FolderRefButton";
            this.FolderRefButton.Size = new System.Drawing.Size(44, 19);
            this.FolderRefButton.TabIndex = 18;
            this.FolderRefButton.Text = "参照";
            this.FolderRefButton.UseVisualStyleBackColor = true;
            this.FolderRefButton.Click += new System.EventHandler(this.FolderRefButton_Click);
            // 
            // OpenPicFileDialog
            // 
            this.OpenPicFileDialog.Filter = "画像ファイル(*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp;|すべてのファイル(*.*)|*.*;";
            this.OpenPicFileDialog.RestoreDirectory = true;
            this.OpenPicFileDialog.Title = "ファイルを選択してください";
            // 
            // ListDelButton
            // 
            this.ListDelButton.Location = new System.Drawing.Point(142, 400);
            this.ListDelButton.Name = "ListDelButton";
            this.ListDelButton.Size = new System.Drawing.Size(75, 23);
            this.ListDelButton.TabIndex = 19;
            this.ListDelButton.Text = "削除";
            this.ListDelButton.UseVisualStyleBackColor = true;
            this.ListDelButton.Click += new System.EventHandler(this.ListDelButton_Click);
            // 
            // IconText
            // 
            this.IconText.Location = new System.Drawing.Point(138, 325);
            this.IconText.Name = "IconText";
            this.IconText.Size = new System.Drawing.Size(234, 19);
            this.IconText.TabIndex = 20;
            // 
            // IconLabel
            // 
            this.IconLabel.AutoSize = true;
            this.IconLabel.Location = new System.Drawing.Point(138, 310);
            this.IconLabel.Name = "IconLabel";
            this.IconLabel.Size = new System.Drawing.Size(74, 12);
            this.IconLabel.TabIndex = 21;
            this.IconLabel.Text = "アイコンファイル";
            // 
            // VerLabel
            // 
            this.VerLabel.AutoSize = true;
            this.VerLabel.Location = new System.Drawing.Point(138, 172);
            this.VerLabel.Name = "VerLabel";
            this.VerLabel.Size = new System.Drawing.Size(50, 12);
            this.VerLabel.TabIndex = 22;
            this.VerLabel.Text = "バージョン";
            // 
            // VerText
            // 
            this.VerText.Location = new System.Drawing.Point(138, 188);
            this.VerText.Name = "VerText";
            this.VerText.Size = new System.Drawing.Size(148, 19);
            this.VerText.TabIndex = 23;
            // 
            // IconRefButton
            // 
            this.IconRefButton.Location = new System.Drawing.Point(378, 325);
            this.IconRefButton.Name = "IconRefButton";
            this.IconRefButton.Size = new System.Drawing.Size(44, 19);
            this.IconRefButton.TabIndex = 24;
            this.IconRefButton.Text = "参照";
            this.IconRefButton.UseVisualStyleBackColor = true;
            this.IconRefButton.Click += new System.EventHandler(this.IconRefButton_Click);
            // 
            // SettingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(434, 427);
            this.Controls.Add(this.IconRefButton);
            this.Controls.Add(this.VerText);
            this.Controls.Add(this.VerLabel);
            this.Controls.Add(this.IconLabel);
            this.Controls.Add(this.IconText);
            this.Controls.Add(this.ListDelButton);
            this.Controls.Add(this.FolderRefButton);
            this.Controls.Add(this.ListAddButton);
            this.Controls.Add(this.ListUpdateButton);
            this.Controls.Add(this.ThumbRefButton);
            this.Controls.Add(this.ExeRefButton);
            this.Controls.Add(this.ThumbnailText);
            this.Controls.Add(this.ThumbnailLabel);
            this.Controls.Add(this.ExeText);
            this.Controls.Add(this.ExeLabel);
            this.Controls.Add(this.FolderLabel);
            this.Controls.Add(this.FolderText);
            this.Controls.Add(this.InfoText);
            this.Controls.Add(this.InfoLabel);
            this.Controls.Add(this.GenreLabel);
            this.Controls.Add(this.GenreText);
            this.Controls.Add(this.TitleLabel);
            this.Controls.Add(this.TitleText);
            this.Controls.Add(this.GameListBox);
            this.Name = "SettingForm";
            this.Text = "ゲームの登録/修正";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox GameListBox;
        private System.Windows.Forms.TextBox TitleText;
        private System.Windows.Forms.Label TitleLabel;
        private System.Windows.Forms.TextBox GenreText;
        private System.Windows.Forms.Label GenreLabel;
        private System.Windows.Forms.Label InfoLabel;
        private System.Windows.Forms.TextBox InfoText;
        private System.Windows.Forms.TextBox FolderText;
        private System.Windows.Forms.Label FolderLabel;
        private System.Windows.Forms.Label ExeLabel;
        private System.Windows.Forms.TextBox ExeText;
        private System.Windows.Forms.Label ThumbnailLabel;
        private System.Windows.Forms.TextBox ThumbnailText;
        private System.Windows.Forms.OpenFileDialog OpenExeFileDialog;
        private System.Windows.Forms.Button ExeRefButton;
        private System.Windows.Forms.Button ThumbRefButton;
        private System.Windows.Forms.Button ListUpdateButton;
        private System.Windows.Forms.Button ListAddButton;
        private System.Windows.Forms.FolderBrowserDialog OpenFolderDialog;
        private System.Windows.Forms.Button FolderRefButton;
        private System.Windows.Forms.OpenFileDialog OpenPicFileDialog;
        private System.Windows.Forms.Button ListDelButton;
        private System.Windows.Forms.TextBox IconText;
        private System.Windows.Forms.Label IconLabel;
        private System.Windows.Forms.Label VerLabel;
        private System.Windows.Forms.TextBox VerText;
        private System.Windows.Forms.Button IconRefButton;
    }
}