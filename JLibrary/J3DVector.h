#pragma once


/* ������ ���� ����
* ���� : Dot(v,w) = |v||w|cosf

* �ڻ��� ������ �̿��� ���� ������ ����ȭ
|v-w|^2 = |v|^2 + |w|^2 - 2|v||w|cosf
-> |v||w|cosf = v1w1 + v2w2 + v3w3 ( ���� ����)

**���� ��Ģ�� �����ϱ� ���ؼ��� ���� i,j,k �� ǥ�ر����� ǥ���Ǿ��־���Ѵ�.**


* ������ �̿��� ���� �Ǻ���
Dot(v,w) == 0  -> 90��
Dot(v,w) < 0   -> 90������ ũ��
Dot(v,w) > 0   -> 90������ �۴�



* ������ �̿��� ��������
���� :  v,w ���Ͱ��ְ�  < w !=0 > �ϋ�
���� : proj(w)v = ( Dot(v,w) / |w|^2 ) * w  (v-w : w�� ��������)
���� : prerp(w)v = v - proj(w)v             (kw ���� - ��Į�󰪸� Ʋ�� w����)
- ���� ��� : �� w�� ����ȭ�� �Ǿ��ִٸ� proj(w)v = Dot(v,w) * w ���ȴ�.
*/



class J3DVector
{
public:
	float x;
	float y;
	float z;

public:
	/** ������ �� �Ҹ��� */
	J3DVector();
	J3DVector(const float _x, const float _y, const float _z);
	J3DVector(const J3DVector& copy);
	~J3DVector();

	/** ���� �� ����, ���� ���� */
	float Length() const;
	float LengthSquared() const;
	J3DVector& Normalize();
	J3DVector Cross(const J3DVector& vector);
	float Dot(const J3DVector& vector);

	/** ������ �����ε� */
	J3DVector& operator=(const J3DVector& vector);
	J3DVector& operator+=(const J3DVector& vector);
	J3DVector& operator*=(const float scalar);
};


/** ������ �����ε� */
J3DVector operator+(const J3DVector& vector1, const J3DVector& vector2);
J3DVector operator*(const float scalar, const J3DVector& vector);
J3DVector operator*(const J3DVector& vector, const float scalar);