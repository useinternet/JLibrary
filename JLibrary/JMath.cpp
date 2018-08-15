#include"JMath.h"
#include"J3DVector.h"
const double JMath::ErrorRange = 0.00005;


float JMath::Sqrt(float num)
{
	float x = 1;
	while (true)
	{
		x = (x + num / x) / 2;
		if (num - ErrorRange < x*x && x*x < num + ErrorRange)
		{
			break;
		}
	}
	return x;
}
bool JMath::IsZero(float num)
{
	if (-ErrorRange < num && num < ErrorRange)
	{
		return true;
	}
	return false;
}

float JMath::Length(const J3DVector& vector)
{
	return Sqrt( (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z) );
}
float JMath::LengthSquared(const J3DVector& vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
}
J3DVector& JMath::Normalize(J3DVector& vector)
{
	float lengthSqrd = LengthSquared(vector);
	if (IsZero(lengthSqrd))
	{
		vector.x = 0.0f; vector.y = 0.0f; vector.z = 0.0f;
		return vector;
	}

	float InverselengthSqrd = 1 / Sqrt(lengthSqrd);
	vector.x *= InverselengthSqrd;
	vector.y *= InverselengthSqrd;
	vector.z *= InverselengthSqrd;

	return vector;
}
J3DVector JMath::Cross(const J3DVector& vector1, const J3DVector& vector2)
{
	return J3DVector((vector1.y * vector2.z) - (vector1.z * vector2.y),
		             (vector1.z * vector2.x) - (vector1.x * vector2.z), 
		             (vector1.x * vector2.y) - (vector1.y * vector2.x));
}
float JMath::Dot(const J3DVector& vector1, const J3DVector& vector2)
{
	return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}