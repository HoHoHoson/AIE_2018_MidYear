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
            Origin = from;
            End = to;

            Vector temp = new Vector(to.X - from.X, to.Y - from.Y);
            temp.Normalize();
            Debug.Assert(double.IsNaN(temp.X) == false && double.IsNaN(temp.Y) == false, "Can't create a Plane2D with only one point.");

            Normal = new Vector(-temp.Y, temp.X);
            Scalar = (float)Vector.Multiply(-from, Normal);
        }

        public float Scalar { get; private set; }
        public Vector Normal { get; private set; }
        private Vector Origin;
        private Vector End;

        /// <summary>
        /// Returns true if the point is either on the plane, or on the right side of it.
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public bool CheckCollision(Vector point)
        {
            return (DistanceTo(point) <= 0);
        }

        public bool CheckCollision(Ray2D ray)
        {
            return ray.CheckCollision(this);
        }

        public float DistanceTo(Vector other)
        {
            float distance = (float)(Vector.Multiply(other, Normal) + Scalar);
            return distance;
        }
    };


    class Ray2D
    {
        public Ray2D(Vector orgin, Vector dest, float length = float.PositiveInfinity)
        {
            Origin = orgin;
            Length = length;

            Direction = dest - orgin;
            Direction.Normalize();

            End = Origin + Direction * Length;
        }

        Vector Origin;
        Vector End;
        Vector Direction;
        float Length;

        public bool CheckCollision(Plane2D p)
        {
            float dir = (float)Vector.Multiply(Direction, p.Normal);
            float dis = p.DistanceTo(Origin);

            if (dis == 0)
                return true;

            if (dir >= 0)
                return false;

            float actualLength = -(dis / dir);

            if (actualLength > Length)
                return false;
            else
                return true;
        }

        public bool CheckCollision(Ray2D r)
        {
            Vector end1 = Origin + Direction * Length;
            Vector end2 = r.Origin + r.Direction * r.Length;
            // Ray 1 
            float A1 = (float)(end1.Y - Origin.Y);
            float B1 = (float)(Origin.X - end1.X);
            float C1 = (float)(A1 * Origin.X + B1 * Origin.Y);
            // Ray 2
            float A2 = (float)(end2.Y - r.Origin.Y);
            float B2 = (float)(r.Origin.X - end2.X);
            float C2 = (float)(A2 * r.Origin.X + B2 * r.Origin.Y);

            float det = A1 * B2 - A2 * B1;

            // Lines are parallel
            if (det == 0)
                return false;

            Vector intersect = new Vector((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);

            if (Math.Min(Origin.X, end1.X) <= intersect.X && intersect.X <= Math.Max(Origin.X, end1.X) &&
                Math.Min(Origin.Y, end1.Y) <= intersect.Y && intersect.Y <= Math.Max(Origin.Y, end1.Y))
                if (Math.Min(r.Origin.X, end2.X) <= intersect.X && intersect.X <= Math.Max(r.Origin.X, end2.X) &&
                    Math.Min(r.Origin.Y, end2.Y) <= intersect.Y && intersect.Y <= Math.Max(r.Origin.Y, end2.Y))
                    return true;

            return false;
        }
    };
}

