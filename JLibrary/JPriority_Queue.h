#pragma once
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include"JTrace.h"
#include"JAlgorithm.h"
#define JPriority_Queue_MAX 100


// 보류






// 대입연산자로 함수 넣기

/*template<class Data>
class JPriority_Queue
{
protected:
	Data* m_Data;
	size_t m_Size; 
	size_t m_MemorySize;
	std::function<bool(const Data&, const Data&)> m_CompareFunction;
	bool m_IsFunctionInit = false;
	// 부모 -> 첫번쨰 자식 = i*2;
	// 부모 -> 두번째 자식 = (i*2) + 1;
public:
	JPriority_Queue(const std::function<bool(const Data&, const Data&)>& func = Less<Data>);
	JPriority_Queue(const size_t size, const std::function<bool(const Data&, const Data&)>& func = Less<Data>);
	JPriority_Queue(const JPriority_Queue& copy);
	~JPriority_Queue();

	void SetCompareFunction(const std::function<bool(const Data&, const Data&)>& func);
	void push(const Data& data);
	void pop();
	void clear(const size_t size = JPriority_Queue_MAX);

	Data top();
	bool empty();
	bool full();
	size_t size();
	void resize(const size_t size);

	void Write_cpp();


private:
	void PriorityCompare_pop(int index);
};

template<class Data>
JPriority_Queue<Data>::JPriority_Queue(const std::function<bool(const Data&, const Data&)>& func)
{
	m_CompareFunction = func;
	m_Data = new Data[JPriority_Queue_MAX];
	m_Size = 0;
	m_MemorySize = JPriority_Queue_MAX;
}
template<class Data>
JPriority_Queue<Data>::JPriority_Queue(const size_t size, const std::function<bool(const Data&, const Data&)>& func)
{
	m_CompareFunction = func;
	m_MemorySize = size;
	m_Size = 0;
	m_Data = new Data[m_MemorySize];
}
template<class Data>
JPriority_Queue<Data>::JPriority_Queue(const JPriority_Queue& copy)
{
	m_CompareFunction = copy.m_CompareFunction;
	m_Size = copy.m_Size;
	m_MemorySize = copy.m_MemorySize;
	m_Data = new Data[m_MemorySize];
	for (size_t i = 0; i < m_MemorySize; ++i)
	{
		m_Data[i] = copy.m_Data[i];
	}
}
template<class Data>
JPriority_Queue<Data>::~JPriority_Queue()
{
	delete[] m_Data;
	m_Size = 0;
	m_MemorySize = 0;
}


template<class Data>
void JPriority_Queue<Data>::SetCompareFunction(const std::function<bool(const Data&, const Data&)>& func)
{
	if (!m_IsFunctionInit)
	{
		m_CompareFunction = func;
	}
	else
	{
		DebugLog("Error : You have already set the function settings.\n");
		DebugLog("Class : JPriority_Queue \n");
		DebugLog("Function : SetCompareFunction \n");
	}
}
template<class Data>
void JPriority_Queue<Data>::push(const Data& data)
{

	size_t Index = m_Size + 1;
	// 배열이 꽉차있을경우
	if (full())
	{
		DebugLog("Error : The queue's memory size is full..\n");
		DebugLog("Class : JPriority_Queue \n");
		DebugLog("Function : push \n");
		assert(false);
	}


	// 루트에 아무것도 없을 경우 함수 설정을 막고 데이터를 루트 노드에 바로 넣는다.
	if (empty())
	{
		m_IsFunctionInit = true;
		m_Data[Index] = data;
		m_Size++;
		return;
	}

	// 일단 삽입
	m_Data[Index] = data;
	m_Size++;
	Data tmp;
	while ((Index / 2 ) > 0)
	{
		// 부모 노드와 우선순위 비교
		// 우선순위가 자식이 더 크다면 부모 노드와 자식노드 교환
		if (m_CompareFunction(m_Data[Index / 2], m_Data[Index]))
		{
			tmp = m_Data[Index];

			m_Data[Index] = m_Data[Index / 2];
			m_Data[Index / 2] = tmp;
			Index = Index / 2;
		}
		// 아니라면 루프에서 벗어난다.
		else
		{
			break;
		}
	}
}
template<class Data>
void JPriority_Queue<Data>::pop()
{
	if (empty())
	{
		DebugLog("Error : The queue's  size is empty..\n");
		DebugLog("Class : JPriority_Queue \n");
		DebugLog("Function : pop \n");
		assert(false);
		return;
	}
	m_Data[1] = m_Data[m_Size];
	m_Size--;
	PriorityCompare_pop(1);
}
template<class Data>
void JPriority_Queue<Data>::clear(const size_t size)
{
	// 모두 삭제
	delete[] m_Data;
	m_Data = nullptr;
	m_Size = 0;
	m_MemorySize = size;

	// 다시 할당
	m_Data = new Data[size];
}

template<class Data>
Data JPriority_Queue<Data>::top()
{
	return m_Data[1];
}
template<class Data>
bool JPriority_Queue<Data>::empty()
{
	if (m_Size == 0)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JPriority_Queue<Data>::full()
{
	if (m_Size != 0 && m_Size - 1 >= m_MemorySize)
	{
		return true;
	}
	return false;
}
template<class Data>
size_t JPriority_Queue<Data>::size()
{
	return m_Size;
}

template<class Data>
void JPriority_Queue<Data>::resize(const size_t size)
{
	Data* tmpData = new Data[size];


	if (m_Size > size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			tmpData[i] = m_Data[i];
		}
		m_Size = size - 1;
	}
	else
	{
		for (size_t i = 0; i < m_Size; ++i)
		{
			tmpData[i] = m_Data[i];
		}
	}

	delete[] m_Data;
	m_Data = nullptr;

	m_MemorySize = size;
	m_Data = tmpData;

}


template<class Data>
void JPriority_Queue<Data>::Write_cpp()
{
	size_t count = 1;
	size_t sumCount = 0;
	int Height = (int)log2(m_Size) + 1;
	Height = Height * 10;

	std::cout << "JPriority_Queue" << endl;
	std::cout << "Size : " << m_Size << endl;
	std::cout << "MemSize : " << m_MemorySize << endl;
	for (size_t i = 1; i < m_Size + 1; ++i)
	{

		for (size_t j = 0; j < count; ++j)
		{
			// 
			if (sumCount == m_Size)
			{
				break;
			}
			// 공백 //첨에만
			for (int blank = 0; blank < Height; ++blank)
			{
				cout << " ";
			}



			// 출력
			std::cout << "[ " << m_Data[i + j] << " ]";
			// 공백
			for (int blank = 0; blank < Height; ++blank)
			{
				cout << " " ;
			}
			sumCount++;
		
		}
		i += count - 1;
		count *= 2;
		Height = Height / 2 -1;
		std::cout << endl;
	}
}

template<class Data>
void JPriority_Queue<Data>::PriorityCompare_pop(int index)
{
	int Left = index * 2;
	int Right = (index * 2) + 1;
	int tmp  = 0;
	// 왼쪽자식으로 대체했고 오른쪽 자식

	// 다시짜기
	// 자식노드가 없을 경우 재귀 탈출
	if (index * 2 > (int)m_Size)
	{
		return;
	}
	// 한쪽(왼쪽) 노드만 있을 경우
	if (Right > (int)m_Size &&  m_CompareFunction(m_Data[index], m_Data[Left] ))
	{
		tmp = m_Data[index];
		m_Data[index] = m_Data[Left];
		m_Data[Left] = tmp;
		return;
	}
	// 우선순위 에따라 부모노드를 대체한다.
	if (m_CompareFunction(m_Data[Right],m_Data[Left]) && m_CompareFunction(m_Data[index], m_Data[Left]))
	{
		tmp = m_Data[index];
		m_Data[index] = m_Data[Left];
		m_Data[Left] = tmp;
		PriorityCompare_pop(Left);
	}
	else if(m_CompareFunction(m_Data[Left],m_Data[Right])  && m_CompareFunction(m_Data[index], m_Data[Right]))
	{
		tmp = m_Data[index];
		m_Data[index] = m_Data[Right];
		m_Data[Right] = tmp;
		PriorityCompare_pop(Right);
	}

}*/
