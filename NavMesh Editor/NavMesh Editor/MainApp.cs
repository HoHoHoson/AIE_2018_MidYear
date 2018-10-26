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

        public static Image originaImage { get; private set; }
        private NavMeshIO navMesh;
        private Image meshCanvas;

        public static int nodeDiameter { get; private set; } = 10;
        private int lineWidth = 4;
        private System.Drawing.Point mouseLastPos;

        public MainApp()
        {
            InitializeComponent();
        }



        // Logic and events for the main application.
        //
        // Runs when the application first starts up.
        private void MainApp_Load(object sender, EventArgs e)
        {
            // Whitelisted extensions has one asterix, Blacklisted has two, list can be continued with a semicolon.
            // | for seperating lists and group names 
            loadMapDialog.Filter = "Image Extensions|*.jpg;*.png;*.jpeg;*.bmp;|Everything Else|*.*";
            loadMeshDialog.Filter = "File Extensions|*.xml|Everything Else|*.*";
            saveMeshDialog.Filter = "XML|*.xml";
            navMesh = new NavMeshIO();
        }

        // How the application acts to certain key presses.
        private void MainApp_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                navMesh.ClearSelected();
                DrawMesh();
            }
        }

        // Runs when the application closes.
        private void MainApp_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (navMesh.polygons.Count == 0)
                return;

            DialogResult dr = MessageBox.Show("Would you like to save your mesh?", "Application Shutdown", MessageBoxButtons.YesNoCancel);

            if (dr == DialogResult.Yes)
                saveMeshDialog.ShowDialog();
            else if (dr == DialogResult.Cancel)
                e.Cancel = true;
        }



        // Handles the Image that gets loaded in as the background for drawing a mesh onto.
        //
        // Button that opens up the dialog box that will load in a specified Image.
        private void loadButton_Click(object sender, EventArgs e)
        {
            if (navMesh.polygons.Count != 0)
                if (OverrideMeshOrImage(false) == false)
                    return;

            loadMapDialog.ShowDialog();
        }

        // Dialog Box that loads in an Image.
        private void loadMapDialog_FileOk(object sender, CancelEventArgs e)
        {
            LoadImage(loadMapDialog.FileName);
        }

        // Refreshes the text Box that displays the loaded Image's directory to get rid of the caret.
        private void imageDirectoryText_MouseLeave(object sender, EventArgs e)
        {
            imageDirectoryText.Enabled = false;
            imageDirectoryText.Enabled = true;
        }



        // These controls handles the saving/loading of navigational meshs as XML files.
        //
        // Button that opens up the loadMeshDialog box.
        private void MeshLoadButton_Click(object sender, EventArgs e)
        {
            if (originaImage == null)
            {
                MessageBox.Show("There is no background image.", "ERROR");
                return;
            }

            if (navMesh.polygons.Count != 0)
                if (OverrideMeshOrImage(true) == false)
                    return;

            loadMeshDialog.ShowDialog();
        }

        // Dialog box for loading in an existing XML mesh that is specified by the user.
        private void loadMeshDialog_FileOk(object sender, CancelEventArgs e)
        {
            Deserialise(loadMeshDialog.FileName);
            DrawMesh();
        }

        // Button that opens up the saveMeshDialog box.
        private void MeshSaveButton_Click(object sender, EventArgs e)
        {
            if (navMesh.polygons.Count != 0)
                saveMeshDialog.ShowDialog();
            else
                MessageBox.Show("Navigational Mesh is empty.", "ERROR");
        }

        //Dialog box that saves the NavMesh as a XML file.
        private void saveMeshDialog_FileOk(object sender, CancelEventArgs e)
        {
                XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));
                TextWriter writer = new StreamWriter(saveMeshDialog.FileName);

                serializer.Serialize(writer, navMesh);
                writer.Close();
        }

        // Removes the MeshDir textbox's caret after it goes out of focus.
        private void MeshDirectoryTect_MouseLeave(object sender, EventArgs e)
        {
            MeshDirectoryText.Enabled = false;
            MeshDirectoryText.Enabled = true;
        }



        // Panel Containing the Picturebox that displays the loaded Image.
        //
        // Mouse controls for creating and deleting nodes and polygons.
        private void loadedImageDisplay_MouseDown(object sender, MouseEventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;

            if (me.Button == MouseButtons.Left && originaImage != null)
                navMesh.VectorInput(new Vector(me.Location.X, originaImage.Height - me.Location.Y));

            if (me.Button == MouseButtons.Right && originaImage != null && navMesh.tempNodes.Count != 0)
                navMesh.UndoPrevNode();

            if (me.Button == MouseButtons.Middle && originaImage != null && navMesh.polygons.Count != 0)
                navMesh.RemovePolygon(new Vector(me.Location.X, originaImage.Height - me.Location.Y));

            if (originaImage != null)
                DrawMesh();
        }

        // Resizes the image inside the panel if the form gets resized.
        private void loadedImagePanel_Resize(object sender, EventArgs e)
        {
            PositionDisplay();
        }

        // Allows data to be dragged into the application's image panel to be loaded.
        private void loadedImagePanel_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }

        // Processes the data that was dragged into the imagebox.
        private void loadedImagePanel_DragDrop(object sender, DragEventArgs e)
        {
            string[] s = (string[])e.Data.GetData(DataFormats.FileDrop);

            if (Path.GetExtension(s[0]) == ".jpg" || Path.GetExtension(s[0]) == ".jpeg" || Path.GetExtension(s[0]) == ".png" || Path.GetExtension(s[0]) == ".bmp")
            {
                if (navMesh.polygons.Count != 0)
                    if (OverrideMeshOrImage(false) == false)
                        return;

                LoadImage(s[0] as string);
                DrawMesh();
            }
            else if (Path.GetExtension(s[0]) == ".xml")
            {
                if (originaImage == null)
                {
                    MessageBox.Show("There is no background image.", "ERROR");
                    return;
                }

                if (OverrideMeshOrImage(true) == true)
                {
                   Deserialise(s[0] as string);
                   DrawMesh();
                }
            }
            else
                MessageBox.Show("Invalid file type.", "ERROR");
        }

        // Feature that changes the background colour when the panel gets double clicked.
        private void loadedImagePanel_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (loadedImagePanel.BackColor.Name == "Control")
                loadedImagePanel.BackColor = Color.FromKnownColor(KnownColor.Black);
            else
                loadedImagePanel.BackColor = Color.FromKnownColor(KnownColor.Control);
        }



        // Picturebox that displays the loaded Image.
        //
        // Creates a tooltip that displays the current coordinate of the mouse over the image.
        private void loadedImageDisplay_MouseMove(object sender, MouseEventArgs e)
        {
            if (originaImage != null)
                if (mouseLastPos != e.Location)
                {
                    mouseLastPos = e.Location;
                    coordinateViewer.SetToolTip(loadedImageDisplay, e.Location.X + " , " + (originaImage.Height - e.Location.Y));
                    tooltipRefreshTimer.Stop();
                }
                else
                    tooltipRefreshTimer.Start();
        }

        // Tooltip gets removed once the mouse moves out of the image.
        private void loadedImageDisplay_MouseLeave(object sender, EventArgs e)
        {
            coordinateViewer.Hide(loadedImageDisplay);
        }

        // Timer that refreshes the Coordinate Viewer tooltip so that it doesn't auto hide.
        private void autoRefreshTimer_Tick(object sender, EventArgs e)
        {
            System.Drawing.Point mouseCoord = loadedImageDisplay.PointToClient(MousePosition);
            coordinateViewer.SetToolTip(loadedImageDisplay, mouseCoord.X + " , " + (originaImage.Height - mouseCoord.Y));
        }



        /// <summary>
        /// Draws the Navigational Mesh onto the background image.
        /// </summary>
        public void DrawMesh()
        {
            meshCanvas = (Image)originaImage.Clone();
            Graphics g = Graphics.FromImage(meshCanvas);

            if (navMesh.polygons.Count != 0)
            {
                Brush nodeColour = new SolidBrush(Color.DodgerBlue);
                Brush polyColour = new SolidBrush(Color.FromArgb(100, 100, 149, 237));
                Pen edgeColour = new Pen(Color.CornflowerBlue, lineWidth);

                foreach (Polygon poly in navMesh.polygons)
                {
                    HashSet<PointF> polyPoints = new HashSet<PointF>();

                    foreach (Edge ed in poly.edges)
                    {
                        polyPoints.Add(new PointF((float)ed.start.X, (float)(originaImage.Height - ed.start.Y)));
                        polyPoints.Add(new PointF((float)ed.end.X, (float)(originaImage.Height - ed.end.Y)));
                    }

                    g.FillPolygon(polyColour, polyPoints.ToArray());
                }   

                foreach (Polygon poly in navMesh.polygons)
                    foreach (Edge ed in poly.edges)
                    {
                        System.Drawing.Point p1 = new System.Drawing.Point((int)ed.start.X, (int)(originaImage.Height - ed.start.Y));
                        System.Drawing.Point p2 = new System.Drawing.Point((int)ed.end.X, (int)(originaImage.Height - ed.end.Y));

                        g.DrawLine(edgeColour, p1, p2);
                    
                        g.FillEllipse(nodeColour, p1.X - nodeDiameter / 2, p1.Y - nodeDiameter / 2, nodeDiameter, nodeDiameter);
                        g.FillEllipse(nodeColour, p2.X - nodeDiameter / 2, p2.Y - nodeDiameter / 2, nodeDiameter, nodeDiameter);
                    }

                nodeColour.Dispose();
                edgeColour.Dispose();
                polyColour.Dispose();
            }

            if (navMesh.nodeSelect != null && 
                !double.IsNaN(navMesh.nodeSelect.X) && !double.IsNaN(navMesh.nodeSelect.Y))
            {
                Brush highlight = new SolidBrush(Color.HotPink);
                System.Drawing.Point sel = new System.Drawing.Point((int)navMesh.nodeSelect.X, (int)(originaImage.Height - navMesh.nodeSelect.Y));

                g.FillEllipse(highlight, sel.X - nodeDiameter * 1.25f / 2, sel.Y - nodeDiameter * 1.25f / 2, 
                              nodeDiameter * 1.25f, nodeDiameter * 1.25f);

                highlight.Dispose();
            }

            Brush neonLime = new SolidBrush(Color.LimeGreen);
            Pen limeLine = new Pen(Color.Lime, lineWidth);
            Pen dashLine = new Pen(Color.Lime, lineWidth);
            float[] dashValues = { 2, 2 };
            dashLine.DashPattern = dashValues;

            for (int i = 0; i < navMesh.tempNodes.Count; ++i)
            {
                PointF end;
                PointF origin;

                if (navMesh.tempNodes.Count - 1 == i)
                {
                    origin = new PointF((float)navMesh.tempNodes.ElementAt(i).X, originaImage.Height - (float)navMesh.tempNodes.ElementAt(i).Y);
                    end = new PointF((float)navMesh.tempNodes.ElementAt(0).X, originaImage.Height - (float)navMesh.tempNodes.ElementAt(0).Y);
                    g.DrawLine(dashLine, origin, end);
                }
                else
                {
                    origin = new PointF((float)navMesh.tempNodes.ElementAt(i).X, originaImage.Height - (float)navMesh.tempNodes.ElementAt(i).Y);
                    end = new PointF((float)navMesh.tempNodes.ElementAt(i + 1).X, originaImage.Height - (float)navMesh.tempNodes.ElementAt(i + 1).Y);
                    g.DrawLine(limeLine, origin, end);
                }

                g.FillEllipse(neonLime, origin.X - nodeDiameter / 2, origin.Y - nodeDiameter / 2, nodeDiameter, nodeDiameter);
            }
            
            loadedImageDisplay.Image = meshCanvas;
            loadedImageDisplay.Refresh();

            g.Dispose();
            neonLime.Dispose();
            limeLine.Dispose();
            dashLine.Dispose();
        }
        
        /// <summary>
        /// Will automatically call PositionDisplay() after loading an <see cref="Image"/> from the file path.
        /// </summary>
        /// <param name="filePath"></param>
        private void LoadImage(string filePath)
        {
            navMesh.polygons.Clear();
            navMesh.ClearSelected();

            originaImage = Image.FromFile(filePath);
            imageDirectoryText.Text = filePath;

            loadedImageDisplay.Image = originaImage;
            loadedImageDisplay.Width = originaImage.Width;
            loadedImageDisplay.Height = originaImage.Height;

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

        /// <summary>
        /// Deserliases the xml file of the given filename.
        /// </summary>
        /// <param name="fileName"></param>
        private void Deserialise(string filePath)
        {
            navMesh.ClearSelected();

            Stream stream = File.Open(filePath, FileMode.Open);
            XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));
            navMesh = (NavMeshIO)serializer.Deserialize(stream);
            stream.Close();

            this.Text = Path.GetFileName(filePath);
            MeshDirectoryText.Text = filePath;
        }

        /// <summary>
        /// Messagebox for when the mesh or image gets overrided. True for mesh, false for image. Function also returns false if the save was canceled.
        /// </summary>
        /// <param name="isMesh"></param>
        private bool OverrideMeshOrImage(bool isMesh)
        {
            string type = "Mesh";
            if (isMesh == false)
                type = "Image";

            DialogResult dr = MessageBox.Show("Would you like to save your mesh?", "Overriding " + type, MessageBoxButtons.YesNoCancel);

            if (dr == DialogResult.Yes)
                saveMeshDialog.ShowDialog();
            else if (dr == DialogResult.Cancel)
                return false;

            return true;
        }
    }
}

