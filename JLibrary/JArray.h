#pragma once
#pragma warning(disable : 4996)

/**   헤더파일 선언 */
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include "JTrace.h"
#include"AlgorithmFunctor.h"
/**  작업 일지
[] 연산자와 index 고려해보기 index는 안전한대신 느리고 []은 불안전한대신 빠르게!!

*/
////////////////////////////////////////////////////////
/////////////////////   정 의 부   /////////////////////
////////////////////////////////////////////////////////

template <class Data>
class JArray
{
public:
	class JArray_Iterator;
protected:
	Data * m_Data;
	size_t m_elementCount;
	size_t m_memorySize;
public:
	/** 생성자 및 소멸자 */
	JArray();
	JArray(const size_t size);
	JArray(const std::initializer_list<Data>& list);
	JArray(const JArray& copy);
	~JArray();

	/** 삽입 및 삭제 */
	void push_back(const Data& data);
	Data& pop_back();
	void clear();

	JArray_Iterator erase(const JArray_Iterator& data);
	JArray_Iterator erase(const JArray_Iterator& start, const JArray_Iterator& end);
	JArray_Iterator remove(const JArray_Iterator& data);
	JArray_Iterator remove(const JArray_Iterator& start, const JArray_Iterator& end);
	JArray_Iterator remove_if(const std::function<bool(const Data& data)>& func);
	JArray_Iterator remove_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func);

	/** 탐색 */
	JArray_Iterator begin();
	JArray_Iterator end();
	JArray_Iterator find(const Data& data);
	JArray_Iterator find(const JArray_Iterator& start, const JArray_Iterator& end,const Data& data);
	JArray_Iterator find_if(const std::function<bool(const Data& data)>& func);
	JArray_Iterator find_if(const JArray_Iterator& start, const JArray_Iterator& end,const std::function<bool(const Data& data)>& func);
	const Data&  safe_index(const size_t idx) const;
	const size_t count(const Data& data) const;
	const size_t count_if(const std::function<bool(const Data& data)>& func);
	const size_t count_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func);

	/** 사이즈 및 크기 */
	void Init(const size_t size);
	void resize(const size_t size);
	void reserve(const size_t size);
	const size_t size() const;
	const size_t memorysize() const;
	bool empty() const;


	/** 정렬 및 편의 함수*/
	void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less_Functor<Data>());
	void sort(const JArray_Iterator& start, const JArray_Iterator& last, const std::function<bool(const Data& data1, const Data& data2)>& func = Less_Functor<Data>());
	void swap(JArray_Iterator data1, JArray_Iterator data2);

	/**  연산자 오버로딩 */
	Data&         operator[](const size_t idx);
	const JArray& operator=(const JArray& data);

	/**  출력  */
	void Write_cpp() const;

public:
	class JArray_Iterator
	{
	private:
		friend class JArray<Data>;
	protected:
		Data * m_Ptr;
	public:
		/*  생성자 및 소멸자 */
		JArray_Iterator();
		JArray_Iterator(Data* data);
		~JArray_Iterator();
		/* 포인터 및 값 반환 */
		Data* operator->();
		Data& operator*();


		/* 대입 연산자 */
		JArray_Iterator& operator=(const JArray_Iterator& data);

		/* 반복자 이동 연산자 */
		JArray_Iterator& operator++();                    // 전위 연산자
		JArray_Iterator operator++(const int idx);        // 후위 연산자
		JArray_Iterator operator+(const int idx);


		JArray_Iterator& operator--();
		JArray_Iterator operator--(const int idx);
		JArray_Iterator operator-(const int idx);

		JArray_Iterator& operator+=(const int idx);
		JArray_Iterator& operator-=(const int idx);
		
		// 반복자 비교 연산
		bool operator==(const JArray_Iterator& rhs) const;
		bool operator!=(const JArray_Iterator& rhs) const;

		bool operator>(const JArray_Iterator& rhs) const;
		bool operator>=(const JArray_Iterator& rhs) const;
		bool operator<(const JArray_Iterator& rhs) const;
		bool operator<=(const JArray_Iterator& rhs) const;
	};
};

