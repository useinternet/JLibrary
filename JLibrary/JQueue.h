#pragma once
/**   헤더파일 선언 */
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include"JTrace.h"

#define JQueue_Max 100
/**  작업 일지
* 문서화
* 디버그 예외처리 제대로 할것
*/
////////////////////////////////////////////////////////
/////////////////////   정 의 부   /////////////////////
////////////////////////////////////////////////////////
template<class Data>
class JQueue
{
protected:
	// 데이터 배열
	Data * m_Data;

	// 사이즈 변수
	size_t m_Size;
	size_t m_memorySize;

	// 위치 변수
	size_t m_Rear;
	size_t m_Front;
public:
	/* 생성자 및 소멸자 */
	JQueue();
	JQueue(size_t size);
	JQueue(const JQueue& copy);
	~JQueue();
	/* 삽입 및 삭제 */
	void push(const Data& data);
	Data& pop();
	void clear(size_t size = JQueue_Max);

	/* 탐색 및 사이즈*/
	Data& back();
	Data& front();
	bool empty();
	bool full();
	size_t size();
	void resize(const size_t size);
	/* 출력 */
	void Write_cpp();
	void Write_cpp_All();
};
template<class Data>
JQueue<Data>::JQueue()
{
	// 데이터 동적할당
	m_Data = new Data[JQueue_Max];

	// 사이즈 초기화
	m_Size = 0;
	m_memorySize = JQueue_Max;

	// 위치 변수 초기화
	m_Rear = 0;
	m_Front = 0;
}
template<class Data>
JQueue<Data>::JQueue(size_t size)
{
	// 데이터 동적할당
	m_Data = new Data[size];

	// 사이즈 초기화
	m_Size = 0;
	m_memorySize = size;

	// 위치 변수 초기화
	m_Rear = 0;
	m_Front = 0;
}
template<class Data>
JQueue<Data>::JQueue(const JQueue& copy)
{
	m_Data = new Data[copy.m_memorySize];
	m_Rear = copy.m_Rear;
	m_Front = copy.m_Front;
	m_Size = copy.m_Size;
	m_memorySize = copy.m_memorySize;

	if (m_Front + m_Size >= m_memorySize)
	{
		// 사이즈 - 메모리사이즈 + 1 + Front
		size_t remainSize = m_Size - m_memorySize + 1 + m_Front;
		for (size_t i = m_Front + 1; i < m_memorySize; ++i)
		{
			m_Data[i] = copy.m_Data[i];
		}
		for (size_t i = 0; i < remainSize; ++i)
		{
			m_Data[i] = copy.m_Data[i];
		}
	}
	// m_Front부터시작해 사이즈만큼 더했을때 메모리 크기를 넘어서지않을때 그냥 출력
	else
	{
		for (size_t i = m_Front + 1; i < m_Front + 1 + m_Size; ++i)
		{
			m_Data[i] = copy.m_Data[i];
		}
	}
}
template<class Data>
JQueue<Data>::~JQueue()
{
	delete[] m_Data;
	m_Data = nullptr;
	m_Size = 0;
	m_memorySize = 0;
	m_Rear = 0;
	m_Front = 0;
}
/** 삽입 및 삭제 */
template<class Data>
void JQueue<Data>::push(const Data& data)
{
	if (full())
	{
		DebugLog(TEXT("Location   : JQueue.h \n"));
		DebugLog(TEXT("Class      : JQueue::push \n"));
		DebugLog(TEXT("Error      : Queue is full ! \n"));
		assert(!full());
	}

	m_Size++;
	m_Rear = (++m_Rear) % m_memorySize;
	m_Data[m_Rear] = data;

}
template<class Data>
Data& JQueue<Data>::pop()
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JQueue.h \n"));
		DebugLog(TEXT("Class      : JQueue::pop \n"));
		DebugLog(TEXT("Error      : Queue is empty ! \n"));
		assert(!empty());
	}
	m_Size--;
	m_Front = (++m_Front) % m_memorySize;
	return m_Data[m_Front];
}
template<class Data>
void JQueue<Data>::clear(size_t size)
{
	delete[] m_Data;
	m_Data = nullptr;
	m_Size = 0;
	m_memorySize = size;
	m_Rear = 0;
	m_Front = 0;

	// 메모리 재할당.
	m_Data = new Data[size];
}
/* 탐색 */
template<class Data>
Data& JQueue<Data>::back()
{
	return m_Data[m_Rear];
}
template<class Data>
Data& JQueue<Data>::front()
{
	size_t result = (m_Front + 1) % m_memorySize;
	return m_Data[result];
}
template<class Data>
bool JQueue<Data>::empty()
{
	m_Front = m_Front % m_memorySize;
	m_Rear = m_Rear % m_memorySize;

	// front 와 rear이 같으면 비어져있는거다.
	if (m_Front == m_Rear)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JQueue<Data>::full()
{
	m_Front = m_Front % m_memorySize;
	m_Rear = m_Rear % m_memorySize;
	if (m_Front == (m_Rear + 1) % m_memorySize)
	{
		return true;
	}
	return false;
}
template<class Data>
size_t JQueue<Data>::size()
{
	return m_Size;
}
template<class Data>
void JQueue<Data>::resize(const size_t size)
{
	Data* tmp = new Data[size];
	size_t index = 1;
	size_t count = 0;

	// 이 큐가 비어져있을떄는 밑의 코드를 무시한다.
	if(!empty())
	{
		// 지금 들어온 사이즈가 현재 사이즈보다 클떄
		if (m_Front + m_Size >= m_memorySize)
		{
			// 사이즈 - 메모리사이즈 + 1 + Front
			size_t remainSize = m_Size - m_memorySize + 1 + m_Front;
			for (size_t i = m_Front + 1; i < m_memorySize; ++i)
			{
				if (count >= size - 1) break;
				tmp[index++] = m_Data[i];
				count++;

			}
			for (size_t i = 0; i < remainSize; ++i)
			{
				if (count >= size - 1) break;
				tmp[index++] = m_Data[i];
				count++;

			}
		}
		// m_Front부터시작해 사이즈만큼 더했을때 메모리 크기를 넘어서지않을때 그냥 출력
		else
		{
			for (size_t i = m_Front + 1; i < m_Front + 1 + m_Size; ++i)
			{
				if (count >= size - 1) break;
				tmp[index++] = m_Data[i];
				count++;
			}
		}

		if (m_Size > size)
		{
			m_Size = size - 1;
		}
	}

	

	delete[] m_Data;
	m_Data = nullptr;

	m_memorySize = size;
	m_Rear = m_Size;
	m_Front = 0;
	m_Data = tmp;
}
/* 출력 */
template<class Data>
void JQueue<Data>::Write_cpp()
{
	std::cout << "JQueue" << endl;
	std::cout << "Front : " << m_Front << endl;
	std::cout << "Rear  : " << m_Rear << endl;
	std::cout << "Size  : " << m_Size << endl;
	std::cout << "MemSize : " << m_memorySize << endl;
	std::cout << "[ ";
	// 넘어섯을때
	if (m_Front + m_Size >= m_memorySize)
	{
		// 사이즈 - 메모리사이즈 + 1 + Front
		size_t remainSize = m_Size - m_memorySize + 1 + m_Front;
		for (size_t i = m_Front + 1; i < m_memorySize; ++i)
		{
			std::cout << m_Data[i] << " ";
			if (i != 0 && i % 10 == 0)
			{
				std::cout << endl;
			}
		}
		for (size_t i = 0; i < remainSize; ++i)
		{
			std::cout << m_Data[i] << " ";
			if (i != 0 && i % 10 == 0)
			{
				std::cout << endl;
			}
		}
	}
	// m_Front부터시작해 사이즈만큼 더했을때 메모리 크기를 넘어서지않을때 그냥 출력
	else
	{
		for (size_t i = m_Front + 1; i < m_Front + 1 + m_Size; ++i)
		{
			std::cout << m_Data[i] << " ";
			if (i != 0 && i % 10 == 0)
			{
				std::cout << endl;
			}
		}
	}

	std::cout << "]" << endl;
}
template<class Data>
void JQueue<Data>::Write_cpp_All()
{
	std::cout << "JQueue" << endl;
	std::cout << "Front : " << m_Front << endl;
	std::cout << "Rear  : " << m_Rear << endl;
	std::cout << "Size  : " << m_Size << endl;
	std::cout << "MemSize : " << m_memorySize << endl;
	std::cout << "[ ";
	for (size_t i = 0; i < m_memorySize; ++i)
	{
		std::cout << m_Data[i] << " ";
		if (i != 0 && i % 10 == 0)
		{
			std::cout << endl;
		}
	}
	std::cout << "]" << endl;
}
