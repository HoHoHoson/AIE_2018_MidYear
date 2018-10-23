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
        private void MainApp_Load(object sender, EventArgs e)
        {
            // Whitelisted extensions has one asterix, Blacklisted has two, list can be continued with a semicolon.
            // | for seperating lists and group names 
            loadMapDialog.Filter = "Image Extensions|*.png;*.jpg|Everything Else|*.*";
            loadMeshDialog.Filter = "File Extensions|*.xml|Everything Else|*.*";
            saveMeshDialog.Filter = "XML|*.xml";
            navMesh = new NavMeshIO();
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

        private void loadMeshDialog_FileOk(object sender, CancelEventArgs e)
        {
            Deserialise(loadMeshDialog.FileName);
            DrawMesh();
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
            saveMeshDialog.ShowDialog();
        }

        private void MeshLoadButton_Click(object sender, EventArgs e)
        {
            loadMeshDialog.ShowDialog();
        }



        // Timer that refreshes the Coordinate Viewer tooltip so that it doesn't auto hide.
        private void autoRefreshTimer_Tick(object sender, EventArgs e)
        {
            System.Drawing.Point mouseCoord = loadedImageDisplay.PointToClient(MousePosition);
            coordinateViewer.SetToolTip(loadedImageDisplay, mouseCoord.X + " , " + (originaImage.Height - mouseCoord.Y));
        }



        // Panel Containing the Picturebox that displays the loaded Image.
        private void loadedImageDisplay_MouseDown(object sender, MouseEventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;

            if (me.Button == MouseButtons.Left && originaImage != null)
            {
                navMesh.VectorInput(new Vector(me.Location.X, originaImage.Height - me.Location.Y));
                DrawMesh();
            }
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

        private void loadedImageDisplay_MouseLeave(object sender, EventArgs e)
        {
            coordinateViewer.Hide(loadedImageDisplay);
        }



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
            originaImage = Image.FromFile(filePath);
            imageDirectoryText.Text = filePath;
            this.Text = Path.GetFileName(filePath) + " - " + formText;

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
            Stream stream = File.Open(filePath, FileMode.Open);
            XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));

            navMesh = (NavMeshIO)serializer.Deserialize(stream);
            stream.Close();
        }

        private void saveMeshDialog_FileOk(object sender, CancelEventArgs e)
        {
            if (navMesh != null)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(NavMeshIO));
                TextWriter writer = new StreamWriter(saveMeshDialog.FileName);

                serializer.Serialize(writer, navMesh);
                writer.Close();
            }
            else
                MessageBox.Show("No NavMesh is loaded", "WARNING");
        }

        private void MainApp_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Back)
            {
                navMesh.UndoPrevNode();
                DrawMesh();
            }

            if (e.KeyCode == Keys.Delete)
            {
                navMesh.ClearSelected();
                DrawMesh();
            }
        }
    }

}

