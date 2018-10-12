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
        List<Polygon> polygons;
    }

    class Polygon
    {
        Polygon() { }
        Polygon(params Vector[] pArray)
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

        public Vector midPoint { get; private set; }
        public List<Edge> edges { get; private set; }
    }

    struct Edge
    {
        public Edge(Vector A, Vector B)
        {
            start = A;
            end = B;
            isMapBoundry = false;
        }

        public bool isMapBoundry { get; set; }
        public Vector start { get; private set; }
        public Vector end { get; private set; }
    }
}
