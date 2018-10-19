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

        public bool CheckCollision(Ray2D ray)
        {
            double denominator = ((End.X - Origin.X) * (ray.End.Y - ray.Origin.Y)) - ((End.Y - Origin.Y) * (ray.End.X - ray.Origin.X));
            double numerator1 = ((Origin.Y - ray.Origin.Y) * (ray.End.X - ray.Origin.X)) - ((Origin.X - ray.Origin.X) * (ray.End.Y - ray.Origin.Y));
            double numerator2 = ((Origin.Y - ray.Origin.Y) * (End.X - Origin.X)) - ((Origin.X - ray.Origin.X) * (End.X - Origin.Y));

	        if (denominator == 0) 
		        return (numerator1 == 0 && numerator2 == 0);

	        double r = numerator1 / denominator;
            double s = numerator2 / denominator;

	        return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
        }
    };
}

