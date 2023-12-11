#pragma once
#include <cmath>
#include <iostream>
/* 

Because the glm library cannot be used for this assignment, you have been provided a start to a Vec3 class. You can use and edit this however you wish. Feel free to use your own style if you would rather not use the one below.

Make sure to #include "Vec3.h" to use this in other classes if needed.

Other operators you might need:
*	operator- to times x, y and z by a minus
*	operator/ to divide the vector by a float
*	Magnitude - return the length of a vector
*	Normalize - return a vector of length 1 but pointing in the same direction
*	Dot Product
*	Cross Product
*   operator*=, /=, +=, -= for ease of use
*/

class Vec3
{
public:
	float x, y, z;

	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	Vec3(const float x, const float y, const float z) :
		x(x), y(y), z(z)
	{};

	~Vec3() {};
	Vec3 operator=(const Vec3& b);
	Vec3 operator+=(const Vec3& b);
	Vec3 operator-=(const Vec3& b);
	Vec3 operator*=(float s);
	Vec3 operator/=(float s);

	
};

inline Vec3 Vec3::operator=(const Vec3& b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
	return *this;
}



inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(const Vec3& a, float s)
{
	return Vec3(a.x * s, a.y * s, a.z * s);
}

inline Vec3 operator /(const Vec3& a, float s)
{
	if (s != 0)
	{
		return Vec3(a.x / s, a.y / s, a.z / s);
	}
	else
	{
		return Vec3(a.x, a.y, a.z);
	}
}

inline Vec3 Vec3::operator+=(const Vec3& b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;
	return (*this);
}

inline Vec3 Vec3::operator-=(const Vec3& b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;
	return (*this);
}

inline Vec3 Vec3::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return (*this);
}

inline Vec3 Vec3::operator/=(float s)
{
	if (s != 0)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		return (*this);
	}
	else
	{
		return (*this);
	}
	
}




inline Vec3 Minus(const Vec3& a, float s)
{
	return Vec3(a.x * -s, a.y * -s, a.z * -s);
}

inline float Magnitude(const Vec3& a) // vector's magnitude
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline Vec3 Normalization(const Vec3& a) // make magnitude as 1, want to know only direction of vector
{
	float magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	if (magnitude > 0)
	{
		return Vec3(a.x / magnitude, a.y / magnitude, a.z / magnitude);
	}
}

inline float Dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);

}
inline Vec3 MatCalculate(const float a[3][3], const Vec3& b)	// Multiplication of matrix and vector
{

	return Vec3
	( 
		a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z,
		a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z,
		a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z
	);
}

inline float Radian(float orientation)
{
	float pi = 3.141592f;
	return (orientation * (pi / 180));
}

inline Vec3 MatInverse(const float a[3][3], const Vec3& b)	// Multiplication of inverse matrix and vector
{
	
	

	float determine = 
		 a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1]) 
		-a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
		+a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

	if (determine == 0)
	{
		std::cout << "matrix determine is 0" << std::endl;
	}

	float temp[3][3];

	temp[0][0] = (a[1][1] * a[2][2] - a[1][2] * a[2][1]);
	temp[0][1] = -(a[1][0] * a[2][2] - a[1][2] * a[2][0]);
	temp[0][2] = (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

	temp[1][0] = -(a[0][1] * a[2][2] - a[0][2] * a[2][1]);
	temp[1][1] = (a[0][0] * a[2][2] - a[0][2] * a[2][0]);
	temp[1][2] = -(a[0][0] * a[2][1] - a[0][1] * a[2][0]);

	temp[2][0] = (a[0][1] * a[1][2] - a[0][2] * a[1][1]);
	temp[2][1] = -(a[0][0] * a[1][2] - a[0][2] * a[1][0]);
	temp[2][2] = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);

	float result[3][3];

	result[0][0] = temp[0][0] / determine;
	result[0][1] = temp[1][0] / determine;
	result[0][2] = temp[2][0] / determine;
	
	result[1][0] = temp[0][1] / determine;
	result[1][1] = temp[1][1] / determine;
	result[1][2] = temp[2][1] / determine;

	result[2][0] = temp[0][2] / determine;
	result[2][1] = temp[1][2] / determine;
	result[2][2] = temp[2][2] / determine;

	Vec3 InversMultVec = MatCalculate(result, b);

	return InversMultVec;


}

