#pragma once
#include <iostream>
#include<initializer_list>
#include <functional>
#include"AlgorithmFunctor.h"
#include "JTrace.h"
/**   �۾� ���� 

*/
////////////////////////////////////////////////////////
/////////////////////   �� �� ��   /////////////////////
////////////////////////////////////////////////////////
template<class Data>
class JList
{
protected:
	struct ListNode
	{
		ListNode* left;
		ListNode* right;
		Data      data;
	};
	class JList_Iterator;
protected:
	ListNode* m_Head;
	ListNode* m_Tail;
	ListNode* m_End;
	size_t m_Size;

private:
	ListNode * NodeInit(const Data& data);
public:
	/** ������ �� �Ҹ��� */
	JList();
	JList(const std::initializer_list<Data>& list);
	JList(const JList& copy);
	~JList();

/** ���� �� ���� */
	void push_back(const Data& data);
	void push_front(const Data& data);

	Data pop_back();
	Data pop_front();

	JList_Iterator insert(const JList_Iterator& Pos, const Data& data);
	JList_Iterator insert(const JList_Iterator& Pos, size_t count, const Data& data);
	JList_Iterator insert(const JList_Iterator& Pos, const JList_Iterator& start, const JList_Iterator& end);

	JList_Iterator remove(const JList_Iterator& iter);
	JList_Iterator remove(const JList_Iterator& start, const JList_Iterator& end);
	JList_Iterator remove_if(const std::function<bool(const Data& data)>& func);
	JList_Iterator remove_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func);

	void clear();

/** Ž�� */
	JList_Iterator begin();
	JList_Iterator end();
	JList_Iterator find(const Data& data);
	JList_Iterator find(const JList_Iterator& start, const JList_Iterator& end, const Data& data);
	JList_Iterator find_if(const std::function<bool(const Data& data)>& func);
	JList_Iterator find_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func);


	Data&  index(const size_t idx);
	size_t count(const Data& data);
	size_t count_if(const std::function<bool(const Data& data)>& func);
	size_t count_if(const JList_Iterator& start, const JList_Iterator& end,const std::function<bool(const Data& data)>& func);

/** ������ �� ũ�� */
	const size_t size();
	bool empty();

/** ���� �� ���� �Լ� */
	void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less_Functor<Data>());
	void sort(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data1, const Data& data2)>& func = Less_Functor<Data>());
	void swap(JList_Iterator iter1, JList_Iterator iter2);

/** ������ �����ε� */
	Data&        operator[](const size_t idx);
	const JList& operator=(const JList& data);

/** ��� */
	void Write_cpp() const;

public: // �ݺ���
	class JList_Iterator
	{
	private:
		friend class JList<Data>;
	protected:
		ListNode * m_Ptr;
	public:
		/* ������ �� �Ҹ��� */
		JList_Iterator();
		JList_Iterator(ListNode* data);
		JList_Iterator(const JList_Iterator& copy);
		~JList_Iterator();
		/* ������ �� �� ��ȯ */
		Data* operator->();
		Data& operator*();

		/* ���� ������ */
		JList_Iterator& operator=(const JList_Iterator& data);
		/* �ݺ��� �̵� ������ */
		JList_Iterator& operator++();
		JList_Iterator operator++(const int idx);
		JList_Iterator operator+(const int idx);

		JList_Iterator& operator--();
		JList_Iterator operator--(const int idx);
		JList_Iterator operator-(const int idx);

		JList_Iterator& operator+=(const int  idx);
		JList_Iterator& operator-=(const int idx);

		// �ݺ��� �� ����
		bool operator==(const JList_Iterator& rhs) const;
		bool operator!=(const JList_Iterator& rhs) const;

		bool operator>(const JList_Iterator& rhs) const;
		bool operator<(const JList_Iterator& rhs) const;
		bool operator>=(const JList_Iterator& rhs) const;
		bool operator<=(const JList_Iterator& rhs) const;
	};
};

