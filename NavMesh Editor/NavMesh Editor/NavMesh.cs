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
        public List<Polygon> polygons = new List<Polygon>();

        [XmlIgnore]
        public Vector selectedNode { get; private set; }
        [XmlIgnore]
        public List<Vector> storedVertices { get; set; } = new List<Vector>();
        private bool polyPositive = true;

        public void NodeInput(Vector mousePos)
        {
            if (DoesExist(mousePos))
                selectedNode = GetNode(mousePos);
            else
            {
                selectedNode = mousePos;

                storedVertices.Add(selectedNode);
                ValidatePoly();

                return;
            }

            // Checks if the Polygon is complete
            if (storedVertices.Count >= 3 && selectedNode == storedVertices.ElementAt(0))
            {
                polygons.Add(new Polygon(storedVertices.ToArray()));
                storedVertices.Clear();
                selectedNode = new Vector(double.NaN, double.NaN);
                return;
            }

            // Checks if the current Polygon is invalid
            foreach(Vector node in storedVertices)
                if (selectedNode == node)
                {
                    MessageBox.Show("The points must form a complete loop.", "Invalid edge");
                    selectedNode = storedVertices.ElementAt(storedVertices.Count - 1);
                    return;
                }
            
            storedVertices.Add(selectedNode);
        }

        // Pass in a node to process it into the NavMesh.
        private Vector GetNode(Vector pos)
        {
            float nodeBounds = (float)Math.Pow(MainApp.nodeDiameter, 2);

            foreach (Polygon poly in polygons)
            {
                foreach(Edge ed in poly.edges)
                {
                    float startDis = (float)(pos - ed.start).LengthSquared;
                    float endDis = (float)(pos - ed.end).LengthSquared;

                    if (startDis <= nodeBounds)
                        return ed.start;

                    if (endDis <= nodeBounds)
                        return ed.end;
                }
            }

            foreach(Vector vec in storedVertices)
            {
                float distance = (float)(pos - vec).LengthSquared;

                if (distance <= nodeBounds)
                    return vec;
            }

            return new Vector(float.NaN, float.NaN);
        }

        private bool DoesExist(Vector mousePos)
        {
            Vector v = GetNode(mousePos);

            if (double.IsNaN(v.X) || double.IsNaN(v.Y))
                return false;
            else
                return true;
        }

        private void ValidatePoly()
        {
            if (storedVertices.Count >= 3)
            {
                int tail = storedVertices.Count - 1;
                Vector cur = storedVertices.ElementAt(tail) - storedVertices.ElementAt(tail - 1);
                Vector prev = storedVertices.ElementAt(tail - 1) - storedVertices.ElementAt(tail - 2);

                float crossProduct = (float)(prev.X * cur.Y - prev.Y * cur.X);

                if (crossProduct == 0)
                {
                    storedVertices.RemoveAt(tail - 1);
                    return;
                }

                if (storedVertices.Count == 3)
                {
                    Vector checkPoint = new Vector((storedVertices.ElementAt(0).X + storedVertices.ElementAt(1).X + storedVertices.ElementAt(2).X) / 3,
                                                   (storedVertices.ElementAt(0).Y + storedVertices.ElementAt(1).Y + storedVertices.ElementAt(2).Y) / 3);
                    Plane2D checkPlane = new Plane2D(storedVertices.ElementAt(0), storedVertices.ElementAt(1));

                    if (checkPlane.IsOutBounds(checkPoint) == true)
                        polyPositive = false;
                    else
                        polyPositive = true;
                }
                else
                {
                    Plane2D checkPlane;

                    if (polyPositive == true)
                        checkPlane = new Plane2D(storedVertices.ElementAt(tail - 1), storedVertices.ElementAt(tail));
                    else
                        checkPlane = new Plane2D(storedVertices.ElementAt(tail), storedVertices.ElementAt(tail - 1));

                    for (int i = 0; i < tail - 1; ++i)
                    {
                        if (checkPlane.IsOutBounds(storedVertices.ElementAt(i)) == true)
                        {
                            storedVertices.RemoveAt(tail);
                            selectedNode = storedVertices.ElementAt(tail - 1);

                            MessageBox.Show("Polygon needs to be convex.", "Invalid edge");
                            break;
                        }   
                    }
                }
            }
        }
    }

    public class Polygon
    {
        public Polygon() { }
        public Polygon(params Vector[] pArray)
        {
            Debug.Assert(pArray.Length >= 3, "Not enough polygon vertices.");

            Vector midPoint = new Vector((pArray[0].X + pArray[1].X + pArray[2].X) / 3, (pArray[0].Y + pArray[1].Y + pArray[2].Y) / 3);

            Plane2D sideCheck = new Plane2D(pArray[0], pArray[1]);

            // Checks if the planes are facing in the correct direction.
            if (sideCheck.IsOutBounds(midPoint) == false)
                for (int i = 0; i < pArray.Length; ++i)
                {
                    if (i == pArray.Length - 1)
                        edges.Add(new Edge(pArray[i], pArray[0]));
                    else
                        edges.Add(new Edge(pArray[i], pArray[i + 1])); 
                }
            else
                for (int i = 0; i < pArray.Length; ++i)
                {
                    if (i == pArray.Length - 1)
                        edges.Add(new Edge(pArray[i], pArray[0]));
                    else
                        edges.Add(new Edge(pArray[i + 1], pArray[i]));
                }
        }

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
