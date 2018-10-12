using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace NavMesh_Editor
{
    class Plane2D
    {
        /// <summary>
        /// The normal is perpendicular and moves outwards from the left side of this line, it indicates the safe side of the plane check.
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        public Plane2D(Vector from, Vector to)
        {
            Vector temp = new Vector(to.X - from.X, to.Y - from.Y);
            temp.Normalize();
            Debug.Assert(double.IsNaN(temp.X) == false && double.IsNaN(temp.Y) == false, "Can't create a Plane2D with only one point.");

            normal = new Vector(-temp.Y, temp.X);
            scalar = (float)Vector.Multiply(temp, normal);
        }

        public float scalar { get; private set; }
        public Vector normal { get; private set; }

        public bool CheckCollision(Vector point)
        {
            return (DistanceTo(point) <= 0);
        }

        private float DistanceTo(Vector other)
        {
            return (float)(Vector.Multiply(other, normal) - scalar);
        }
    };
}
