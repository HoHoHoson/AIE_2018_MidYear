namespace NavMesh_Editor
{
    partial class MainApp
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
            this.loadButton = new System.Windows.Forms.Button();
            this.loadMapDialog = new System.Windows.Forms.OpenFileDialog();
            this.loadedImagePanel = new System.Windows.Forms.Panel();
            this.loadedImageDisplay = new System.Windows.Forms.PictureBox();
            this.imageDirectoryText = new System.Windows.Forms.TextBox();
            this.MeshSaveButton = new System.Windows.Forms.Button();
            this.loadedImagePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.loadedImageDisplay)).BeginInit();
            this.SuspendLayout();
            // 
            // loadButton
            // 
            this.loadButton.BackColor = System.Drawing.Color.Transparent;
            this.loadButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.loadButton.Location = new System.Drawing.Point(84, 38);
            this.loadButton.Name = "loadButton";
            this.loadButton.Size = new System.Drawing.Size(75, 23);
            this.loadButton.TabIndex = 2;
            this.loadButton.Text = "Load";
            this.loadButton.UseVisualStyleBackColor = false;
            this.loadButton.Click += new System.EventHandler(this.loadButton_Click);
            // 
            // loadMapDialog
            // 
            this.loadMapDialog.FileName = "LoadSomething.png";
            this.loadMapDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.loadMapDialog_FileOk);
            // 
            // loadedImagePanel
            // 
            this.loadedImagePanel.AllowDrop = true;
            this.loadedImagePanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.loadedImagePanel.AutoScroll = true;
            this.loadedImagePanel.BackColor = System.Drawing.SystemColors.Control;
            this.loadedImagePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.loadedImagePanel.CausesValidation = false;
            this.loadedImagePanel.Controls.Add(this.loadedImageDisplay);
            this.loadedImagePanel.Location = new System.Drawing.Point(254, -2);
            this.loadedImagePanel.Name = "loadedImagePanel";
            this.loadedImagePanel.Size = new System.Drawing.Size(1011, 685);
            this.loadedImagePanel.TabIndex = 4;
            this.loadedImagePanel.DragDrop += new System.Windows.Forms.DragEventHandler(this.loadedImagePanel_DragDrop);
            this.loadedImagePanel.DragEnter += new System.Windows.Forms.DragEventHandler(this.loadedImagePanel_DragEnter);
            this.loadedImagePanel.Resize += new System.EventHandler(this.loadedImagePanel_Resize);
            // 
            // loadedImageDisplay
            // 
            this.loadedImageDisplay.BackColor = System.Drawing.Color.Transparent;
            this.loadedImageDisplay.Location = new System.Drawing.Point(0, 0);
            this.loadedImageDisplay.Name = "loadedImageDisplay";
            this.loadedImageDisplay.Size = new System.Drawing.Size(377, 232);
            this.loadedImageDisplay.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.loadedImageDisplay.TabIndex = 0;
            this.loadedImageDisplay.TabStop = false;
            this.loadedImageDisplay.Click += new System.EventHandler(this.loadedImageDisplay_Click);
            // 
            // imageDirectoryText
            // 
            this.imageDirectoryText.CausesValidation = false;
            this.imageDirectoryText.Location = new System.Drawing.Point(12, 12);
            this.imageDirectoryText.Name = "imageDirectoryText";
            this.imageDirectoryText.ReadOnly = true;
            this.imageDirectoryText.Size = new System.Drawing.Size(236, 20);
            this.imageDirectoryText.TabIndex = 5;
            this.imageDirectoryText.MouseLeave += new System.EventHandler(this.imageDirectoryText_MouseLeave);
            // 
            // MeshSaveButton
            // 
            this.MeshSaveButton.Location = new System.Drawing.Point(84, 67);
            this.MeshSaveButton.Name = "MeshSaveButton";
            this.MeshSaveButton.Size = new System.Drawing.Size(75, 23);
            this.MeshSaveButton.TabIndex = 6;
            this.MeshSaveButton.Text = "SAVE";
            this.MeshSaveButton.UseVisualStyleBackColor = true;
            this.MeshSaveButton.Click += new System.EventHandler(this.MeshSaveButton_Click);
            // 
            // MainApp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.ClientSize = new System.Drawing.Size(1264, 682);
            this.Controls.Add(this.MeshSaveButton);
            this.Controls.Add(this.imageDirectoryText);
            this.Controls.Add(this.loadedImagePanel);
            this.Controls.Add(this.loadButton);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Name = "MainApp";
            this.Text = "Hoson\'s Homemade NavMesh Handler";
            this.Load += new System.EventHandler(this.MainApp_Load);
            this.loadedImagePanel.ResumeLayout(false);
            this.loadedImagePanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.loadedImageDisplay)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button loadButton;
        private System.Windows.Forms.OpenFileDialog loadMapDialog;
        private System.Windows.Forms.Panel loadedImagePanel;
        private System.Windows.Forms.PictureBox loadedImageDisplay;
        private System.Windows.Forms.TextBox imageDirectoryText;
        private System.Windows.Forms.Button MeshSaveButton;
    }
}

