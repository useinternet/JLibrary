#pragma once

class J3DVector;



class JMath
{
private:
	const static double ErrorRange;
public:
	static float Sqrt(float num);
	static bool IsZero(float num);



	/* 벡터 관련 함수 */
	// 길이
	static float Length(const J3DVector& vector);
	static float LengthSquared(const J3DVector& vector);
	// 정규화
	static J3DVector& Normalize(J3DVector& vector);
	// 외적
	static J3DVector Cross(const J3DVector& vector1, const J3DVector& vector2);
	// 내적
	static float Dot(const J3DVector& vector1, const J3DVector& vector2);

};