////////////////////////////////////////////////////////
/////////////////////   구 현 부   /////////////////////
////////////////////////////////////////////////////////
/*  생성자 및 소멸자 */
template <class Data>
JArray<Data>::JArray()
{
	m_memorySize = 10;
	m_elementCount = 0;
	m_Data = new Data[m_memorySize];
}
template <class Data>
JArray<Data>::JArray(const size_t size)
{
	m_memorySize = size;
	m_elementCount = 0;
	m_Data = new Data[m_memorySize];
}
template <class Data>
JArray<Data>::JArray(const std::initializer_list<Data>& list)
{
	m_memorySize = list.size();
	m_elementCount = m_memorySize;
	m_Data = nullptr;
	m_Data = new Data[m_memorySize];

	int i = 0;
	for (auto& iter : list)
	{
		m_Data[i++] = iter;
	}
}
template <class Data>
JArray<Data>::JArray(const JArray& copy)
{
	m_elementCount = copy.size();
	m_memorySize = copy.memorysize();
	m_Data = new Data[m_memorySize];
	for (size_t i = 0; i < m_elementCount; ++i)
	{
		m_Data[i] = copy.index(i);
	}
}
template <class Data>
JArray<Data>::~JArray()
{
	delete[] m_Data;
	m_Data = nullptr;
}


/* 삽입 및 삭제 */
template <class Data>
void JArray<Data>::push_back(const Data& data)
{
	// 메모리영역이 꽉찼을 경우
	if (m_elementCount >= m_memorySize)
	{
		reserve(m_memorySize * 2);
	}

	m_Data[m_elementCount++] = data;
}
template <class Data>
Data& JArray<Data>::pop_back()
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::pop_back() \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return Data();
	}
	m_elementCount--;
	return m_Data[m_elementCount];
}
template <class Data>
void JArray<Data>::clear()
{
	m_elementCount = 0;
	m_memorySize = 10;
	
	delete[] m_Data;
	m_Data = nullptr;

	m_Data = new Data[m_memorySize];
}

