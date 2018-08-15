#pragma once
/**   ������� ���� */
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include"JTrace.h"

#define JQueue_Max 100
/**  �۾� ����
* ����ȭ
* ����� ����ó�� ����� �Ұ�
*/
////////////////////////////////////////////////////////
/////////////////////   �� �� ��   /////////////////////
////////////////////////////////////////////////////////
template<class Data>
class JQueue
{
protected:
	// ������ �迭
	Data * m_Data;

	// ������ ����
	size_t m_Size;
	size_t m_memorySize;

	// ��ġ ����
	size_t m_Rear;
	size_t m_Front;
public:
	/* ������ �� �Ҹ��� */
	JQueue();
	JQueue(size_t size);
	JQueue(const JQueue& copy);
	~JQueue();
	/* ���� �� ���� */
	void push(const Data& data);
	Data& pop();
	void clear(size_t size = JQueue_Max);

	/* Ž�� �� ������*/
	Data& back();
	Data& front();
	bool empty();
	bool full();
	size_t size();
	void resize(const size_t size);
	/* ��� */
	void Write_cpp();
	void Write_cpp_All();
};
template<class Data>
JQueue<Data>::JQueue()
{
	// ������ �����Ҵ�
	m_Data = new Data[JQueue_Max];

	// ������ �ʱ�ȭ
	m_Size = 0;
	m_memorySize = JQueue_Max;

	// ��ġ ���� �ʱ�ȭ
	m_Rear = 0;
	m_Front = 0;
}
template<class Data>
JQueue<Data>::JQueue(size_t size)
{
	// ������ �����Ҵ�
	m_Data = new Data[size];

	// ������ �ʱ�ȭ
	m_Size = 0;
	m_memorySize = size;

	// ��ġ ���� �ʱ�ȭ
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
		// ������ - �޸𸮻����� + 1 + Front
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
	// m_Front���ͽ����� �����ŭ �������� �޸� ũ�⸦ �Ѿ�������� �׳� ���
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
/** ���� �� ���� */
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

	// �޸� ���Ҵ�.
	m_Data = new Data[size];
}
/* Ž�� */
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

	// front �� rear�� ������ ������ִ°Ŵ�.
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

	// �� ť�� ������������� ���� �ڵ带 �����Ѵ�.
	if(!empty())
	{
		// ���� ���� ����� ���� ������� Ŭ��
		if (m_Front + m_Size >= m_memorySize)
		{
			// ������ - �޸𸮻����� + 1 + Front
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
		// m_Front���ͽ����� �����ŭ �������� �޸� ũ�⸦ �Ѿ�������� �׳� ���
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
/* ��� */
template<class Data>
void JQueue<Data>::Write_cpp()
{
	std::cout << "JQueue" << endl;
	std::cout << "Front : " << m_Front << endl;
	std::cout << "Rear  : " << m_Rear << endl;
	std::cout << "Size  : " << m_Size << endl;
	std::cout << "MemSize : " << m_memorySize << endl;
	std::cout << "[ ";
	// �Ѿ����
	if (m_Front + m_Size >= m_memorySize)
	{
		// ������ - �޸𸮻����� + 1 + Front
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
	// m_Front���ͽ����� �����ŭ �������� �޸� ũ�⸦ �Ѿ�������� �׳� ���
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
