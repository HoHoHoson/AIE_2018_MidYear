using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace NavMesh_Editor
{
    public class Polygon
    {
        public Polygon() { }
        public Polygon(params Vector[] pArray)
        {
            Debug.Assert(pArray.Length >= 3, "Not enough polygon vertices.");

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
