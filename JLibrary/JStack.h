#pragma once

/**   헤더파일 선언 */
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include"JTrace.h"
#define JStack_Max 100
/**  작업 일지
* 제대로 동작하는지 실험하기
* 문서화하기
* 디버그 예외처리 제대로 할것

*/
////////////////////////////////////////////////////////
/////////////////////   정 의 부   /////////////////////
////////////////////////////////////////////////////////
template<class Data>
class JStack
{
protected:
	Data * m_Data;

	// 사이즈 변수
	size_t m_memorySize;
	
	// 위치 변수
	int m_Top;
public:
	/* 생성자 및 소멸자 */
	JStack();
	JStack(const size_t size);
	JStack(const JStack& copy);
	~JStack();

	/* 삽입 및 삭제 */
	void push(const Data& data);
	Data& pop();
	void clear(const size_t size = JStack_Max);

	/* 탐색및 사이즈 */
	Data& top();
	bool empty();
	bool full();
	size_t size();
	void resize(const size_t size);
	/* 출력 */
	void Write_cpp();
	void Write_cpp_All();
};

/* 생성자 및 소멸자 */
template<class Data>
JStack<Data>::JStack()
{
	m_Data = new Data[JStack_Max];
	m_memorySize = JStack_Max;
	m_Top = -1;
}
template<class Data>
JStack<Data>::JStack(const size_t size)
{
	m_Data = new Data[size];
	m_memorySize = size;
	m_Top = -1;
}
template<class Data>
JStack<Data>::JStack(const JStack& copy)
{
	m_memorySize = copy.m_memorySize;
	m_Data = new Data[m_memorySize];

	for (size_t i = 0; i < copy.m_Top + 1; ++i)
	{
		m_Data[i] = copy.m_Data[i];
	}
	m_Top = copy.m_Top;
}
template<class Data>
JStack<Data>::~JStack()
{
	delete m_Data;
	m_Data = nullptr;
	m_memorySize = 0;
	m_Top = -1;
}

/* 삽입 및 삭제 */
template<class Data>
void JStack<Data>::push(const Data& data)
{
	if (full())
	{
		DebugLog(TEXT("Location   : JStack.h \n"));
		DebugLog(TEXT("Class      : JStack::push \n"));
		DebugLog(TEXT("Error      : JStack is full ! \n"));
		assert(!full());
	}

	m_Top++;
	m_Data[m_Top] = data;
}
template<class Data>
Data& JStack<Data>::pop()
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JStack.h \n"));
		DebugLog(TEXT("Class      : JStack::pop \n"));
		DebugLog(TEXT("Error      : JStack is empty ! \n"));
		assert(!empty());
	}

	return m_Data[m_Top--];
}
template<class Data>
void JStack<Data>::clear(const size_t size)
{
	delete m_Data;
	m_Data = nullptr;

	m_memorySize = size;
	m_Top = -1;
	m_Data = new Data[size];
}

/* 탐색및 사이즈 */
template<class Data>
Data& JStack<Data>::top()
{
	return m_Data[m_Top];
}
template<class Data>
bool JStack<Data>::empty()
{
	if (m_Top == -1)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JStack<Data>::full()
{
	if (m_Top == m_memorySize - 1)
	{
		return true;
	}
	return false;
}
template<class Data>
size_t JStack<Data>::size()
{
	return m_Top + 1;
}
template<class Data>
void JStack<Data>::resize(const size_t size)
{
	Data* tmp = new Data[size];

	if (!empty())
	{
		for (int i = 0; i < m_Top + 1; ++i)
		{
			if (i >= size - 1) break;
			tmp[i] = m_Data[i];
		}
		if (size < m_Top + 1)
		{
			m_Top = size - 1;
		}
	}

	delete m_Data;
	m_Data = nullptr;

	m_memorySize = size;
	m_Data = tmp;
}
/* 출력 */
template<class Data>
void JStack<Data>::Write_cpp()
{
	std::cout << "JStack" << endl;
	std::cout << "MemorySize : " << m_memorySize << endl;
	std::cout << "Top : " << m_Top << endl;
	std::cout << "[ ";
	for (int i = 0; i < m_Top + 1; ++i)
	{
		std::cout << m_Data[i] << " ";
		if (i != 0 && i % 10 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << " ]" << endl;
}
template<class Data>
void JStack<Data>::Write_cpp_All()
{
	std::cout << "JStack" << endl;
	std::cout << "MemorySize : " << m_memorySize << endl;
	std::cout << "Top : " << m_Top << endl;
	std::cout << "[ ";
	for (int i = 0; i < m_memorySize; ++i)
	{
		std::cout << m_Data[i] << " ";
		if (i != 0 && i % 10 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << " ]" << endl;
}