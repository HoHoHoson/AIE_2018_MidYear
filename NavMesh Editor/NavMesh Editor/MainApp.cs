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

namespace NavMesh_Editor
{
    public partial class MainApp : Form
    {

        MeshEditor  mEditor = new MeshEditor();
        Point setPoint = new Point(1000, 100); 
        Image       mapTexture;

        public MainApp()
        {
            InitializeComponent();
        }

        private void loadButton_Click(object sender, EventArgs e)
        {
            DialogResult result = loadMapDialog.ShowDialog();

            if (result == DialogResult.OK)
            {
                mapTexture = Image.FromFile(loadMapDialog.FileName);
                loadedImageName.Text = Path.GetFileName(loadMapDialog.FileName);

                pictureBox1.Image = mapTexture;
                
                mEditor.Show();
                mEditor.DesktopLocation = new Point(0, 0);
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Graphics g = Graphics.FromImage(mapTexture);
            Brush p = new SolidBrush(Color.Brown);
            MouseEventArgs me = (MouseEventArgs)e;
            g.FillEllipse(p, me.Location.X - 50, me.Location.Y - 50, 100, 100);
            pictureBox1.Image = mapTexture;
            g.Dispose();
        }
    }
}