template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::erase(const JArray_Iterator& data)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::erase \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}

	JArray_Iterator result;
	for (auto iter = data; iter < end(); ++iter)
	{
		*iter = *(iter + 1);
	}

	m_elementCount--;
	Data* tmpData = new Data[m_memorySize];


	for (size_t i = 0; i < m_elementCount; ++i)
	{
		tmpData[i] = m_Data[i];
		if (data == &m_Data[i])
		{
			result = &tmpData[i];
		}
	}
	delete[] m_Data;
	m_Data = nullptr;

	m_Data = tmpData;
	return result;
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::erase(const JArray_Iterator& start, const JArray_Iterator& last)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::erase \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}

	JArray_Iterator result;
	size_t count = 0;

	// 구간 길이 알기
	for (auto iter = start; iter < last; ++iter)
	{
		count++;
	}
	for(auto iter = start; iter< end() - count; ++iter)
	{
		*iter = *(iter + count);
	}
	m_elementCount -= count;

	Data* tmpData = new Data[m_memorySize];
	for (size_t i = 0; i < m_elementCount; ++i)
	{
		tmpData[i] = m_Data[i];
		if (start == &m_Data[i])
		{
			result = &tmpData[i];
		}
	}
	delete[] m_Data;
	m_Data = nullptr;

	m_Data = tmpData;
	return result;
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::remove(const JArray_Iterator& data)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::remove \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}
	for (auto iter = data; iter < end(); ++iter)
	{
		*iter = *(iter + 1);
	}
	m_elementCount--;
	return data;
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::remove(const JArray_Iterator& start, const JArray_Iterator& last)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::remove \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}
	size_t count = 0;
	// 처음과 끝부분의 간격을 알아낸다.
	for(auto iter = start; iter < last; ++iter)
	{
		count++;
	}
	for (auto iter = start; iter < (end() - count); ++iter)
	{
		*iter = *(iter + count);
	}
	m_elementCount -= count;
	return start;
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::remove_if(const std::function<bool(const Data& data)>& func)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::remove_if \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}
	auto start = begin();
	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (func(*iter))
		{
			start = iter;
			for (auto iter = start; iter < (end() - 1); ++iter)
			{
				*iter = *(iter + 1);
			}
			m_elementCount--;
		}
	}
	return start;
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::remove_if(const JArray_Iterator& start, const JArray_Iterator& last, const std::function<bool(const Data& data)>& func)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::remove_if \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
		return JArray_Iterator();
	}
	auto tmp_start = start;

	for (auto iter = start; iter < last; ++iter)
	{
		if (func(*iter))
		{
			tmp_start = iter;
			for (auto iter = tmp_start; iter < end(); ++iter)
			{
				*iter = *(iter + 1);
			}
			m_elementCount--;
			last--;
		}
	}
	return tmp_start;
}
/* 탐 색 */
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::begin()
{
	if (m_elementCount == 0)
	{
		return JArray_Iterator(nullptr);
	}
	else
	{
		return JArray_Iterator(&m_Data[0]);
	}
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::end()
{
	if (m_elementCount == 0)
	{
		return JArray_Iterator(nullptr);
	}
	Data * pdata = &m_Data[m_elementCount - 1];
	return JArray_Iterator(pdata + 1);
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::find(const Data& data)
{
	for (size_t i = 0; i < m_elementCount; ++i)
	{
		if (m_Data[i] == data)
		{
			return JArray_Iterator(&m_Data[i]);
		}
	}
	return end();
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::find(const JArray_Iterator& start, const JArray_Iterator& end,const Data& data)
{
	for (auto iter = start; iter < end; ++iter)
	{
		if (data == (*iter))
		{
			return iter;
		}
	}
	return JArray_Iterator(nullptr);
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::find_if(const std::function<bool(const Data& data)>& func)
{
	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (func(*iter))
		{
			return JArray_Iterator(iter);
		}
	}
	return this->end();
}
template <class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::find_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
{
	for (auto iter = start; iter < end; ++iter)
	{
		if (func(*iter))
		{
			return JArray_Iterator(iter);
		}
	}
	return this->end();
}
template <class Data>
const Data& JArray<Data>::safe_index(const size_t idx) const
{
	if (idx >= m_elementCount)
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::safe_index \n"));
		DebugLog(TEXT("Error      : The index is out of range of the array element. \n"));

		assert(idx < m_elementCount);
		return m_Data[m_elementCount - 1];
	}
	else
	{
		return m_Data[idx];
	}
}
template <class Data>
const size_t JArray<Data>::count(const Data& data) const
{
	size_t count = 0;
	for (size_t i = 0; i < m_elementCount; i++)
	{
		if (m_Data[i] == data) count++;
	}
	return count;
}
template <class Data>
const size_t JArray<Data>::count_if(const std::function<bool(const Data& data)>& func)
{
	size_t count = 0;
	for (size_t = 0; i < m_elementCount; i++)
	{
		if (func(m_Data[i])) count++;
	}
	return count;
}
template <class Data>
const size_t JArray<Data>::count_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
{
	size_t count = 0;
	for (auto iter = start; iter < end; iter++)
	{
		if (func(*iter)) count++;
	}
	return count;
}
/* 사이즈 및 크기 */
template <class Data>
void JArray<Data>::Init(const size_t size)
{
	Data dummy;
	reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		push_back(dummy);
	}
}
template <class Data>
void JArray<Data>::resize(const size_t size)
{
	m_elementCount = size;
}
template <class Data>
void JArray<Data>::reserve(const size_t size)
{
	m_memorySize = size;
	Data* tmp = new Data[size];

	for (size_t i = 0; i < m_elementCount; ++i)
	{
		tmp[i] = m_Data[i];
	}

	delete[] m_Data;
	m_Data = nullptr;

	m_Data = tmp;
}
template <class Data>
const size_t JArray<Data>::size() const
{
	return m_elementCount;
}
template <class Data>
const size_t JArray<Data>::memorysize() const
{
	return m_memorySize;
}
template <class Data>
bool JArray<Data>::empty() const
{
	if (m_elementCount <= 0)
	{
		return true;
	}
	return false;
}
template <class Data>
void JArray<Data>::sort(const std::function<bool(const Data& data1, const Data& data2)>& func)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
	}
	Quick_Sort_Functor<Data, JArray_Iterator>()(begin(), end() - 1, func);
}
template <class Data>
void JArray<Data>::sort(const JArray_Iterator& start, const JArray_Iterator& last, const std::function<bool(const Data& data1, const Data& data2)>& func)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray \n"));
		DebugLog(TEXT("Error      : Array is empty! \n"));
	}
	Quick_Sort_Functor<Data, JArray_Iterator>()(start, last, func);
}
template <class Data>
void JArray<Data>::swap(JArray_Iterator data1, JArray_Iterator data2)
{
	Data tmp = *data1;
	*data1 = *data2;
	*data2 = tmp;
}
/** 연 산 자  오 버 로 딩 */
template <class Data>
Data& JArray<Data>::operator[](const size_t idx)
{
	if (idx >= m_memorySize)
	{
		DebugLog(TEXT("Location   : JArray.h \n"));
		DebugLog(TEXT("Class      : JArray::operator[] \n"));
		DebugLog(TEXT("Error      : The index is out of range of the array! \n"));
		assert(idx <= m_memorySize);
		return m_Data[m_memorySize - 1];
		
	}
	else
	{
		return m_Data[idx];
	}
}
template <class Data>
const JArray<Data>& JArray<Data>::operator=(const JArray<Data>& data)
{
	if (m_Data)
	{
		delete m_Data;
		m_Data = nullptr;
	}
	m_elementCount = data.size();
	m_memorySize = data.memorysize();
	m_Data = new Data[m_memorySize];
	for (size_t i = 0; i < m_elementCount; ++i)
	{
		m_Data[i] = data.index(i);
	}
	return *this;
}
/*  출력  */
template <class Data>
void JArray<Data>::Write_cpp() const
{
	std::cout << "JArray : [ ";
	for (size_t i = 0; i < m_elementCount; ++i)
	{
		if (i < m_elementCount - 1)
		{
			std::cout << m_Data[i] << ", ";
		}
		else
		{
			std::cout << m_Data[i];
		}
	}
	std::cout<< " ]" << std::endl;
	std::cout << "elementCount : " << m_elementCount << std::endl;
	std::cout << "memorySize   : " << m_memorySize << std::endl;
}


