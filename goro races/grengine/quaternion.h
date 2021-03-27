#include "vector.h"

class CQuaternion
{
// Attributes
public:
	double w;
	CVector v;

// Functions
public:
	// Equality
	bool const operator==(CQuaternion const &q) const
	{
		return ((w == q.w) && (v == q.v));
	}

	// Inequality
	bool const operator!=(CQuaternion const &q) const
	{
		return !(*this == q);
	}

	// Assignment
	CQuaternion const operator=(CQuaternion const &q)
	{
		w = q.w;
		v = q.v;

		return CQuaternion(*this);
	}

	// Magnitudo
	double const magnitudo(void) const
	{
		return sqrt(w*w + v.x*v.x + v.y*v.y + v.z*v.z);
	}

	// Normalization
	void normalize(void)
	{
		double m_inv = 1 / magnitudo();

		w = w * m_inv;
		v = v * m_inv;
	}

	// Sum
	CQuaternion const operator+(CQuaternion const &q) const
	{
		return CQuaternion(w+q.w, v+q.v);
	}

	// Subtraction
	CQuaternion const operator-(CQuaternion const &q) const
	{
		return CQuaternion(*this+(-q));
	}

	// Add
	CQuaternion const operator+(void) const
	{
		return CQuaternion(*this);
	}
	
	// Negation
	CQuaternion const operator-(void) const
	{
		return CQuaternion(-w, -v);
	}

	// Product
	CQuaternion const operator*(CQuaternion const &q) const
	{
		return CQuaternion((w*q.w) - (v%q.v), (v*q.w) + (w*q.v) + (v^q.v));
	}

	// Returns rotation axis
	CVector const getAxis(void) const
	{
		return v / v.lenght();
	}

	// Returns rotation angle
	double const getAngle(void) const
	{
		return 2 * acos(w);
	}

	// Returns a 3x3 rotation matrix from quaternion values
	void *getMatrix_3x3(double matrix[]) const
	{
		double xx = v.x * v.x;
		double xy = v.x * v.y;
		double xz = v.x * v.z;
		double xw = v.x * w;

		double yy = v.y * v.y;
		double yz = v.y * v.z;
		double yw = v.y * w;

		double zz = v.z * v.z;
		double zw = v.z * w;

		matrix[0] = 1 - 2 * ( yy + zz );
		matrix[1] =     2 * ( xy - zw );
		matrix[2] =     2 * ( xz + yw );

		matrix[3] =     2 * ( xy + zw );
		matrix[4] = 1 - 2 * ( xx + zz );
		matrix[5] =     2 * ( yz - xw );

		matrix[6] =     2 * ( xz - yw );
		matrix[7] =     2 * ( yz + xw );
		matrix[8] = 1 - 2 * ( xx + yy );
	}

	// Returns a 4x4 matrix from quaternion values
	void getMatrix_4x4(double matrix[]) const
	{
		double xx = v.x * v.x;
		double xy = v.x * v.y;
		double xz = v.x * v.z;
		double xw = v.x * w;

		double yy = v.y * v.y;
		double yz = v.y * v.z;
		double yw = v.y * w;

		double zz = v.z * v.z;
		double zw = v.z * w;

		matrix[0]  = 1 - 2 * ( yy + zz );
		matrix[1]  =     2 * ( xy - zw );
		matrix[2]  =     2 * ( xz + yw );

		matrix[4]  =     2 * ( xy + zw );
		matrix[5]  = 1 - 2 * ( xx + zz );
		matrix[6]  =     2 * ( yz - xw );

		matrix[8]  =     2 * ( xz - yw );
		matrix[9]  =     2 * ( yz + xw );
		matrix[10] = 1 - 2 * ( xx + yy );

		matrix[3] = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0;
		matrix[15] = 1;
	}

	// Convert given axis and angle to a normalized quaternion
	void setAxisAngle(double const angle, CVector const &axis)
	{
		w = cos(angle / 2);
		v = sin(angle / 2) * axis;

		normalize();
	}

	void setAxisAngle(double const angle, double const x, double const y, double const z)
	{
		setAxisAngle(angle, CVector(x,y,z));
	}

	// Convert given angle to a normalized quaternion using its current v component
	void setAngle(double const angle)
	{
		w = cos(angle / 2);

		normalize();
	}

// Constructors and destructors
public:
	CQuaternion(void)
	{
		w = 0;
		v = 0;
	}

	CQuaternion(double const w, double const x, double const y, double const z)
	{
		this->w = w;
		this->v = CVector(x,y,z);
	}

	CQuaternion(CQuaternion  const &q)
	{
		w = q.w;
		v = q.v;
	}

	CQuaternion(double const w, CVector const &v)
	{
		this->w = w;
		this->v = v;
	}

	~CQuaternion(void)
	{
	
	}
};