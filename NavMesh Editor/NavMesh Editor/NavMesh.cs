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
        public Vector nodeSelect { get; private set; }
        [XmlIgnore]
        public List<Vector> tempNodes { get; private set; } = new List<Vector>();
        [XmlIgnore]
        public static bool polyPositive = true;
        private Vector originNode;



        /// <summary>
        /// Processes a Vector that was selected by the user.
        /// </summary>
        /// <param name="mousePos"></param>
        public void VectorInput(Vector mousePos)
        {
            // Sets the first node as the origin node.
            if (tempNodes.Count == 1)
                originNode = tempNodes.ElementAt(0);

            // Detects if the user has selected an existing node.
            if (DoesExist(mousePos) == true)
            {
                nodeSelect = GetNode(mousePos);

                // Checks if the polygon is self intersecting.
                foreach (Vector node in tempNodes)
                    if (nodeSelect == node && nodeSelect != originNode || nodeSelect == originNode && tempNodes.Count < 3)
                    {
                        nodeSelect = tempNodes.ElementAt(tempNodes.Count - 1);
                        MessageBox.Show("The points must form a complete polygon.", "Invalid Edge");
                        return;
                    }
            }
            else
            {
                nodeSelect = mousePos;

                if (IsValidNode(mousePos) == false)
                    return;
            }
            ValidatePoly();
        }



        /// <summary>
        /// Undos the last node that was added.
        /// </summary>
        public void UndoPrevNode()
        {
            if (tempNodes.Count == 0)
                return;

            tempNodes.RemoveAt(tempNodes.Count - 1);

            if (tempNodes.Count == 0)
                nodeSelect = new Vector(double.NaN, 0);
            else
                nodeSelect = tempNodes.ElementAt(tempNodes.Count - 1);
        }



        public void ClearSelected()
        {
            tempNodes.Clear();
            nodeSelect = new Vector(double.NaN, 0);
        }



        /// <summary>
        /// Checks that the polygon being made is valid.  
        /// </summary>
        private void ValidatePoly()
        {
            if (tempNodes.Count >= 2)
            {
                // Checks if the polygon will overlap another.
                List<Vector> tempArray = new List<Vector>(tempNodes);
                if (nodeSelect != originNode)
                    tempArray.Add(nodeSelect);

                Vector checkPoint = new Vector((tempArray.ElementAt(0).X + tempArray.ElementAt(1).X + tempArray.ElementAt(2).X) / 3,
                                (tempArray.ElementAt(0).Y + tempArray.ElementAt(1).Y + tempArray.ElementAt(2).Y) / 3);
                Plane2D plane = new Plane2D(tempArray.ElementAt(0), tempArray.ElementAt(1));

                if (plane.CheckCollision(checkPoint) == true)
                    tempArray.Reverse();

                List<Plane2D> tempPlanes = new List<Plane2D>();
                for (int i = 0; i < tempArray.Count; ++i)
                {
                    if (i == tempArray.Count - 1)
                        tempPlanes.Add(new Plane2D(tempArray[i], tempArray[0]));
                    else
                        tempPlanes.Add(new Plane2D(tempArray[i], tempArray[i + 1]));
                }

                List<Vector> vSet = new List<Vector>();

                foreach (Polygon p in polygons)
                    foreach (Edge ed in p.edges)
                        vSet.Add(ed.start);

                foreach (Vector v in vSet)
                {
                    bool isValid = false;

                    foreach (Plane2D pl in tempPlanes)
                    {
                        if (tempArray.Any(vec => vec == v) == true || pl.CheckCollision(v) == true)
                            isValid = true;
                    }

                    if (isValid == false)
                    {
                        nodeSelect = tempNodes.ElementAt(tempNodes.Count - 1);
                        MessageBox.Show("The polygon will overlap with another.", "Invalid edge");

                        return;
                    }
                }
            }

            if (tempNodes.Count < 3)
            {
                tempNodes.Add(nodeSelect);
                return;
            }

            int tailNode = tempNodes.Count - 1;

            if (tempNodes.Count == 3)
            {
                Vector checkPoint = new Vector((tempNodes.ElementAt(0).X + tempNodes.ElementAt(1).X + tempNodes.ElementAt(2).X) / 3,
                                                (tempNodes.ElementAt(0).Y + tempNodes.ElementAt(1).Y + tempNodes.ElementAt(2).Y) / 3);
                Plane2D plane = new Plane2D(tempNodes.ElementAt(0), tempNodes.ElementAt(1));

                if (plane.CheckCollision(checkPoint) == true)
                    polyPositive = false;
                else
                    polyPositive = true;
            }

            // Checks if Polygon is convex by comparing with the other temp nodes.
            Plane2D checkPlane;
            if (nodeSelect != originNode)
            {
                if (polyPositive == true)
                    checkPlane = new Plane2D(tempNodes.ElementAt(tailNode), nodeSelect);
                else
                    checkPlane = new Plane2D(nodeSelect, tempNodes.ElementAt(tailNode));

                for (int i = 0; i < tailNode - 1; ++i)
                {
                    if (checkPlane.CheckCollision(tempNodes.ElementAt(i)) == true)
                    {
                        nodeSelect = tempNodes.ElementAt(tailNode);
                        MessageBox.Show("Polygon needs to be convex.", "Invalid edge");

                        return;
                    }
                }
            }
            else
            {
                if (polyPositive == true)
                    checkPlane = new Plane2D(tempNodes.ElementAt(tailNode), nodeSelect);
                else
                    checkPlane = new Plane2D(nodeSelect, tempNodes.ElementAt(tailNode));

                for (int i = 1; i < tailNode; ++i)
                {
                    if (checkPlane.CheckCollision(tempNodes.ElementAt(i)) == true)
                    {
                        tempNodes.RemoveAt(tailNode);
                        nodeSelect = tempNodes.ElementAt(tailNode - 1);
                        MessageBox.Show("Polygon needs to be convex.", "Invalid edge");

                        return;
                    }
                }
            }

            // Adds selected node if it passes all the validation checks.
            if (nodeSelect != originNode)
                tempNodes.Add(nodeSelect);

            // Removes uneeded nodes that were inlined with the current node.
            Vector cur = tempNodes.ElementAt(tailNode) - tempNodes.ElementAt(tailNode - 1);
            Vector prev = tempNodes.ElementAt(tailNode - 1) - tempNodes.ElementAt(tailNode - 2);
            float crossProduct = (float)(prev.X * cur.Y - prev.Y * cur.X);

            if (crossProduct == 0)
                tempNodes.RemoveAt(tailNode - 1);

            // One last check to see if the polygon already exists. Then stores the polygon once it is complete.
            if (tempNodes.Count >= 3 && nodeSelect == originNode)
            {
                foreach (Polygon p in polygons)
                {
                    int edgeCount = p.edges.Count;

                    for (int i = 0; i < p.edges.Count; ++i)
                        foreach (Vector v in tempNodes)
                            if (v == p.edges.ElementAt(i).start)
                            {
                                edgeCount--;
                                if (edgeCount == 0)
                                {
                                    originNode = new Vector(double.NaN, double.NaN);
                                    nodeSelect = new Vector(double.NaN, double.NaN);
                                    tempNodes.Clear();
                                    polyPositive = true;

                                    MessageBox.Show("Polygon is a duplicate and/or overlaps another.", "Invalid Polygon");

                                    return;
                                }
                            }
                }

                var nodeArray = tempNodes.ToArray();

                if (polyPositive == false)
                    Array.Reverse(nodeArray);

                polygons.Add(new Polygon(nodeArray));

                originNode = new Vector(double.NaN, double.NaN);
                nodeSelect = new Vector(double.NaN, double.NaN);
                tempNodes.Clear();
                polyPositive = true;
            }
        }



        /// <summary>
        /// Returns true if the user selects an existing mesh node.
        /// </summary>
        /// <param name="mousePos"></param>
        /// <returns></returns>
        private bool DoesExist(Vector mousePos)
        {
            Vector v = GetNode(mousePos);

            if (double.IsNaN(v.X) || double.IsNaN(v.Y))
                return false;
            else
                return true;
        }



        /// <summary>
        /// Gets the node that was selected by the user.
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        private Vector GetNode(Vector pos)
        {
            float nodeBoundSqr = (float)Math.Pow(MainApp.nodeDiameter, 2);

            foreach (Polygon poly in polygons)
            {
                foreach (Edge ed in poly.edges)
                {
                    float startDis = (float)(pos - ed.start).LengthSquared;

                    if (startDis <= nodeBoundSqr)
                        return ed.start;
                }
            }

            foreach (Vector vec in tempNodes)
            {
                float distance = (float)(pos - vec).LengthSquared;

                if (distance <= nodeBoundSqr)
                    return vec;
            }

            return new Vector(float.NaN, float.NaN);
        }



        /// <summary>
        /// Checks if the inputed node is valid, returns false if not.
        /// </summary>
        /// <param name="nodePos"></param>
        /// <returns></returns>
        private bool IsValidNode(Vector nodePos)
        {
            // Checks if the node is inside any existing polygons.
            List<Plane2D> polyChecks = new List<Plane2D>();
            foreach (Polygon poly in polygons)
            {
                bool isValid = false;
                polyChecks.Clear();

                foreach (Edge ed in poly.edges)
                    polyChecks.Add(new Plane2D(ed.start, ed.end));

                foreach (Plane2D plane in polyChecks)
                    if (plane.CheckCollision(nodePos) == true)
                        isValid = true;

                if (isValid == false)
                {
                    nodeSelect = new Vector(double.NaN, double.NaN);
                    MessageBox.Show("Node can not be created inside an existing Polygon.", "Invalid Node");
                    return false;
                }
            }

            // Checks if the edge created by the new node intersects with any existing polygons.
            if (tempNodes.Count != 0)
            {
                bool prevExist = false;
                Vector tailVec = tempNodes.ElementAt(tempNodes.Count - 1);

                if (DoesExist(tailVec) == true)
                    prevExist = true;

                float length = (float)(nodeSelect - tailVec).Length;
                Ray2D rayCheck = new Ray2D(tailVec, nodeSelect, length);
                
                foreach (Polygon p in polygons)
                    foreach (Edge ed in p.edges)
                    {
                        if (prevExist == false || prevExist == true && ed.start != tailVec && ed.end != tailVec)
                        {
                            Ray2D edgeRay = new Ray2D(ed.start, ed.end, (float)(ed.end - ed.start).Length);

                            if (rayCheck.CheckCollision(edgeRay) == true)
                            {
                                nodeSelect = tailVec;
                                MessageBox.Show("Edge intersects with an existing Polygon.", "Invalid Edge");
                                return false;
                            }
                        }
                    }
            }

            return true;
        }
    }
}
