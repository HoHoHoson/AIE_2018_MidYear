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
        public List<Vector> TempNodes { get; set; } = new List<Vector>();
        [XmlIgnore]
        public static bool polyPositive = true;

        public void VectorInput(Vector mousePos)
        {
            if (DoesExist(mousePos) == true)
                selectedNode = GetNode(mousePos);
            else
            {
                if (IsValidNode(mousePos) == false)
                    return;

                selectedNode = mousePos;

                TempNodes.Add(selectedNode);
                ValidatePoly();

                return;
            }

            // Checks if the Polygon is complete
            if (TempNodes.Count >= 3 && selectedNode == TempNodes.ElementAt(0))
            {
                int currentNum = TempNodes.Count;

                ValidatePoly(true);
                if (currentNum != TempNodes.Count)
                    return;

                polygons.Add(new Polygon(TempNodes.ToArray()));
                TempNodes.Clear();
                selectedNode = new Vector(double.NaN, double.NaN);
                return;
            }

            // Checks if the current Polygon is invalid
            foreach(Vector node in TempNodes)
                if (selectedNode == node)
                {
                    MessageBox.Show("The points must form a complete loop.", "Invalid Edge");
                    selectedNode = TempNodes.ElementAt(TempNodes.Count - 1);
                    return;
                }
            
            TempNodes.Add(selectedNode);
        }



        // Checks if the polygon is convex
        private void ValidatePoly(bool IsComplete = false)
        {
            if (TempNodes.Count >= 3)
            {
                int tail = TempNodes.Count - 1;
                Vector cur = TempNodes.ElementAt(tail) - TempNodes.ElementAt(tail - 1);
                Vector prev = TempNodes.ElementAt(tail - 1) - TempNodes.ElementAt(tail - 2);

                float crossProduct = (float)(prev.X * cur.Y - prev.Y * cur.X);

                if (crossProduct == 0)
                {
                    TempNodes.RemoveAt(tail - 1);
                    return;
                }

                if (TempNodes.Count == 3)
                {
                    Vector checkPoint = new Vector((TempNodes.ElementAt(0).X + TempNodes.ElementAt(1).X + TempNodes.ElementAt(2).X) / 3,
                                                   (TempNodes.ElementAt(0).Y + TempNodes.ElementAt(1).Y + TempNodes.ElementAt(2).Y) / 3);
                    Plane2D plane = new Plane2D(TempNodes.ElementAt(0), TempNodes.ElementAt(1));

                    if (plane.CheckCollision(checkPoint) == true)
                        polyPositive = false;
                    else
                        polyPositive = true;
                }

                //List<Plane2D> PolyEdges = new List<Plane2D>();

                //for (int i = 0; i < tail; ++i)
                //    PolyEdges.Add(new Plane2D(TempNodes.ElementAt(i), TempNodes.ElementAt(i + 1)));
                //PolyEdges.Add(new Plane2D(TempNodes.ElementAt(tail), TempNodes.ElementAt(0)));

                //foreach (Polygon p in polygons)
                //    foreach (Edge ed in p.edges)
                //    {
                //        int startCount = PolyEdges.Count;
                //        int endCount = PolyEdges.Count;

                //        foreach (Plane2D pl in PolyEdges)
                //        {
                //            if (pl.CheckCollision(ed.start) == false)
                //                startCount--;
                //            if (startCount == 0)
                //            {
                //                TempNodes.RemoveAt(tail - 1);
                //                selectedNode = TempNodes.ElementAt(tail - 1);

                //                MessageBox.Show("The polygon was going to overlap another.", "Invalid Edge");
                //                break;
                //            }
                //        }

                //        foreach (Plane2D pl in PolyEdges)
                //        {
                //            if (pl.CheckCollision(ed.end) == false)
                //                endCount--;
                //            if (endCount == 0)
                //            {
                //                TempNodes.RemoveAt(tail - 1);
                //                selectedNode = TempNodes.ElementAt(tail - 1);

                //                MessageBox.Show("The polygon was going to overlap another.", "Invalid Edge");
                //                break;
                //            }
                //        }
                //    }

                // Checks if Polygon is convex by comparing the other temp nodes.
                Plane2D checkPlane;
                if (IsComplete == false)
                {
                    if (polyPositive == true)
                        checkPlane = new Plane2D(TempNodes.ElementAt(tail - 1), TempNodes.ElementAt(tail));
                    else
                        checkPlane = new Plane2D(TempNodes.ElementAt(tail), TempNodes.ElementAt(tail - 1));

                    for (int i = 0; i < tail - 1; ++i)
                    {
                        if (checkPlane.CheckCollision(TempNodes.ElementAt(i)) == true)
                        {
                            TempNodes.RemoveAt(tail);
                            selectedNode = TempNodes.ElementAt(tail - 1);

                            MessageBox.Show("Polygon needs to be convex.", "Invalid edge");
                            break;
                        }   
                    }
                }
                else
                {
                    if (polyPositive == true)
                        checkPlane = new Plane2D(TempNodes.ElementAt(tail), TempNodes.ElementAt(0));
                    else
                        checkPlane = new Plane2D(TempNodes.ElementAt(0), TempNodes.ElementAt(tail));

                    for (int i = 1; i < tail; ++i)
                    {
                        if (checkPlane.CheckCollision(TempNodes.ElementAt(i)) == true)
                        {
                            TempNodes.RemoveAt(tail);
                            selectedNode = TempNodes.ElementAt(tail - 1);

                            MessageBox.Show("Polygon needs to be convex.", "Invalid edge");
                            break;
                        }
                    }
                }
                
            }
        }



        private bool DoesExist(Vector mousePos)
        {
            Vector v = GetNode(mousePos);

            if (double.IsNaN(v.X) || double.IsNaN(v.Y))
                return false;
            else
                return true;
        }



        // Pass in a node to process it into the NavMesh.
        private Vector GetNode(Vector pos)
        {
            float nodeBoundSqr = (float)Math.Pow(MainApp.nodeDiameter, 2);

            foreach (Polygon poly in polygons)
            {
                foreach (Edge ed in poly.edges)
                {
                    float startDis = (float)(pos - ed.start).LengthSquared;
                    float endDis = (float)(pos - ed.end).LengthSquared;

                    if (startDis <= nodeBoundSqr)
                        return ed.start;

                    if (endDis <= nodeBoundSqr)
                        return ed.end;
                }
            }

            foreach (Vector vec in TempNodes)
            {
                float distance = (float)(pos - vec).LengthSquared;

                if (distance <= nodeBoundSqr)
                    return vec;
            }

            return new Vector(float.NaN, float.NaN);
        }



        private bool IsValidNode(Vector nodePos)
        {
            foreach (Polygon poly in polygons)
            {
                int collisionCount = 0;

                foreach (Edge ed in poly.edges)
                {
                    Plane2D polyBounds = new Plane2D(ed.start, ed.end);

                    if (TempNodes.Count != 0)
                    {
                        Vector tailNode = TempNodes.ElementAt(TempNodes.Count - 1);
                        float length = (float)(tailNode - nodePos).Length;
                        Ray2D rayCheck = new Ray2D(tailNode, nodePos, length);
                        Ray2D edgeRay = new Ray2D(ed.start, ed.end, (float)(ed.end - ed.start).Length);

                        if (edgeRay.CheckCollision(rayCheck) == true)
                        {
                            MessageBox.Show("Edge intersects with an existing Polygon.", "Invalid Edge");
                            return false;
                        }
                    }
                    else if (polyBounds.CheckCollision(nodePos) == false)
                    {
                        collisionCount++;
                        if (poly.edges.Count == collisionCount)
                        {
                            MessageBox.Show("Node can not be created inside an existing Polygon.", "Invalid Node");
                            return false;
                        }
                    }
                }
            }

            return true;
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
            if (sideCheck.CheckCollision(midPoint) == true)
                Array.Reverse(pArray);

            for (int i = 0; i < pArray.Length; ++i)
            {
                if (i == pArray.Length - 1)
                    edges.Add(new Edge(pArray[i], pArray[0]));
                else
                    edges.Add(new Edge(pArray[i], pArray[i + 1]));
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
