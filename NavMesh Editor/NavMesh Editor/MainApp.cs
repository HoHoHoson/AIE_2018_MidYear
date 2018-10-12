using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml.Serialization;

namespace NavMesh_Editor
{
    public partial class MainApp : Form
    {
        private string formText = "Hoson's Homemade NavMesh Handler";
        private Image mapTexture;

        public MainApp()
        {
            InitializeComponent();
        }
        private void MainApp_Load(object sender, EventArgs e)
        {
            // Whitelisted extensions has one asterix, Blacklisted has two, list can be continued with a semicolon.
            // | for seperating lists and group names 
            loadMapDialog.Filter = "Image Extensions|*.png;*.jpg|Everything Else|*.*";
        }


        private void loadButton_Click(object sender, EventArgs e)
        {
            loadMapDialog.ShowDialog();
        }

        private void loadMapDialog_FileOk(object sender, CancelEventArgs e)
        {
            LoadImage(loadMapDialog.FileName);
        }

        private void imageDirectoryText_MouseLeave(object sender, EventArgs e)
        {
            imageDirectoryText.Enabled = false;
            imageDirectoryText.Enabled = true;
        }



        private void loadedImagePanel_Resize(object sender, EventArgs e)
        {
            PositionDisplay();
        }

        private void loadedImagePanel_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }

        private void loadedImagePanel_DragDrop(object sender, DragEventArgs e)
        {
            string[] s = (string[])e.Data.GetData(DataFormats.FileDrop);
            LoadImage(s[0] as string);
        }

        private void loadedImageDisplay_Click(object sender, EventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;

            if (me.Button == MouseButtons.Left && mapTexture != null)
            {
                Graphics g = Graphics.FromImage(mapTexture);
                Brush b = new SolidBrush(Color.Brown);

                g.FillEllipse(b, me.Location.X - 50, me.Location.Y - 50, 100, 100);
                g.Dispose();
                b.Dispose();

                loadedImageDisplay.Refresh();
            }
        }


        /// <summary>
        /// Will automatically call PositionDisplay() after loading an <see cref="Image"/> from the file path.
        /// </summary>
        /// <param name="filePath"></param>
        private void LoadImage(string filePath)
        {
            mapTexture = Image.FromFile(filePath);
            imageDirectoryText.Text = filePath;
            this.Text = Path.GetFileName(filePath) + " - " + formText;

            loadedImageDisplay.Image = mapTexture;
            loadedImageDisplay.Width = mapTexture.Width;
            loadedImageDisplay.Height = mapTexture.Height;

            PositionDisplay();
        }

        /// <summary>
        /// Relocates the loaded image display. Should be called after resizing the form.
        /// </summary>
        private void PositionDisplay()
        {
            if (loadedImagePanel.Width > loadedImageDisplay.Width)
                loadedImageDisplay.Location = new Point(loadedImagePanel.Width / 2 - loadedImageDisplay.Width / 2, loadedImageDisplay.Location.Y);
            else
                loadedImageDisplay.Location = new Point(0, loadedImageDisplay.Location.Y);

            if (loadedImagePanel.Height > loadedImageDisplay.Height)
                loadedImageDisplay.Location = new Point(loadedImageDisplay.Location.X, loadedImagePanel.Height / 2 - loadedImageDisplay.Height / 2);
            else
                loadedImageDisplay.Location = new Point(loadedImageDisplay.Location.X, 0);

            loadedImagePanel.Refresh();
        }

        private void MeshSaveButton_Click(object sender, EventArgs e)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));
            TextWriter writer = new StreamWriter("myTest.xml");

            NavMeshIO newNav = new NavMeshIO();
            serializer.Serialize(writer, newNav);
            writer.Close();
        }
    }
}

