#pragma once


// ���� ������

template<class T1, class T2>
class JPair
{
public:
	T1 first;
	T2 second;
public:
	JPair();
	JPair(const T1& data1, const T1& data2);
	JPair(const JPair& copy);
	~JPair();
	JPair& operator=(const JPair& pair);
};
// ���� �� //
template<class T1, class T2>
JPair<T1, T2>::JPair() {}
template<class T1, class T2>
JPair<T1, T2>::JPair(const T1& data1, const T1& data2)
{
	// �� �ֱ�
	first = data1;
	second = data2;
}
template<class T1, class T2>
JPair<T1, T2>::JPair(const JPair& copy)
{
	first = copy.first;
	second = copy.second;
}
template<class T1, class T2>
JPair<T1, T2>::~JPair() {}
template<class T1, class T2>
JPair<T1,T2>& JPair<T1, T2>::operator=(const JPair& pair)
{
	this->first = pair.first;
	this->second = pair.second;

	return *this;
}