// ��� �ʱ�ȭ
template<class Data>
typename JList<Data>::ListNode* 
JList<Data>::NodeInit(const Data& data)
{
	ListNode* node = new ListNode;
	node->left = nullptr;
	node->right = nullptr;
	node->data = data;
	return node;
}
/** ������ �� �Ҹ��� */

template<class Data>
JList<Data>::JList()
{
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;


	m_End = new ListNode;
	m_End->right = nullptr;
	m_End->left = nullptr;
}
template<class Data>
JList<Data>::JList(const std::initializer_list<Data>& list)
{
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;

	m_End = new ListNode;
	m_End->right = nullptr;
	m_End->left = nullptr;

	for (auto& iter : list)
	{
		push_back(iter);
	}
}
template<class Data>
JList<Data>::JList(const JList& copy)
{
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;

	m_End = new ListNode;
	m_End->right = nullptr;
	m_End->left = nullptr;

	ListNode* Cur = copy.m_Head;
	for (size_t i = 0; i < copy.m_Size; ++i)
	{
		push_back(Cur->data);
		Cur = Cur->right;
	}
}
template<class Data>
JList<Data>::~JList()
{
	if (!empty())
	{
		ListNode* cur = m_Head;
		// ���� for�� ���鼭 ��� delete
		while (m_Head != m_End)
		{
			m_Head = m_Head->right;
			delete cur;
			cur = nullptr;
			cur = m_Head;
		}
	}
	delete m_End;
	m_End = nullptr;
}
/** ���� �� ���� */
template<class Data>
void JList<Data>::push_back(const Data& data)
{
	ListNode* newNode = NodeInit(data);


	// �Ӹ� �κ��� null�̶�� Head�� newNode�� �ȴ�.
	if (m_Head == nullptr)
	{
		m_Head = newNode;
		m_Tail = newNode;
		m_Tail->right = m_End;
		m_End->left = m_Tail;
	}
	else
	{
		// ������ ����
		m_Tail->right = newNode;
		newNode->left = m_Tail;
		m_Tail = newNode;
		// �ٽ� ���ϰ� ����
		m_Tail->right = m_End;
		m_End->left = m_Tail;
	}
	m_Size++;
}
template<class Data>
void JList<Data>::push_front(const Data& data)
{
	ListNode* newNode = NodeInit(data);


	// �Ӹ� �κ��� null�̶�� Head�� newNode�� �ȴ�.
	if (m_Head == nullptr)
	{
		m_Head = newNode;
		m_Tail = newNode;

		m_Tail->right = m_End;
		m_End->left = m_Tail;
	}
	else
	{
		m_Head->left = newNode;
		newNode->right = m_Head;
		m_Head = newNode;
	}
	m_Size++;
}
template<class Data>
Data JList<Data>::pop_back()
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JList.h \n"));
		DebugLog(TEXT("Class      : JList::pop_back \n"));
		DebugLog(TEXT("Error      : List is empty! \n"));
		return Data();
	}
	// �ڿ��� ���� �����Ѵ�.
	ListNode* tmp = m_Tail;
	Data result = tmp->data;

	//
	m_Tail = m_Tail->left;
	m_Tail->right = m_End;
	m_End->left = m_Tail;

	delete tmp;
	tmp = nullptr;

	//
	m_Size--;

	if (m_Size == 0)
	{
		m_Head = nullptr;
		m_Tail = nullptr;
	}

	return result;
}
template<class Data>
Data JList<Data>::pop_front()
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JList.h \n"));
		DebugLog(TEXT("Class      : JList::pop_front \n"));
		DebugLog(TEXT("Error      : List is empty! \n"));
	}

	// �տ������� �����Ѵ�.
	ListNode* tmp = m_Head;
	Data result = tmp->data;

	//
	m_Head = m_Head->right;
	m_Head->left = nullptr;

	delete tmp;
	tmp = nullptr;

	//
	m_Size--;

	//
	if (m_Size == 0)
	{
		m_Head = nullptr;
		m_Tail = nullptr;
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::insert(const JList_Iterator& Pos, const Data& data)
{
	if (empty())
	{
		DebugLog(TEXT("Location   : JList.h \n"));
		DebugLog(TEXT("Class      : JList::insert \n"));
		DebugLog(TEXT("Error      : List is empty! \n"));
	}
	ListNode* Cur = Pos.m_Ptr;
	ListNode* CurLeft = Cur->left;
	// ���� ��ġ�� �� ó���̶��
	if (CurLeft == nullptr)
	{
		push_front(data);
		return JList_Iterator(begin());
	}
	// ���� ��ġ�� ������ ��ġ���ٸ�.
	if (Cur == m_End)
	{
		push_back(data);
		return JList_Iterator(end() - 1);
	}

	ListNode* newNode = NodeInit(data);
	// ���� ����
	CurLeft->right = newNode;
	newNode->left = CurLeft;

	newNode->right = Cur;
	Cur->left = newNode;

	m_Size++;
	return JList_Iterator(newNode);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::insert(const JList_Iterator& Pos, size_t count, const Data& data)
{
	JList_Iterator result;
	for (size_t i = 0; i < count; ++i)
	{
		result = insert(Pos, data);
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::insert(const JList_Iterator& Pos, const JList_Iterator& start, const JList_Iterator& end)
{
	JList_Iterator result;
	for (auto iter = start; iter < end; ++iter)
	{
		result = insert(Pos, *iter);
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::remove(const JList_Iterator& iter)
 {
	if (empty())
	{
		DebugLog(TEXT("Location   : JList.h \n"));
		DebugLog(TEXT("Class      : JList::remove \n"));
		DebugLog(TEXT("Error      : List is empty! \n"));
	}

	ListNode* Cur = iter.m_Ptr;
	JList_Iterator result;
	// �� �κ��̶�� �������� �ʴ´�.
	if (iter == m_End)
	{
		return JList_Iterator(m_End);
	}
	// ���� ��ġ�� �� ���̶�� 
	if (Cur == m_Head)
	{
		m_Head = m_Head->right;
		m_Head->left = nullptr;
		result = m_Head;
	}
	// ���� ��ġ�� �� ���̶��
	else if (Cur == m_Tail)
	{
		m_Tail = m_Tail->left;
		m_Tail->right = m_End;
		m_End->left = m_Tail;
		result = m_End;
	}
	else
	{
		ListNode* CurLeft = Cur->left;
		ListNode* CurRight = Cur->right;

		CurLeft->right = CurRight;
		CurRight->left = CurLeft;

		result = CurRight;
	}

	delete Cur;
	Cur = nullptr;

	m_Size--;
	if (m_Size == 0)
	{
		m_Head = nullptr;
		m_Tail = nullptr;
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::remove(const JList_Iterator& start, const JList_Iterator& end)
{
	JList_Iterator result;

	for (result = start; result < end;)
	{
		result = remove(result);
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::remove_if(const std::function<bool(const Data& data)>& func)
{
	JList_Iterator result;
	for (auto iter = begin(); iter < end();)
	{
		if (func(*iter))
		{
			iter = remove(iter);
			result = iter;
		}
		else
		{
			iter++;
		}
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::remove_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
{
	JList_Iterator result;
	for (auto iter = start; iter < end; ++iter)
	{
		if (func(*iter))
		{
			result = remove(iter);
		}
	}
	return result;
}
template<class Data>
void JList<Data>::clear()
{
	ListNode* Cur = m_Head;
	while (m_Head != m_End)
	{
		m_Head = m_Head->right;
		delete Cur;
		Cur = nullptr;
		Cur = m_Head;
	}
	// ���� ������ ���� nullptr�� �ʱ�ȭ
	m_Head = nullptr;
	m_Tail = nullptr;
	m_End->left = nullptr;
	m_End->right = nullptr;
	m_Size = 0;
}


/** Ž�� */
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::begin()
{
	return JList_Iterator(m_Head);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::end()
{
	return JList_Iterator(m_End);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::find(const Data& data)
{
	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (*iter == data)
		{
			return JList_Iterator(iter);
		}
	}
	return JList_Iterator(nullptr);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::find(const JList_Iterator& start, const JList_Iterator& end, const Data& data)
{
	for (auto iter = start; iter < end; ++iter)
	{
		if (*iter == data)
		{
			return JList_Iterator(iter);
		}
	}
	return JList_Iterator(nullptr);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::find_if(const std::function<bool(const Data& data)>& func)
{
	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (func(*iter))
		{
			return JList_Iterator(iter);
		}
	}
	return JList_Iterator(nullptr);
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::find_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
{
	for (auto iter = start; iter < end; ++iter)
	{
		if (func(*iter))
		{
			return JList_Iterator(iter);
		}
	}
	return JList_Iterator(nullptr);
}
template<class Data>
Data&  JList<Data>::index(const size_t idx)
{
	return *(begin() + idx);
}
template<class Data>
size_t JList<Data>::count(const Data& data)
{
	size_t count = 0;
	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (*iter == data)
		{
			count++;
		}
	}
	return count;
}
template<class Data>
size_t JList<Data>::count_if(const std::function<bool(const Data& data)>& func)
{
	size_t count = 0;

	for (auto iter = begin(); iter < end(); ++iter)
	{
		if (func(*iter))
		{
			count++;
		}
	}

	return count;
}
template<class Data>
size_t JList<Data>::count_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
{
	size_t count = 0;

	for (auto iter = start; iter < end; ++iter)
	{
		if (func(*iter))
		{
			count++;
		}
	}

	return count;
}
/** ������ �� ũ�� */
template<class Data>
const size_t JList<Data>::size()
{
	return m_Size;
}
template<class Data>
bool JList<Data>::empty()
{
	if (m_Size == 0)
	{
		return true;
	}
	return false;
}
/** ���� �� ���� �Լ� */
template<class Data>
void JList<Data>::sort(const std::function<bool(const Data& data1, const Data& data2)>& func)
{
	Quick_Sort_Functor<Data, JList_Iterator>()(begin(), end() - 1, func);
}
template<class Data>
void JList<Data>::sort(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data1, const Data& data2)>& func)
{
	Quick_Sort_Functor<Data, JList_Iterator>()(begin(), end, func);
}
template<class Data>
void JList<Data>::swap(JList_Iterator iter1, JList_Iterator iter2)
{
	Data data = *iter1;
	*iter1 = *iter2;
	*iter2 = data;
}
/** ������ �����ε� */
template<class Data>
Data& JList<Data>::operator[](const size_t idx)
{
	if (m_Size <= idx)
	{
		DebugLog(TEXT("Location   : JList.h \n"));
		DebugLog(TEXT("Class      : JList::operator[] \n"));
		DebugLog(TEXT("Error      : The index is out of range of the list.! \n"));
		assert(m_Size > idx);
	}
	ListNode* result = m_Head;
	for (size_t i = 0; i < idx; ++i)
	{
		result = result->right;
	}
	return result->data;
}
template<class Data>
const JList<Data>& JList<Data>::operator=(const JList& data)
{
	ListNode* Cur = data.m_Head;
	for (size_t i = 0; i < data.m_Size; ++i)
	{
		push_back(Cur->data);
		Cur = Cur->right;
	}

	return *this;
}

/** ��� */
template<class Data>
void JList<Data>::Write_cpp() const
{
	ListNode* cur = m_Head;
	cout << "JList : [ ";
	while (cur != m_End)
	{
		cout << cur->data << " ";
		cur = cur->right;
	}
	cout << "]" << endl;
	cout << "Size : " << m_Size << endl;
}



/** �ݺ��� ������ �����ε� �� ������ �� �Ҹ��� */
/* ������ �� �Ҹ��� */
template<class Data>
JList<Data>::JList_Iterator::JList_Iterator()
{
	m_Ptr = nullptr;
}
template<class Data>
JList<Data>::JList_Iterator::JList_Iterator(ListNode* data)
{
	m_Ptr = data;
}
template<class Data>
JList<Data>::JList_Iterator::JList_Iterator(const JList_Iterator& copy)
{
	m_Ptr = copy.m_Ptr;
}
template<class Data>
JList<Data>::JList_Iterator::~JList_Iterator()
{
	m_Ptr = nullptr;
}

/* ������ �� �� ��ȯ */
template<class Data>
Data* JList<Data>::JList_Iterator::operator->()
{
	return &(m_Ptr->data);
}
template<class Data>
Data& JList<Data>::JList_Iterator::operator*()
{
	return m_Ptr->data;
}

/* ���� ������ */
template<class Data>
typename JList<Data>::JList_Iterator& JList<Data>::JList_Iterator::operator=(const JList_Iterator& data)
{
	m_Ptr = data.m_Ptr;
	return *this;
}
/* �ݺ��� �̵� ������ */
template<class Data>
typename JList<Data>::JList_Iterator& JList<Data>::JList_Iterator::operator++()
{
	m_Ptr = m_Ptr->right;
	return *this;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::JList_Iterator::operator++(const int idx)
{
	auto result = *this;
	m_Ptr = m_Ptr->right;
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::JList_Iterator::operator+(const int idx)
{
	auto result = *this;
	for (int i = 0; i < idx; ++i)
	{
		result.m_Ptr = result.m_Ptr->right;
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator& JList<Data>::JList_Iterator::operator--()
{
	m_Ptr = m_Ptr->left;
	return *this;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::JList_Iterator::operator--(const int idx)
{
	auto result = *this;
	m_Ptr = m_Ptr->left;
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator JList<Data>::JList_Iterator::operator-(const int idx)
{
	auto result = *this;
	for (int i = 0; i < idx; ++i)
	{
		result.m_Ptr = result.m_Ptr->left;
	}
	return result;
}
template<class Data>
typename JList<Data>::JList_Iterator& JList<Data>::JList_Iterator::operator+=(const int idx)
{
	for (int i = 0; i < idx; ++i)
	{
		m_Ptr = m_Ptr->right;
	}
	return *this;
}
template<class Data>
typename JList<Data>::JList_Iterator& JList<Data>::JList_Iterator::operator-=(const int idx)
{
	for (int i = 0; i < idx; ++i)
	{
		m_Ptr = m_Ptr->left;
	}
	return *this;
}

// �ݺ��� �� ����
template<class Data>
bool JList<Data>::JList_Iterator::operator==(const JList_Iterator& rhs) const
{
	if (this->m_Ptr == rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JList<Data>::JList_Iterator::operator!=(const JList_Iterator& rhs) const
{
	if (this->m_Ptr != rhs.m_Ptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JList<Data>::JList_Iterator::operator>(const JList_Iterator& rhs) const
{
	ListNode* Cur1 = m_Ptr;
	ListNode* Cur2 = rhs.m_Ptr;
	if (Cur1 == nullptr || Cur2 == nullptr)
	{
		return false;
	}
	while (Cur1 != nullptr && Cur2 != nullptr)
	{
		Cur1 = Cur1->right;
		Cur2 = Cur2->right;
	}
	if (Cur1 == nullptr)
	{
		return true;
	}
	return false;
}
template<class Data>
bool JList<Data>::JList_Iterator::operator<(const JList_Iterator& rhs) const
{
	ListNode* Cur1 = m_Ptr;
	ListNode* Cur2 = rhs.m_Ptr;
	if (Cur1 == nullptr || Cur2 == nullptr)
	{
		return false;
	}
	while (Cur1 != nullptr && Cur2 != nullptr)
	{
		Cur1 = Cur1->right;
		Cur2 = Cur2->right;
	}
	if (Cur1 == nullptr)
	{
		return false;
	}
	return true;
}
template<class Data>
bool JList<Data>::JList_Iterator::operator>=(const JList_Iterator& rhs) const
{
	if ( (*this) < rhs)
	{
		return false;
	}
	return true;
}
template<class Data>
bool JList<Data>::JList_Iterator::operator<=(const JList_Iterator& rhs) const
{
	if ((*this) > rhs)
	{
		return false;
	}
	return true;
}
