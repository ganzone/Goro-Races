#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>


class CVector
{
// Attributes
public:
	double x;		// X coordinate
	double y;		// Y coordinate
	double z;		// Z coordinate

public:
	// Constructors
	CVector(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	CVector(const CVector &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	// Vector Assignmement
	void set(const CVector &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	// Vector Assignmement
	void set(double const x, double const y, double const z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

		
	// Vector Assignement
	const CVector &operator=(const CVector &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	// Vector Equality
	const bool operator==(const CVector &vec) const
	{
		return ((x == vec.x) && (y == vec.y) && (z == vec.z));
	}

	// Vector Inequality
	const bool operator!=(const CVector &vec) const
	{
		return !(*this == vec);
	}

	// Vector Addition
	const CVector operator+(const CVector &vec) const
	{
		return CVector(x + vec.x, y + vec.y, z + vec.z);
	}

	// Vector Add
	const CVector operator+() const
	{
		return CVector(*this);
	}

	// Vector Increment
	const CVector &operator+=(const CVector &vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	// Vector Subtraction
	const CVector operator-(const CVector &vec) const
	{
		return CVector(x - vec.x, y - vec.y, z - vec.z);
	}

	// Vector Negation
	const CVector operator-() const
	{
		return CVector(-x, -y, -z);
	}

	// Vector Decrement
	const CVector &operator-=(const CVector &vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	// Scalar Multiply
	const CVector &operator*=(const double &s)
	{
		x *= s;
		y *= s;
		z *= z;

		return *this;
	}

	// Scalar Division
	const CVector &operator/=(const double &s)
	{
		const double recip = 1/s;

		x *= recip;
		y *= recip;
		z *= recip;

		return *this;
	}

	// Post Multiply by Scalar
	const CVector operator*(const double &s) const
	{
		return CVector(x*s, y*s, z*s);
	}

	// Pre Multiply by Scalar
	friend inline const CVector operator*(const double &s, const CVector &vec)
	{
		return vec*s;
	}

	// Divide by Scalar
	const CVector operator/(double s) const
	{
		s = 1/s;

		return CVector(s*x, s*y, s*z);
	}

	// Cross Product of This Vector and vec
	const CVector crossProduct(const CVector &vec) const
	{
		return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// Cross Product
	const CVector operator^(const CVector &vec) const
	{
		return crossProduct(vec);
	}

	// Dot Product
	const double dotProduct(const CVector &vec) const
	{
		return x*vec.x + y*vec.y + z*vec.z;
	}

	// Dot Product
	const double operator%(const CVector &vec) const
	{
		return dotProduct(vec);
	}

	// Lenght of Vector
	const double lenght(void) const
	{
		return (double) sqrt ((double) (x*x + y*y + z*z));
	}

	// Vector Lenght
	const double operator!(void) const
	{
		return lenght();
	}

	// Unit Vector
	const CVector unitVector(void) const
	{
		return (*this) / lenght();
	}

	// Normalize this Vector
	void normalize(void)
	{
		(*this) /= lenght();
	}

	// Return this Vector with Specified Lenght
	const CVector operator|(const double lenght) const
	{
		return (*this) * (lenght / (!(*this)));
	}

	// Set Lenght of Vector Equal to Lenght
	const CVector &operator|=(const double lenght)
	{
		return *this = *this | lenght;
	}

	// Return Angle Between this Vector and a Normal Vector
	const double angle(const CVector &normal) const
	{
		return acos(*this % normal);
	}

	// Reflect this Vector About a Normal Vector
	const CVector reflection(const CVector &normal) const
	{
		const CVector vec(*this | 1);
		return (vec - normal * 2.0 * (vec % normal)) * !*this;
	}
};


#endif // _VECTOR_H