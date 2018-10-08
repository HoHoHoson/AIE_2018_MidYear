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
    public partial class Form1 : Form
    {
        doStuff d = new doStuff();
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Why are you clicking on this?", "Insert crappy caption here");
        }

        private void TestButton_Click(object sender, EventArgs e)
        {
            d.doThing();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch(comboBox1.SelectedItem)
            {
                case "White":
                    {
                        BackColor = Color.White;
                        break;
                    }
                case "Blue":
                    {
                        BackColor = Color.Blue;
                        break;
                    }
                case "Red":
                    {
                        BackColor = Color.Red;
                        break;
                    }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.Items.Add("White");
            comboBox1.Items.Add("Blue");
            comboBox1.Items.Add("Red");
            comboBox1.SelectedItem = "White";
        }

        private void pictureBox1_DragDrop(object sender, DragEventArgs e)
        {

        }
    }
}

