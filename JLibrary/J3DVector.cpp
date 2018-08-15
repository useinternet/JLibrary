#include "J3DVector.h"
#include "JMath.h"


/** 생성자 및 소멸자 */
J3DVector::J3DVector() : x(0),y(0),z(0) {}
J3DVector::J3DVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
J3DVector::J3DVector(const J3DVector& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}
J3DVector::~J3DVector() {}

/** 길이 및 내적, 각종 연산 */
float J3DVector::Length() const
{
	return JMath::Sqrt(x * x + y * y + z * z);
}
float J3DVector::LengthSquared() const
{
	return x * x + y * y + z * z;
}
J3DVector& J3DVector::Normalize()
{
	float LengthSqrd = x * x + y * y + z * z;
	if (JMath::IsZero(LengthSqrd))
	{
		x = 0.0f; y = 0.0f; z = 0.0f;
		return *this;
	}

	float InverseLengthSqrd = 1 / JMath::Sqrt(LengthSqrd);

	x *= InverseLengthSqrd;
	y *= InverseLengthSqrd;
	z *= InverseLengthSqrd;

	return *this;
}
J3DVector J3DVector::Cross(const J3DVector& vector)
{
	return J3DVector((y * vector.z) - (z* vector.y),
		(z * vector.x) - (x * vector.z), (x * vector.y) - (y * vector.x));
}
float J3DVector::Dot(const J3DVector& vector)
{
	return x * vector.x + y * vector.y + z * vector.z;
}


/** 연산자 오버로딩 */
J3DVector& J3DVector::operator=(const J3DVector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}
J3DVector& J3DVector::operator+=(const J3DVector& vector)
{
	x =x + vector.x;
	y =y + vector.y;
	z =z + vector.z;
	return *this;
}
J3DVector& J3DVector::operator*=(const float scalar)
{
	x = x * scalar;
	y = y * scalar;
	z = z * scalar;
	return *this;
}






J3DVector operator+(const J3DVector& vector1, const J3DVector& vector2)
{
	return J3DVector(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}
J3DVector operator*(const float scalar, const J3DVector& vector)
{
	return J3DVector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}
J3DVector operator*(const J3DVector& vector, const float scalar)
{
	return J3DVector(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}