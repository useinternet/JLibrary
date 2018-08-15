#pragma once
class JPlane
{
	/* ����� ������ ���ϴ¹�
	* �� P,Q,R�� �ִٸ�
	* u = Q - P;
	* v = R - P;
	* n = cross(u,v)
	* normalize(n) = (a,b,c);
	* d = -(a*P1 + b*P2 + c*P3) */
private:
	float x, y, z; // ��� ����
	float d;
public:
	JPlane(float a,float b, float c, float d);
	~JPlane();
};

