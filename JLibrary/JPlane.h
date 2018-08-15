#pragma once
class JPlane
{
	/* 평면의 방정식 구하는법
	* 점 P,Q,R가 있다면
	* u = Q - P;
	* v = R - P;
	* n = cross(u,v)
	* normalize(n) = (a,b,c);
	* d = -(a*P1 + b*P2 + c*P3) */
private:
	float x, y, z; // 노멀 벡터
	float d;
public:
	JPlane(float a,float b, float c, float d);
	~JPlane();
};