template<class Data>
JArray<Data>::JArray_Iterator::JArray_Iterator() {}

template<class Data>
JArray<Data>::JArray_Iterator::JArray_Iterator(Data* data)
{
	m_Ptr = data;
}
template<class Data>
JArray<Data>::JArray_Iterator::~JArray_Iterator() {}


// 포인터 및 값 반환
template<class Data>
Data* JArray<Data>::JArray_Iterator::operator->()
{
	return m_Ptr;
}
template<class Data>
Data& JArray<Data>::JArray_Iterator::operator*()
{
	return (*m_Ptr);
}

/* 대입 연산자 */
template<class Data>
typename JArray<Data>::JArray_Iterator& JArray<Data>::JArray_Iterator::operator=(const JArray_Iterator& data)
{
	this->m_Ptr = data.m_Ptr;
	return *this;
}
/* 반복자 이동 연산자 */
template<class Data>
typename JArray<Data>::JArray_Iterator& JArray<Data>::JArray_Iterator::operator++()
{
	m_Ptr++;
	return *this;
}
template<class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::JArray_Iterator::operator++(const int idx)
{
	auto result = *this;
	m_Ptr++;
	return result;
}
template<class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::JArray_Iterator::operator+(const int idx)
{
	Data* ptr = m_Ptr + idx;
	return JArray_Iterator(ptr);
}
template<class Data>
typename JArray<Data>::JArray_Iterator& JArray<Data>::JArray_Iterator::operator--()
{
	m_Ptr--;
	return *this;
}
template<class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::JArray_Iterator::operator--(const int idx)
{
	auto result = *this;
	m_Ptr--;
	return result;
}
template<class Data>
typename JArray<Data>::JArray_Iterator JArray<Data>::JArray_Iterator::operator-(const int idx)
{
	Data* ptr = m_Ptr - idx;
	return JArray_Iterator(ptr);
}
template<class Data>
typename JArray<Data>::JArray_Iterator& JArray<Data>::JArray_Iterator::operator+=(const int idx)
{
	m_Ptr = m_Ptr + idx;
	return *this;
}
template<class Data>
typename JArray<Data>::JArray_Iterator& JArray<Data>::JArray_Iterator::operator-=(const int idx)
{
	m_Ptr = m_Ptr - idx;
	return *this;
}

/* 반복자 비교 연산 */
template<class Data>
bool JArray<Data>::JArray_Iterator::operator==(const JArray_Iterator& rhs) const
{
	if (this->m_Ptr == rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JArray<Data>::JArray_Iterator::operator!=(const JArray_Iterator& rhs) const
{
	if (this->m_Ptr == rhs.m_Ptr)
	{
		return true;
	}
	return false;
}

template<class Data>
bool JArray<Data>::JArray_Iterator::operator>(const JArray_Iterator& rhs) const
{
	if (m_Ptr > rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JArray<Data>::JArray_Iterator::operator>=(const JArray_Iterator& rhs) const
{
	if (m_Ptr >= rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JArray<Data>::JArray_Iterator::operator<(const JArray_Iterator& rhs) const
{
	if (m_Ptr < rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JArray<Data>::JArray_Iterator::operator<=(const JArray_Iterator& rhs) const
{
	if (m_Ptr <= rhs.m_Ptr)
	{
		return true;
	}
	return false;
}