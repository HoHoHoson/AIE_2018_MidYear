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
using System.Windows;

namespace NavMesh_Editor
{
    public partial class MainApp : Form
    {
        private string formText = "Hoson's Homemade NavMesh Handler";

        private NavMeshIO navMesh;
        private Image mapTexture;

        public int nodeWidth { get; private set; } = 10;
        public int nodeHeight { get; private set; } = 10;
        private System.Drawing.Point mouseLastPos;

        public MainApp()
        {
            InitializeComponent();
        }
        private void MainApp_Load(object sender, EventArgs e)
        {
            // Whitelisted extensions has one asterix, Blacklisted has two, list can be continued with a semicolon.
            // | for seperating lists and group names 
            loadMapDialog.Filter = "Image Extensions|*.png;*.jpg|Everything Else|*.*";
            navMesh = new NavMeshIO(this);
        }



        // Button that opens up the dialog box that will load in a specified Image.
        private void loadButton_Click(object sender, EventArgs e)
        {
            loadMapDialog.ShowDialog();
        }



        // Dialog Box that loads in an Image.
        private void loadMapDialog_FileOk(object sender, CancelEventArgs e)
        {
            LoadImage(loadMapDialog.FileName);
        }



        // Text Box that displays the loaded Image's directory.
        private void imageDirectoryText_MouseLeave(object sender, EventArgs e)
        {
            imageDirectoryText.Enabled = false;
            imageDirectoryText.Enabled = true;
        }



        // Button that saves the NavMesh to a XML file.
        private void MeshSaveButton_Click(object sender, EventArgs e)
        {
            if (navMesh != null)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));
                TextWriter writer = new StreamWriter("myTest.xml");

                serializer.Serialize(writer, navMesh);
                writer.Close();
            }
            else
                MessageBox.Show("No NavMesh is loaded", "WARNING");
        }



        // Timer that refreshes the Coordinate Viewer tooltip so that it doesn't auto hide.
        private void autoRefreshTimer_Tick(object sender, EventArgs e)
        {
            System.Drawing.Point mouseCoord = loadedImageDisplay.PointToClient(MousePosition);
            coordinateViewer.SetToolTip(loadedImageDisplay, mouseCoord.X + " , " + (mapTexture.Height - mouseCoord.Y));
        }



        // Panel Containing the Picturebox that displays the loaded Image.
        private void loadedImageDisplay_MouseDown(object sender, MouseEventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;

            //if (me.Button == MouseButtons.Left && mapTexture != null)
            //{
            //    Graphics g = Graphics.FromImage(mapTexture);
            //    Brush b = new SolidBrush(Color.LimeGreen);

            //    g.FillEllipse(b, me.Location.X - nodeWidth / 2, me.Location.Y - nodeHeight / 2, nodeWidth, nodeHeight);
            //    g.Dispose();
            //    b.Dispose();

            //    loadedImageDisplay.Refresh();
            //}
            navMesh.storedVertices.Add(new Vector(me.Location.X, me.Location.Y));
            DrawMesh();
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

        private void loadedImagePanel_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (loadedImagePanel.BackColor.Name == "Control")
                loadedImagePanel.BackColor = Color.FromKnownColor(KnownColor.Black);
            else
                loadedImagePanel.BackColor = Color.FromKnownColor(KnownColor.Control);
        }



        // Picturebox that displays the loaded Image.
        private void loadedImageDisplay_MouseMove(object sender, MouseEventArgs e)
        {
            if (mapTexture != null)
                if (mouseLastPos != e.Location)
                {
                    mouseLastPos = e.Location;
                    coordinateViewer.SetToolTip(loadedImageDisplay, e.Location.X + " , " + (mapTexture.Height - e.Location.Y));
                    autoRefreshTimer.Stop();
                }
                else
                    autoRefreshTimer.Start();
        }

        private void loadedImageDisplay_MouseLeave(object sender, EventArgs e)
        {
            coordinateViewer.Hide(loadedImageDisplay);
        }



        public void DrawMesh()
        {
            Graphics g = Graphics.FromImage(mapTexture);
            Brush b = new SolidBrush(Color.LimeGreen);

            if (navMesh.selectedNode != null)
            {
                Brush pinkBrush = new SolidBrush(Color.HotPink);
                Vector vec = navMesh.selectedNode;

                g.FillEllipse(pinkBrush, (float)vec.X - nodeWidth / 2, (float)vec.Y - nodeHeight / 2, nodeWidth, nodeHeight);

                pinkBrush.Dispose();
            }

            foreach (Vector p in navMesh.storedVertices)
            {
                g.FillEllipse(b, (float)p.X - nodeWidth / 2, (float)p.Y - nodeHeight / 2, nodeWidth, nodeHeight);
            }

            g.Dispose();
            b.Dispose();
            loadedImageDisplay.Refresh();
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
                loadedImageDisplay.Location = new System.Drawing.Point(loadedImagePanel.Width / 2 - loadedImageDisplay.Width / 2, loadedImageDisplay.Location.Y);
            else
                loadedImageDisplay.Location = new System.Drawing.Point(0, loadedImageDisplay.Location.Y);

            if (loadedImagePanel.Height > loadedImageDisplay.Height)
                loadedImageDisplay.Location = new System.Drawing.Point(loadedImageDisplay.Location.X, loadedImagePanel.Height / 2 - loadedImageDisplay.Height / 2);
            else
                loadedImageDisplay.Location = new System.Drawing.Point(loadedImageDisplay.Location.X, 0);

            loadedImagePanel.Refresh();
        }
    }
}

