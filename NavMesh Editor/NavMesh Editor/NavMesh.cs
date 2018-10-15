using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.Xml.Serialization;
using System.Diagnostics;
using System.Windows;

namespace NavMesh_Editor
{
    [Serializable]
    public class NavMeshIO
    {
        public NavMeshIO(MainApp link) { mainApp = link; }
        public List<Polygon> polygons = new List<Polygon>();

        [XmlIgnore]
        public Vector selectedNode { get; private set; }
        [XmlIgnore]
        public List<Vector> storedVertices { get; set; } = new List<Vector>();
        private MainApp mainApp;

        public void MouseInput(Vector mousePos)
        {
            selectedNode = CheckFor(mousePos);

            if (selectedNode.X == float.NaN || selectedNode.Y == float.NaN)
                return;
        }

        private Vector CheckFor(Vector pos)
        {
            foreach(Polygon poly in polygons)
            {
                foreach(Edge ed in poly.edges)
                {
                    float startDis = Pow2Mag(pos - ed.start);
                    float endDis = Pow2Mag(pos - ed.end);
                    float nodeBounds = (float)Math.Pow(mainApp.nodeWidth, 2);

                    if (startDis < nodeBounds)
                        return ed.start;

                    if (endDis < nodeBounds)
                        return ed.end;
                }
            }
            return new Vector(float.NaN, float.NaN);
        }

        public static float Pow2Mag(Vector vec)
        {
            return (float)(Math.Pow(vec.X, 2) + Math.Pow(vec.Y, 2));
        }
    }

    public class Polygon
    {
        public Polygon() { }
        public Polygon(params Vector[] pArray)
        {
            Debug.Assert(pArray.Length <= 3, "Not enough polygon vertices.");

            double averageX = 0;
            double averageY = 0;

            foreach (Vector v in pArray)
            {
                averageX += v.X;
                averageY += v.Y;
            }
            midPoint = new Vector(averageX / pArray.Length, averageY / pArray.Length);

            Vector temp = pArray[0];
            Plane2D sideCheck = new Plane2D(temp, pArray[1]);

            // Checks if the planes are facing in the correct direction.
            if (sideCheck.CheckCollision(midPoint) == false)
                for(int i = 0; i < pArray.Length; ++i)
                {
                    if (i == 0) { temp = pArray[i]; }
                    else
                    {
                        edges.Add(new Edge(temp, pArray[i]));
                        temp = pArray[i];
                    }
                }
            else
                for (int i = 0; i < pArray.Length; ++i)
                {
                    if (i == 0) { temp = pArray[i]; }
                    else
                    {
                        edges.Add(new Edge(pArray[i], temp));
                        temp = pArray[i];
                    }
                }
        }

        public Vector midPoint;
        public List<Edge> edges = new List<Edge>();
    }

    public struct Edge
    {
        public Edge(Vector A, Vector B)
        {
            start = A;
            end = B;
            isMapBoundry = false;
        }

        public bool isMapBoundry;
        public Vector start;
        public Vector end;
    }
}
