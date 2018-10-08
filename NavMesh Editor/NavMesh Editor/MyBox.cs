using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NavMesh_Editor
{
    public partial class MyBox : Form
    {
        public MyBox()
        {
            InitializeComponent();
        }

        private void MyBox_FormClosed(object sender, FormClosedEventArgs e)
        {
            MyBox b = new MyBox();
            b.Show();
            MyBox o = new MyBox();
            o.Show();
        }
    }
}
