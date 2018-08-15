#pragma once

class J3DVector;



class JMath
{
private:
	const static double ErrorRange;
public:
	static float Sqrt(float num);
	static bool IsZero(float num);



	/* ���� ���� �Լ� */
	// ����
	static float Length(const J3DVector& vector);
	static float LengthSquared(const J3DVector& vector);
	// ����ȭ
	static J3DVector& Normalize(J3DVector& vector);
	// ����
	static J3DVector Cross(const J3DVector& vector1, const J3DVector& vector2);
	// ����
	static float Dot(const J3DVector& vector1, const J3DVector& vector2);

};