/*
 *	core.h holds physics/mathematics code
 */
#pragma once

#include "./precision.h"
#include <cmath>

namespace physics
{
	/*
	 *	Holds a vector in 3 dimensions. Four data members are allocated
	 *	to ensure alignment in an array (pad). On many machines four-
	 *	floating point values sit more cleanly in memory than 3.
	 *  Using right-handed coordinates for axes.
	 */
	class Vector3
	{
	public:
		/* Holds values along the x, y, and z axis. (Public for efficiency) */
		real x;
		real y;
		real z;

	private:
		// Padding to ensure 4-word alignment.
		real pad;

	public:
		/* Constructor, default creates zero vector */
		Vector3() : x(0), y(0), z(0), pad(0) {}

		/* Explicit Constructor, creates vector with given components */
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z), pad(0) {}

		/* Returns a copy of this vector when added with another vector b */
		Vector3 operator+(const Vector3& b) const
		{
			return Vector3(x + b.x, y + b.y, z + b.z);
		}

		/* Adds this by given vector (b). */
		void operator+=(const Vector3& b)
		{
			x += b.x;
			y += b.y;
			z += b.z;
		}

		/* Returns a copy of this vector when subtracted with another vector b */
		Vector3 operator-(const Vector3& b) const
		{
			return Vector3(x - b.x, y - b.y, z - b.z);
		}

		/* Subtracts this by given vector (b). */
		void operator-=(const Vector3& b)
		{
			x -= b.x;
			y -= b.y;
			z -= b.z;
		}

		/* Returns a copy of this vector scaled to given value */
		Vector3 operator*(const real scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		/*
		 *	(Overload) This returns a copy of the scalar product of
		 *	this vector with the given vector
		 */
		real operator*(const Vector3& vector) const
		{
			return (x * vector.x) + (y * vector.y) + (z * vector.z);
		}

		/* Multiplies this vector by given scalar */
		void operator*=(real scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
		}

		/* Sets all the components to 0 */
		void zero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		/* Flips all the components of the vector. */
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		/* Flips the X component of the vector. */
		void invertX()
		{
			x = -x;
		}

		/* Flips the Y component of the vector. */
		void invertY()
		{
			y = -y;
		}

		/* Gets magnitude of the this vector */
		real magnitude() const
		{
			return real_sqrt(x * x + y * y + z * z);
		}

		/* Gets the squared magnitude of this vector */
		real squareMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		/* Normalizes vector (unit length 1). */
		void normalize()
		{
			real length = magnitude();
			if (length > 0)
			{
				// "this" is a pointer to itself, *this dereferences the pointer
				*this *= ((real)1) / length;
			}
		}

		/*
		 *	Adds the given vector to this.
		 */
		void add(const Vector3& vector)
		{
			x += vector.x;
			y += vector.y;
		}

		/*
		 *	Adds the given vector to this, scaled by the given amount.
		 *	This is useful for some scenarios when you can't trust the
		 *	compiler to do the overide for += correctly (integrating a vector)
		 */
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/*
		 *	Calculates and returns a copy of the component-wise product of this vector
		 *	with the given vector. (not using operator because its not commonly used)
		 */
		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		/* Performs a component-wise product but updates this instead */
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/*
		 *	Calculates and returns a copy of the scalar product of this
		 *	vector with the given vector
		 */
		real scalarProduct(const Vector3& vector) const
		{
			return (x * vector.x) + (y * vector.y) + (z * vector.z);	// ()'s for clairity
		}

		/*
		 *	Calculates and returns a copy of the vector product (or "cross product")
		 *	of this vector with the given vector
		 */
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3((y * vector.z - z * vector.y),
				(z * vector.x - x * vector.z),
				(x * vector.y - y * vector.x));
		}

		/* Performs a vector product but updates this instead */
		void vectorProductUpdate(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}

		/* This will return a direction vector starting at this to another point */
		Vector3 getDirectionVector(const Vector3& vector) const
		{
			Vector3 direction = vector - *this;
			direction.normalize();
			return direction;
		}

		/* Returns the angle in radians */
		float getAngleRadians() const
		{
			return atan2f(y, x);	// atan2f is is arctan which also handles quadrants
		}

		/* Returns distance between 2 points */
		float getDistanceBetween(const Vector3& vector) const
		{
			// Remember the vectors tips/ends are just points (start at 0,0 and goes to tip)
			Vector3 distanceVect = vector - *this;
			return distanceVect.magnitude();
		}
	};
}