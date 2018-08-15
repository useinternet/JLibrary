#pragma once
#include"JPair.h"
#include"JArray.h"
#include"JList.h"


template<typename Key,typename Data, int len = 1000>
class JHash_Map
{
private:
	using HashData = JPair<Key, Data>;
	using HashNode = JList<HashData>;
	typedef struct ItInfo
	{
		JArray<HashNode>* Array;
		size_t ArrayIndex;
	    size_t ListIndex;

		bool operator==(const ItInfo& info)
		{
			if (Array == info.Array && 
				ArrayIndex == info.ArrayIndex && 
				ListIndex == info.ListIndex)
			{
				return true;
			}
			return false;
		}
	}ItInfo;
	class JHash_Map_Iterator;
protected:
	JArray<HashNode> m_Array;
	JArray<ItInfo>   m_IndexArray;
	std::hash<Key> Hashing;
	size_t m_Size;
public:
	JHash_Map();
	JHash_Map(JHash_Map& copy);
	~JHash_Map();


	void insert(const HashData& data);
	void remove(const Key& key);
	void clear();
	JHash_Map_Iterator begin();
	JHash_Map_Iterator end();

	HashData safe_index(const Key& key);
	HashData& operator[](const Key& key);
	JHash_Map& operator=(const JHash_Map& map);

	void Write_cpp();
public:
	class JHash_Map_Iterator
	{
	protected:
		friend class JHash_Map<Key, Data,len>;
		ItInfo* pointer;
	public:
		JHash_Map_Iterator();
		JHash_Map_Iterator(ItInfo* info);
		JHash_Map_Iterator(const JHash_Map_Iterator& copy);
		~JHash_Map_Iterator();


		HashData* operator->();
		HashData& operator*();

		/* ���� ������ */
		JHash_Map_Iterator& operator=(const JHash_Map_Iterator& data);
		/* �ݺ��� �̵� ������ */
		JHash_Map_Iterator& operator++();
		JHash_Map_Iterator operator++(const int idx);
		JHash_Map_Iterator operator+(const int idx);

		JHash_Map_Iterator& operator--();
		JHash_Map_Iterator operator--(const int idx);
		JHash_Map_Iterator operator-(const int idx);

		JHash_Map_Iterator& operator+=(const int  idx);
		JHash_Map_Iterator& operator-=(const int idx);

		// �ݺ��� �� ����
		bool operator==(const JHash_Map_Iterator& rhs);
		bool operator!=(const JHash_Map_Iterator& rhs);

