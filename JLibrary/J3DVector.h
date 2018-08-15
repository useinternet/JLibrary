#pragma once


/* 벡터의 내적 정리
* 공식 : Dot(v,w) = |v||w|cosf

* 코사인 공식을 이용한 내적 공식의 간편화
|v-w|^2 = |v|^2 + |w|^2 - 2|v||w|cosf
-> |v||w|cosf = v1w1 + v2w2 + v3w3 ( 최종 공식)

**위의 법칙이 성립하기 위해서는 기저 i,j,k 의 표준기저로 표현되어있어야한다.**


* 내적을 이용한 각도 판별법
Dot(v,w) == 0  -> 90도
Dot(v,w) < 0   -> 90도보다 크다
Dot(v,w) > 0   -> 90도보다 작다



* 내적을 이용한 투영벡터
가정 :  v,w 벡터가있고  < w !=0 > 일떄
공식 : proj(w)v = ( Dot(v,w) / |w|^2 ) * w  (v-w : w에 수직벡터)
공식 : prerp(w)v = v - proj(w)v             (kw 벡터 - 스칼라값만 틀린 w벡터)
- 최종 결론 : 즉 w가 정규화만 되어있다면 proj(w)v = Dot(v,w) * w 가된다.
*/



class J3DVector
{
public:
	float x;
	float y;
	float z;

public:
	/** 생성자 및 소멸자 */
	J3DVector();
	J3DVector(const float _x, const float _y, const float _z);
	J3DVector(const J3DVector& copy);
	~J3DVector();

	/** 길이 및 내적, 각종 연산 */
	float Length() const;
	float LengthSquared() const;
	J3DVector& Normalize();
	J3DVector Cross(const J3DVector& vector);
	float Dot(const J3DVector& vector);

	/** 연산자 오버로딩 */
	J3DVector& operator=(const J3DVector& vector);
	J3DVector& operator+=(const J3DVector& vector);
	J3DVector& operator*=(const float scalar);
};


/** 연산자 오버로딩 */
J3DVector operator+(const J3DVector& vector1, const J3DVector& vector2);
J3DVector operator*(const float scalar, const J3DVector& vector);
J3DVector operator*(const J3DVector& vector, const float scalar);