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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainApp));
            this.loadButton = new System.Windows.Forms.Button();
            this.loadMapDialog = new System.Windows.Forms.OpenFileDialog();
            this.loadedImagePanel = new System.Windows.Forms.Panel();
            this.loadedImageDisplay = new System.Windows.Forms.PictureBox();
            this.imageDirectoryText = new System.Windows.Forms.TextBox();
            this.MeshSaveButton = new System.Windows.Forms.Button();
            this.coordinateViewer = new System.Windows.Forms.ToolTip(this.components);
            this.tooltipRefreshTimer = new System.Windows.Forms.Timer(this.components);
            this.MeshLoadButton = new System.Windows.Forms.Button();
            this.loadMeshDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveMeshDialog = new System.Windows.Forms.SaveFileDialog();
            this.MeshDirectoryText = new System.Windows.Forms.TextBox();
            this.titlePart1 = new System.Windows.Forms.Label();
            this.titlePart2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.loadedImagePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.loadedImageDisplay)).BeginInit();
            this.SuspendLayout();
            // 
            // loadButton
            // 
            this.loadButton.AutoSize = true;
            this.loadButton.BackColor = System.Drawing.Color.Transparent;
            this.loadButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.loadButton.Location = new System.Drawing.Point(12, 81);
            this.loadButton.Name = "loadButton";
            this.loadButton.Size = new System.Drawing.Size(236, 23);
            this.loadButton.TabIndex = 2;
            this.loadButton.Text = "Load Background";
            this.loadButton.UseVisualStyleBackColor = false;
            this.loadButton.Click += new System.EventHandler(this.loadButton_Click);
            // 
            // loadMapDialog
            // 
            this.loadMapDialog.FileName = "LoadSomething.png";
            this.loadMapDialog.Title = "Load Background Image";
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
            this.loadedImagePanel.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.loadedImagePanel_MouseDoubleClick);
            this.loadedImagePanel.Resize += new System.EventHandler(this.loadedImagePanel_Resize);
            // 
            // loadedImageDisplay
            // 
            this.loadedImageDisplay.BackColor = System.Drawing.Color.Transparent;
            this.loadedImageDisplay.Location = new System.Drawing.Point(-1, -1);
            this.loadedImageDisplay.Name = "loadedImageDisplay";
            this.loadedImageDisplay.Size = new System.Drawing.Size(377, 232);
            this.loadedImageDisplay.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.loadedImageDisplay.TabIndex = 0;
            this.loadedImageDisplay.TabStop = false;
            this.loadedImageDisplay.MouseDown += new System.Windows.Forms.MouseEventHandler(this.loadedImageDisplay_MouseDown);
            this.loadedImageDisplay.MouseLeave += new System.EventHandler(this.loadedImageDisplay_MouseLeave);
            this.loadedImageDisplay.MouseMove += new System.Windows.Forms.MouseEventHandler(this.loadedImageDisplay_MouseMove);
            // 
            // imageDirectoryText
            // 
            this.imageDirectoryText.CausesValidation = false;
            this.imageDirectoryText.Location = new System.Drawing.Point(12, 55);
            this.imageDirectoryText.Name = "imageDirectoryText";
            this.imageDirectoryText.ReadOnly = true;
            this.imageDirectoryText.Size = new System.Drawing.Size(236, 20);
            this.imageDirectoryText.TabIndex = 5;
            this.imageDirectoryText.MouseLeave += new System.EventHandler(this.imageDirectoryText_MouseLeave);
            // 
            // MeshSaveButton
            // 
            this.MeshSaveButton.AutoSize = true;
            this.MeshSaveButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.MeshSaveButton.Location = new System.Drawing.Point(133, 153);
            this.MeshSaveButton.Name = "MeshSaveButton";
            this.MeshSaveButton.Size = new System.Drawing.Size(115, 23);
            this.MeshSaveButton.TabIndex = 6;
            this.MeshSaveButton.Text = "Save Mesh";
            this.MeshSaveButton.UseVisualStyleBackColor = true;
            this.MeshSaveButton.Click += new System.EventHandler(this.MeshSaveButton_Click);
            // 
            // coordinateViewer
            // 
            this.coordinateViewer.AutomaticDelay = 0;
            this.coordinateViewer.AutoPopDelay = 1000;
            this.coordinateViewer.InitialDelay = 0;
            this.coordinateViewer.ReshowDelay = 0;
            this.coordinateViewer.UseAnimation = false;
            this.coordinateViewer.UseFading = false;
            // 
            // tooltipRefreshTimer
            // 
            this.tooltipRefreshTimer.Tick += new System.EventHandler(this.autoRefreshTimer_Tick);
            // 
            // MeshLoadButton
            // 
            this.MeshLoadButton.AutoSize = true;
            this.MeshLoadButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.MeshLoadButton.Location = new System.Drawing.Point(12, 153);
            this.MeshLoadButton.Name = "MeshLoadButton";
            this.MeshLoadButton.Size = new System.Drawing.Size(115, 23);
            this.MeshLoadButton.TabIndex = 1;
            this.MeshLoadButton.Text = "Load Mesh";
            this.MeshLoadButton.UseVisualStyleBackColor = true;
            this.MeshLoadButton.Click += new System.EventHandler(this.MeshLoadButton_Click);
            // 
            // loadMeshDialog
            // 
            this.loadMeshDialog.InitialDirectory = "$(SolutionDir)";
            this.loadMeshDialog.Title = "Load Navigational Mesh";
            this.loadMeshDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.loadMeshDialog_FileOk);
            // 
            // saveMeshDialog
            // 
            this.saveMeshDialog.Title = "Save Navigational Mesh";
            this.saveMeshDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveMeshDialog_FileOk);
            // 
            // MeshDirectoryText
            // 
            this.MeshDirectoryText.CausesValidation = false;
            this.MeshDirectoryText.Location = new System.Drawing.Point(12, 127);
            this.MeshDirectoryText.Name = "MeshDirectoryText";
            this.MeshDirectoryText.ReadOnly = true;
            this.MeshDirectoryText.Size = new System.Drawing.Size(236, 20);
            this.MeshDirectoryText.TabIndex = 7;
            this.MeshDirectoryText.MouseLeave += new System.EventHandler(this.MeshDirectoryTect_MouseLeave);
            // 
            // titlePart1
            // 
            this.titlePart1.AutoSize = true;
            this.titlePart1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titlePart1.Location = new System.Drawing.Point(66, 12);
            this.titlePart1.Name = "titlePart1";
            this.titlePart1.Size = new System.Drawing.Size(121, 15);
            this.titlePart1.TabIndex = 8;
            this.titlePart1.Text = "Hoson\'s Homemade";
            // 
            // titlePart2
            // 
            this.titlePart2.AutoSize = true;
            this.titlePart2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titlePart2.Location = new System.Drawing.Point(75, 27);
            this.titlePart2.Name = "titlePart2";
            this.titlePart2.Size = new System.Drawing.Size(106, 15);
            this.titlePart2.TabIndex = 9;
            this.titlePart2.Text = "NavMesh Handler";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 228);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(216, 312);
            this.label1.TabIndex = 10;
            this.label1.Text = resources.GetString("label1.Text");
            // 
            // MainApp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.ClientSize = new System.Drawing.Size(1264, 682);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.titlePart2);
            this.Controls.Add(this.titlePart1);
            this.Controls.Add(this.MeshDirectoryText);
            this.Controls.Add(this.MeshLoadButton);
            this.Controls.Add(this.MeshSaveButton);
            this.Controls.Add(this.imageDirectoryText);
            this.Controls.Add(this.loadedImagePanel);
            this.Controls.Add(this.loadButton);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "MainApp";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainApp_FormClosing);
            this.Load += new System.EventHandler(this.MainApp_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainApp_KeyDown);
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
        private System.Windows.Forms.ToolTip coordinateViewer;
        private System.Windows.Forms.Timer tooltipRefreshTimer;
        private System.Windows.Forms.Button MeshLoadButton;
        private System.Windows.Forms.OpenFileDialog loadMeshDialog;
        private System.Windows.Forms.SaveFileDialog saveMeshDialog;
        private System.Windows.Forms.TextBox MeshDirectoryText;
        private System.Windows.Forms.Label titlePart1;
        private System.Windows.Forms.Label titlePart2;
        private System.Windows.Forms.Label label1;
    }
}