		bool operator>(const JHash_Map_Iterator& rhs);
		bool operator<(const JHash_Map_Iterator& rhs);
		bool operator>=(const JHash_Map_Iterator& rhs);
		bool operator<=(const JHash_Map_Iterator& rhs);
	};
};
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map()
{
	m_Array.Init(len);
	m_IndexArray.reserve(len);
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map(JHash_Map& copy)
{
	m_Array.Init(len);
	m_IndexArray.reserve(len);

	for (auto iter = copy.begin(); iter< copy.end(); ++iter)
	{
		insert(JPair<Key, Data>(*iter));
	}
	// ���߿� �۾�
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::~JHash_Map()
{
	// ���߿� �۾�
}
template<typename Key, typename Data, int len>
void JHash_Map<Key, Data, len>::insert(const HashData& data)
{
	// �ؽ�
	size_t code = (Hashing(data.first) % len);
	
	//
	// �ݺ��ڸ� ���� ������ �����Ѵ�.
	ItInfo info = { &m_Array, code, m_Array[code].size() };
	m_IndexArray.push_back(info);

	//
	m_Array[code].push_back(data);
	m_Size++;
	int num = 0;
}
template<typename Key, typename Data, int len>
void JHash_Map<Key, Data, len>::remove(const Key& key)
{
	// �ؽ�
	size_t code = (Hashing(key) % len);
	//
	// �ؽ��� �ڵ�� �ش� �ε��� �����Ͽ� Ÿ�� ����Ʈ�� �����Ѵ�.
	JList<HashData>* TargetList = &m_Array[code];

	//
	size_t count = 0;
	// �ش� ����Ʈ���� Ű���� ���� ��带 ����.
	for (auto iter = TargetList->begin(); iter < TargetList->end();)
	{
		if (iter->first == key)
		{
			// �ݺ��� ���� ����
			ItInfo info = { &m_Array, code, count };
			auto target = m_IndexArray.find(info);
			m_IndexArray.remove(target);
			count++;

			// ����
			iter = TargetList->remove(iter);
			m_Size--;
		}
		else
		{
			++iter; 
		}
	}
}
template<typename Key, typename Data, int len>
void JHash_Map<Key, Data, len>::clear()
{
	m_Array.clear();
	m_IndexArray.clear();

	m_Array.Init(len);
	m_IndexArray.reserve(len);
	m_Size = 0;
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator 
JHash_Map<Key, Data, len>::begin()
{
	return JHash_Map_Iterator(&m_IndexArray[0]);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator
JHash_Map<Key, Data, len>::end()
{
	if (m_IndexArray.size() == 0)
	{
		return JHash_Map_Iterator(nullptr);
	}
	ItInfo* index = &m_IndexArray[m_IndexArray.size() - 1];
	return JHash_Map_Iterator(index + 1);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::HashData 
JHash_Map<Key, Data, len>::safe_index(const Key& key)
{
	// �ؽ�
	size_t code = (Hashing(key) % len);
	// �ؽ��� �ڵ�� �ش� �ε��� �����Ͽ� Ÿ�� ����Ʈ�� �����Ѵ�.
	JList<HashData>* TargetList = &m_Array[code];

	// Ž��
	for (auto iter = TargetList->begin(); iter < TargetList->end();)
	{
		if (iter->first == key)
		{
			return (*iter);
		}
		else
		{
			++iter;
		}
	}


	DebugLog(TEXT("Location   : JHash_Map.h \n"));
	DebugLog(TEXT("Class      : JHash_Map::safe_index() \n"));
	DebugLog(TEXT("Error      : key is nothing! \n"));
	assert(false);
	return HashData();
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::HashData&
JHash_Map<Key, Data, len>::operator[](const Key& key)
{
	// �ؽ�
	size_t code = (Hashing(key) % len);
	// �ؽ��� �ڵ�� �ش� �ε��� �����Ͽ� Ÿ�� ����Ʈ�� �����Ѵ�.
	JList<HashData>* TargetList = &m_Array[code];


	// Ž��
	for (auto iter = TargetList->begin(); iter < TargetList->end();)
	{
		if (iter->first == key)
		{
			return (*iter);
		}
		else
		{
			++iter;
		}
	}
	// ����ó�� Ű���� �������� �ʴ´�.
	// ���ο� ������ �����.
	DebugLog(TEXT("Location   : JHash_Map.h \n"));
	DebugLog(TEXT("Class      : JHash_Map::operator[] \n"));
	DebugLog(TEXT("Error      : key is nothing! \n"));
	HashData tmpData;
	tmpData.first = key;
	insert(tmpData);
	return this->operator[](key);
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>& JHash_Map<Key, Data, len>::operator=(const JHash_Map& map)
{
	for (auto& iter : copy)
	{
		this->insert(JPair<Key, Data>(iter));
	}
}
template<typename Key, typename Data, int len>
void JHash_Map<Key, Data, len>::Write_cpp()
{
	std::cout << "Hash_Map~~!" << endl;
	std::cout << " Size : " << m_Size << endl;
	for (size_t i = 0; i < len; ++i)
	{
		if (m_Array[i].size())
		{
			cout << "Key : " << m_Array[i][0].first << endl;
			cout << "Count : " << m_Array[i].size() << endl;
		}
	}
}








// �ݺ���



template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map_Iterator::JHash_Map_Iterator()
{
	pointer = nullptr;
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map_Iterator::JHash_Map_Iterator(ItInfo* info)
{
	pointer = info;
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map_Iterator::JHash_Map_Iterator(const JHash_Map_Iterator& copy)
{
	pointer = copy.pointer;
}
template<typename Key, typename Data, int len>
JHash_Map<Key, Data, len>::JHash_Map_Iterator::~JHash_Map_Iterator()
{

}

template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::HashData*
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator->()
{
	size_t AIndex = pointer->ArrayIndex;
	size_t LIndex = pointer->ListIndex;
	return &( (*pointer->Array)[AIndex][LIndex] );
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::HashData&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator*()
{
	size_t AIndex = pointer->ArrayIndex;
	size_t LIndex = pointer->ListIndex;
	return (*pointer->Array)[AIndex][LIndex];
}

/* ���� ������ */
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator=(const JHash_Map_Iterator& data)
{
	pointer = data.pointer;
}
/* �ݺ��� �̵� ������ */
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator++() // ����
{
	pointer++;
	return *this;
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator++(const int idx)
{
	auto result = pointer;
	pointer++;
	return JHash_Map_Iterator(result);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator+(const int idx)
{
	auto result = pointer + idx;
	return JHash_Map_Iterator(result);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator--()
{
	pointer--;
	return *this;
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator--(const int idx)
{
	auto result = pointer;
	pointer--;
	return JHash_Map_Iterator(result);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator-(const int idx)
{
	auto result = pointer - idx;
	return JHash_Map_Iterator(result);
}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator+=(const int  idx)
{
	pointer = pointer + idx;
	return *this;

}
template<typename Key, typename Data, int len>
typename JHash_Map<Key, Data, len>::JHash_Map_Iterator&
JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator-=(const int idx)
{
	pointer = pointer - idx;
	return *this;
}

// �ݺ��� �� ����
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator==(const JHash_Map_Iterator& rhs) 
{
	if (pointer == rhs.pointer)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator!=(const JHash_Map_Iterator& rhs) 
{
	if (pointer != rhs.pointer)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator>(const JHash_Map_Iterator& rhs) 
{
	if (pointer > rhs.pointer)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator<(const JHash_Map_Iterator& rhs) 
{
	if (pointer < rhs.pointer)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator>=(const JHash_Map_Iterator& rhs) 
{
	if (pointer >= rhs.pointer)
	{
		return true;
	}
	return false;
}
template<typename Key, typename Data, int len>
bool JHash_Map<Key, Data, len>::JHash_Map_Iterator::operator<=(const JHash_Map_Iterator& rhs) 
{
	if (pointer <= rhs.pointer)
	{
		return true;
	}
	return false;
}