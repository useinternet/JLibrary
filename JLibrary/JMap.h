#pragma once
#include"JPair.h"
#include"AlgorithmFunctor.h"

// Ž���� �����������ؼ� ����.. �ٽ� ����
template<class Key,class Data,class CompareFunctor = Less_Functor<Key>>
class JMap
{
public:
	class JMap_Iterator;
protected:
	typedef JPair<Key, Data> NodeData;
	enum Color
	{
		Red,Black
	};
	// ��������
	// @param left    : ���� �ڽ� ���
	// @param right   : ������ �ڽ� ���
	// @param parent  : �θ� ���
	// @param end     : ���������( �ݺ��� ����� )
	// @param nil     : �ٻ����(�ݺ��� �����)
	// @param data    : JPair<Key,Data> Ű���� �����Ͱ��� �������ִ� ������
	// @param color   : ��� �� ( ����, �� )
	typedef struct RBNode
	{
		RBNode* left = nullptr;
		RBNode* right = nullptr;
		RBNode* parent = nullptr;
		RBNode* end = nullptr;
		RBNode* nil = nullptr;
		NodeData* data = nullptr;
		Color color = Red;
	}RBNode;
protected:
	// @param m_Root   : ��Ʈ���
	// @param m_End    : ��������� (�ݺ��� ����ũ ���)
	// @param m_Nil    : �ٻ����
	// @param m_Size   : ��� ����
	// @param func     : �� �Լ�
	RBNode* m_Root;
	RBNode* m_End;
	RBNode* m_Nil;
	size_t m_Size;
	CompareFunctor func;
public:
	// ������ �� �Ҹ���
	JMap();
	JMap(const JMap& copy);
	~JMap();

	// ���� �� ����
	void insert(const NodeData& data);
	JMap_Iterator remove(const Key& key);
	void clear();

	// Ž��
	JMap_Iterator begin();
	JMap_Iterator end();
	JMap_Iterator find(const Key& key);
	bool empty();
	size_t size();

	// ������ �����ε�
	Data& operator[](const Key& key);
	JMap& operator=(JMap& map);
private:
	void EquipEndNode();
	void DeleteEnd();
	RBNode* NodeFind(const Key& key, RBNode* node);
public:
	// ��� �ӽ�
	void Write_cpp();

private:
	RBNode* CreateNode(RBNode* node);
	void DestoryNode(RBNode** node);
	RBNode* GetBrotherNode(RBNode* node);

	// ���� ���� �Լ�
	RBNode* CompareDataInsert(RBNode* Root,RBNode* newNode);
	void RunAdditionalTasks(RBNode* node);
	void Case1_RootNode_is_nullptr(RBNode* node);
	void Case2_Parent_is_Black(RBNode* node);
	void Case3_Parent_And_Parent_Brother_is_Red(RBNode* node);
	void Case4_Parent_And_Child_is_Red(RBNode* node);
	void Case5_Additional_Parent_Brother_is_Black(RBNode* node);
	void LeftRotation(RBNode* parentnode);
	void RightRotation(RBNode* parentnode);

	// ���� ���� �Լ�
	JMap_Iterator RemoveEntry(const Key& key);
	void Remove_Case1(RBNode* node);
	void Remove_Case2(RBNode* node);
	void Remove_Case3(RBNode* node);
	void Remove_Case4(RBNode* node);
	void Remove_Case5(RBNode* node);
	void Remove_Case6(RBNode* node);
	void FindDeleteNodeReplace(RBNode* ReplaceNode, RBNode* node);

public:
	class JMap_Iterator
	{
	private:
		friend class JMap<Key, Data, CompareFunctor>;
	protected:
		RBNode* pointer;
	protected:
		RBNode* get() { return pointer; }
		void set(RBNode* node) { pointer = node; }
	public:
		JMap_Iterator();
		JMap_Iterator(RBNode* node);
		~JMap_Iterator();
		// ������ �����ε�
		NodeData* operator->();
		NodeData& operator*();

		//���� ������
		JMap_Iterator& operator=(const JMap_Iterator& iter);

		// �ݺ��� �̵� ������
		JMap_Iterator& operator++();
		JMap_Iterator operator++(const int idx); //���� ������

		JMap_Iterator& operator--();
		JMap_Iterator operator--(const int idx);



		bool operator==(const JMap_Iterator& rhs);
		bool operator!=(const JMap_Iterator& rhs);

		bool operator>(const JMap_Iterator& rhs);
		bool operator>=(const JMap_Iterator& rhs);
		bool operator<(const JMap_Iterator& rhs);
		bool operator<=(const JMap_Iterator& rhs);
	private:
		RBNode* maximum(RBNode* node);
		RBNode* minimum(RBNode* node);
		RBNode* next(RBNode* node);
		RBNode* prev(RBNode* node);
	};
};
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::JMap() 
{
	m_Root = nullptr;
	m_End = CreateNode(m_End);
	m_Nil = CreateNode(m_Nil);
	m_Nil->color = Black;
	m_Size = 0;
}
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::JMap(const JMap& copy)
{
	this->operator=(copy);
}
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::~JMap()
{
	clear();
	DestoryNode(&m_End);
	DestoryNode(&m_Nil);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::insert(const NodeData& data)
{
	// ���Ǹ� ���� End ��� ����
	DeleteEnd();

	// ���ο� ��� �ۼ�
	RBNode* newNode = nullptr;
	newNode = CreateNode(newNode);
	newNode->left = m_Nil;
	newNode->right = m_Nil;
	*(newNode->data) = data;


	// ��Ʈ ��尡 nullptr �̶��
	if (m_Root == nullptr)
	{
		m_Root = newNode;
	}
	else
	{
		// ������ ����
		newNode = CompareDataInsert(m_Root, newNode);
	}

	if (newNode == nullptr)
	{
		//����ó�� Ű ���� �Ȱ������� �Դٴ°�
		return;
	}

	// ������ �籸��
	RunAdditionalTasks(newNode);

	// End ��� �ٽ� ���̱�
	EquipEndNode();
	m_Size++;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::clear()
{
	// m_Root��尡 ������ִٸ�.. �׳� ����
	if (m_Root == nullptr)
	{
		return;
	}
	// ���������� ������Ų��.
	for (auto iter = begin(); iter < end(); )
	{
		iter = remove(iter->first);
	}
	m_Root = nullptr;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator
JMap<Key, Data, CompareFunctor>::remove(const Key& key)
{
	// �ݺ��� �۾� ����
	JMap_Iterator result(nullptr);

	// ������ִٸ� �׳� ����
	if (empty())
	{
		return result;
	}
	// ���� ����
	result = RemoveEntry(key);

	m_Size--;
	return result;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator 
JMap<Key, Data, CompareFunctor>::begin()
{
	JMap_Iterator iter;
	return 	iter.minimum(m_Root);;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator
JMap<Key, Data, CompareFunctor>::end()
{
	return m_End;
}

template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator
JMap<Key, Data, CompareFunctor>::find(const Key& key)
{
	RBNode* node = NodeFind(key, m_Root);
	if (node == nullptr)
	{
		// ����ó��
		// Ű ���� ������������
	}
	return JMap_Iterator(node);
}
template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::empty()
{
	if (m_Root == nullptr)
	{
		return true;
	}
	return false;
}
template<class Key, class Data, class CompareFunctor>
size_t JMap<Key, Data, CompareFunctor>::size()
{
	return m_Size;
}
template<class Key, class Data, class CompareFunctor>
Data& JMap<Key, Data, CompareFunctor>::operator[](const Key& key)
{
	bool bassert = true;
	RBNode* result = NodeFind(key, m_Root);
	if (result == nullptr)
	{
		bassert = false;
		DebugLog(TEXT("Location   : JMap.h \n"));
		DebugLog(TEXT("Class      : JMap::operator[] \n"));
		DebugLog(TEXT("Error      : Key is Nothing \n"));
		assert(bassert);
	}
	return result->data->second;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>&
JMap<Key, Data, CompareFunctor>::operator=(JMap& map)
{
	if(!map.empty())
	{
		for (auto& iter : map)
		{
			this->insert(iter);
		}
	}
	return *this;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::EquipEndNode()
{
	if (m_Root == nullptr)
	{
		return;
	}
	// �Լ� ������ ���� �����Ͽ� �ǳ��� End ��带 ���δ�.
	RBNode* cur = m_Root;
	if (cur == nullptr)
	{
		int result = 0;
	}
	while (cur->right != m_Nil )
	{
		cur = cur->right;
		if (cur == nullptr)
		{
			int result = 0;
		}
	}
	cur->right = m_End;
	m_End->parent = cur;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::DeleteEnd()
{
	if (m_Root == nullptr)
	{
		return;
	}
	RBNode* cur = m_Root;
	while (cur->right != m_End)
	{
		cur = cur->right;
	}
	cur->right = m_Nil;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::NodeFind(const Key& key,RBNode* node)
{
	bool bFind = false;
	// ��尡 �ٻ���� / End��� / nullptr�̶�� nullptr�� ��ȯ�Ѵ�.
	if (node == m_Nil || node == m_End || node == nullptr)
	{
		return nullptr;
	}

	RBNode* cur = node;

	while (cur != m_Nil && cur != m_End && cur != nullptr)
	{
		if (func(key, cur->data->first))
		{
			cur = cur->left;
		}
		else if (func(cur->data->first , key))
		{
			cur = cur->right;
		}
		else
		{
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		cur = nullptr;
	}

	return cur;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Write_cpp()
{
	std::cout << "Size : " << m_Size << endl;
	std::cout<<std::endl;
	for (auto& iter : *this)
	{
		std::cout << "Key : " << iter.first << endl;
		std::cout << "Data : " << iter.second << endl;
		std::cout << std::endl;
	}
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::CreateNode(RBNode* node)
{
	node = new RBNode;
	node->data = new NodeData;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = nullptr;
	node->end = m_End;
	node->nil = m_Nil;

	return node;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::DestoryNode(RBNode** node)
{
	delete (*node)->data;
	(*node)->data = nullptr;

	delete (*node);
	(*node) = nullptr;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::GetBrotherNode(RBNode* node)
{
	if (node == node->parent->left)
	{
		return node->parent->right;
	}
	else
	{
		return node->parent->left;
	}
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::CompareDataInsert(RBNode* Root, RBNode* newNode)
{
	// ���Լ��� ��ȯ������ �켱������ ���Ͽ� ��� ����
	if (func(Root->data->first, newNode->data->first))
	{
		if (Root->right == m_Nil)
		{
			Root->right = newNode;
			newNode->parent = Root;
			return newNode;
		}
		return CompareDataInsert(Root->right, newNode);
	}
	if (func(newNode->data->first, Root->data->first))
	{
		if (Root->left == m_Nil)
		{
			Root->left = newNode;
			newNode->parent = Root;
			return newNode;
		}
		return CompareDataInsert(Root->left, newNode);
	}

	return nullptr;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::RunAdditionalTasks(RBNode* node)
{
	Case1_RootNode_is_nullptr(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case1_RootNode_is_nullptr(RBNode* node)
{
	// ����� �θ� ���°�� Root ����� ����
	if (node->parent == nullptr)
	{
		node->color = Black;
		return;
	}

	// ���� ���׿� �ش��� ���� �ʴ°�� ���� ���̽� ����
	Case2_Parent_is_Black(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case2_Parent_is_Black(RBNode* node)
{
	if (node->parent->color == Black)
	{
		return;
	}

	Case3_Parent_And_Parent_Brother_is_Red(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case3_Parent_And_Parent_Brother_is_Red(RBNode* node)
{
	RBNode* child = node;
	RBNode* parent = child->parent;
	RBNode* grand_parent = child->parent->parent;
	RBNode* parent_brother = nullptr;
	if (parent == grand_parent->right)
	{
		parent_brother = grand_parent->left;
	}
	else
	{
		parent_brother = grand_parent->right;
	}


	// �θ� ������ nullptr�� �ƴϰ� Red�� �̶��
	if (parent_brother != nullptr && parent_brother->color == Red)
	{
		// �θ�� �θ� ������ ���� Black���� �ٲٰ� �Ҿƺ����� ���� Red�� �ٲ۴�.
		parent->color         = Black;
		parent_brother->color = Black;
		grand_parent->color   = Red;

		// �Ҿƺ����� Root �ϰ�쵵 �����Ƿ� Case1 ���� �ٽð˻��Ѵ�.
		Case1_RootNode_is_nullptr(grand_parent);

		return;
	}

	// ���� ���̽� ����
	Case4_Parent_And_Child_is_Red(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case4_Parent_And_Child_is_Red(RBNode* node)
{
	RBNode* child = node;
	RBNode* parent = child->parent;
	RBNode* grand_parent = child->parent->parent;


	// �θ� ��尡 �Ҿƺ��� ����� ���� && �ڽĳ�尡 �θ����� �����ʿ� �����Ұ��
	if (grand_parent->left == parent && parent->right == child)
	{

		// ���� ȸ��
		LeftRotation(parent);
		child = child->left;
	}
	// �ݴ�
	else if (grand_parent->right == parent && parent->left == child)
	{
		// ������ ȸ��
		RightRotation(parent);
		child = child->right;
	}

	// ���� �۾�
	Case5_Additional_Parent_Brother_is_Black(child);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case5_Additional_Parent_Brother_is_Black(RBNode* node)
{
	RBNode* child = node;
	RBNode* parent = child->parent;
	RBNode* grand_parent = child->parent->parent;

	parent->color = Black;
	grand_parent->color = Red;

	if (child == parent->left)
	{
		RightRotation(grand_parent);
	}
	else
	{
		LeftRotation(grand_parent);
	}
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::LeftRotation(RBNode* parentnode)
{
	RBNode *cur = parentnode->right;

	/* �� ���� �ڽĿͰ�  �θ� ��� �������� ���� */
	parentnode->right = cur->left;
	if (cur->left!= m_Nil) {
		cur->left->parent = parentnode;
	}

	/* ���� �θ��� ��ġ�� �ٲ۴�. */
	cur->parent = parentnode->parent;
	if (parentnode->parent == nullptr) {
		/* parent�� root��� �ǹ��̹Ƿ� root�� �����Ѵ�. */
		m_Root = cur;
	}
	else {
		if (parentnode == parentnode->parent->left) {
			/* �θ� node�� �Ҿƹ��� node�� ���ʿ� �ִ� ���. */
			parentnode->parent->left = cur;
		}
		else {
			/* �θ� node�� �Ҿƹ��� node�� �����ʿ� �ִ� ���. */
			parentnode->parent->right = cur;
		}
	}

	/* �ٲ� ��ġ�� ���� �θ� ���� */
	parentnode->parent = cur;
	cur->left = parentnode;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::RightRotation(RBNode* parentnode)
{
	RBNode *cur = parentnode->left;

	/* �� ������ �ڽİ� �θ� ���� �ڽĳ�带 ���� */
	parentnode->left = cur->right;
	if (cur->right != m_Nil) {
		cur->right->parent = parentnode;
	}

	/* ���� parent�� ��ġ�� �ٲ۴�. */
	cur->parent = parentnode->parent;
	if (parentnode->parent == nullptr) {
		/* parent�� root��� �ǹ��̹Ƿ� root�� �����Ѵ�. */
		m_Root = cur;
	}
	else {
		if (parentnode == parentnode->parent->left) {
			/* �θ� node�� �Ҿƹ��� node�� ���ʿ� �ִ� ���. */
			parentnode->parent->left = cur;
		}
		else {
			/* �θ� node�� �Ҿƹ��� node�� �����ʿ� �ִ� ���. */
			parentnode->parent->right = cur;
		}
	}

	/* �ٲ� ��ġ�� ���� �θ� ���� */
	cur->right = parentnode;
	parentnode->parent = cur;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator
JMap<Key, Data, CompareFunctor>::RemoveEntry(const Key& key)
{
	RBNode* Target = NodeFind(key, m_Root);
	RBNode* RemoveNode = nullptr;
	RBNode* cur = nullptr;
	JMap_Iterator result(Target);
	Key resultKey= (++result)->first;

	// ���Ǹ� ���� End��带 ��� ���ش�.
	DeleteEnd();

	// Ÿ���� �ܸ� ����̸� �״�� �������� �����Ѵ�.
	if (Target->right == m_Nil && Target->left == m_Nil)
	{
		RemoveNode = Target;
	}
	// Ÿ���� ��ü�� ���� �켱���� ��带 Ž���Ѵ�.
	else if (Target->right == m_Nil)
	{
		cur = Target->left;
		while (cur->right != m_Nil)
		{
			cur = cur->right;
		}
		RemoveNode = cur;
	}
	else
	{
		cur = Target->right;
		while (cur->left != m_Nil)
		{
			cur = cur->left;
		}
		RemoveNode = cur;
	}


	// Ž���� �Ϸ�Ǹ� Ÿ�� �����͸� Ž���� ����� ������ ��ü
	FindDeleteNodeReplace(Target, RemoveNode);

	// Ÿ���� ���� ���̸�
	if (Target->color == Black)
	{
		// ���� ����� ���� ������̸�
		if (RemoveNode->color == Red)
		{
			RemoveNode->color = Black;
		}
		// ��������� ���� ���̸�
		else
		{
			// ���̽� 1�� ����
			Remove_Case1(RemoveNode);
		}
	}

	// ���� ����� �θ� �ְ� ������尡 �θ��� ������ ����̸�
	if (RemoveNode->parent && RemoveNode == RemoveNode->parent->right)
	{
		// ��������� �θ� ����� ������ ��带 �ٻ����� ��ü�ϰ� �ش� ������带 �����Ѵ�.
		RemoveNode->parent->right = m_Nil;
		DestoryNode(&RemoveNode);
	}
	// ���� ����� �θ� �ְ� ������尡 �θ��� �ަU ����̸�
	else if(RemoveNode->parent && RemoveNode == RemoveNode->parent->left)
	{
		// ��������� �θ� ����� ���� ��带 �ٻ����� ��ü�ϰ� �ش� ������带 �����Ѵ�.
		RemoveNode->parent->left = m_Nil;
		DestoryNode(&RemoveNode);
	}
	// ���� �ش������� ���������ʴ°�쿡�� ������尡 ��Ʈ����̹Ƿ� ��Ʈ��带 �����Ѵ�.
	else if(RemoveNode->parent == nullptr)
	{
		DestoryNode(&m_Root);
		return end();
	}

	// ��������� ���� �� ����Ű�� �ݺ��ڸ� �����Ѵ�.
	RBNode* ResultNode = NodeFind(resultKey,m_Root);
	result.set(ResultNode);


	// ���ǻ� End ��带 ��������� �ٽ� ���δ�.
	EquipEndNode();
	return result;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case1(RBNode* node)
{
	// ����� �θ� �����Ѵٸ�
	if (node->parent != nullptr)
	{
		Remove_Case2(node);
	}
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case2(RBNode* node)
{
	RBNode* brother = GetBrotherNode(node);

	if (brother->color == Red)
	{
		node->parent->color = Red;
		brother->color = Black;

		if (node == node->parent->left)
		{
			LeftRotation(node->parent);
		}
		else
		{
			RightRotation(node->parent);
		}
	}

	Remove_Case3(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case3(RBNode* node)
{
	RBNode* brother = GetBrotherNode(node);

	if (node->parent->color  == Black && brother->color        == Black &&
		brother->left->color == Black && brother->right->color == Black)
	{
		brother->color = Red;
		Remove_Case1(node->parent);
	}
	else
	{
		Remove_Case4(node);
	}
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case4(RBNode* node)
{
	RBNode* brother = GetBrotherNode(node);

	if (node->parent->color  == Red   && brother->color        == Black &&
		brother->left->color == Black && brother->right->color == Black)
	{
		brother->color = Red;
		node->parent->color = Black;
	}
	else
	{
		Remove_Case5(node);
	}
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case5(RBNode* node)
{
	RBNode* brother = GetBrotherNode(node);


	if (node == node->parent->left &&
		brother->right->color == Black && brother->left->color == Red)
	{
		brother->color = Red;
		brother->left->color = Black;
		RightRotation(brother);
	}
	else if (node == node->parent->right &&
		brother->left->color == Black && brother->right->color == Red)
	{
		brother->color = Red;
		brother->right->color = Black;
		LeftRotation(brother);
	}
	Remove_Case6(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case6(RBNode* node)
{
	RBNode* brother = GetBrotherNode(node);

	brother->color = node->parent->color;
	node->parent->color = Black;

	if (node == node->parent->left)
	{
		brother->right->color = Black;
		LeftRotation(node->parent);
	}
	else
	{
		brother->left->color = Black;
		RightRotation(node->parent);
	}
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::FindDeleteNodeReplace(RBNode* ReplaceNode, RBNode* node)
{
	if (node->right == m_Nil && node->left == m_Nil)
	{
		NodeData tmp = *(node->data);
		*(ReplaceNode->data) = tmp;
		return;
	}
	if (ReplaceNode->right == node)
	{
		NodeData tmp = *(node->data);
		*(ReplaceNode->data) = tmp;
		FindDeleteNodeReplace(node, node->right);
	}
	else
	{
		NodeData tmp = *(node->data);
		*(ReplaceNode->data) = tmp;
		FindDeleteNodeReplace(node, node->left);
	}
}

// JMap_Iterator
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::JMap_Iterator::JMap_Iterator()
{
	pointer = nullptr;
}
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::JMap_Iterator::JMap_Iterator(RBNode* node)
{
	pointer = node;
}
template<class Key, class Data, class CompareFunctor>
JMap<Key, Data, CompareFunctor>::JMap_Iterator::~JMap_Iterator() {}


// ������ �����ε�
template<class Key, class Data, class CompareFunctor>
typename JMap<Key,Data, CompareFunctor>::NodeData* 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator->()
{
	return pointer->data;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::NodeData& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator*()
{
	return *(pointer->data);
}

//���� ������
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator=(const JMap_Iterator& iter)
{
	this->pointer = iter.pointer;

	return *this;
}

// �ݺ��� �̵� ������

template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator++()
{
	pointer = next(pointer);
	return *this;
	// ���� ������
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator++(const int idx)
{
	JMap<Key, Data, CompareFunctor>::JMap_Iterator nextIter;
	nextIter.pointer = pointer;
	pointer = next(pointer);
	return nextIter;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator--()
{
	pointer = prev(pointer);
	return *this;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator--(const int idx)
{
	JMap<Key, Data, CompareFunctor>::JMap_Iterator prevIter;
	prevIter.pointer = pointer;
	pointer = prev(pointer);
	return prevIter;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator==(const JMap_Iterator& rhs)
{
	if (pointer == rhs.pointer)
	{
		return true;
	}
	return false;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator!=(const JMap_Iterator& rhs)
{
	if (pointer != rhs.pointer)
	{
		return true;
	}
	return false;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator>(const JMap_Iterator& rhs)
{
	size_t count1 = 0;
	size_t count2 = 0;
	RBNode* node1 = this->pointer;
	RBNode* node2 = rhs.pointer;

	// ���� �ϳ��� nullptr�̶�� �ٷ� �ߴ��Ѵ�.
	if (node1 == nullptr || node2 == nullptr)
	{
		return false;
	}
	RBNode* end = node1->end;
	// node1 �� node2 �����ϳ��� ������ ��尡 ���ö����� ������.
	while (node1 != end && node2 != end)
	{
		node1 = next(node1);
		node2 = next(node2);
	}
	// ���� node2�� ������ ������ �������� ���ߴٸ� true�� ��ȯ�Ѵ�.
	if (node2 != end)
	{
		return true;
	}

	return false;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator>=(const JMap_Iterator& rhs)
{
	if (rhs.pointer == (*this).pointer ||  (*this) > rhs)
	{
		return true;
	}
	return false;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator<(const JMap_Iterator& rhs)
{
	if (rhs.pointer == (*this).pointer || (*this) > rhs)
	{
		return false;
	}
	return true;
}

template<class Key, class Data, class CompareFunctor>
bool JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator<=(const JMap_Iterator& rhs)
{
	if ((*this) > rhs)
	{
		return false;
	}
	return true;
}

template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::JMap_Iterator::maximum(RBNode* node)
{
	// ���� ������ ��� �̸� ��ȯ
	if (node->right == node->end || node->right == node->nil)
	{
		return node;
	}
	return maximum(node->right);
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::JMap_Iterator::minimum(RBNode* node)
{
	// ���� ���� ��� �̸� ��ȯ
	if (node->left == node->nil)
	{
		return node;
	}
	return minimum(node->left);
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::JMap_Iterator::next(RBNode* node)
{
	// ������ �� ����� end�� ��ȯ
	if (node == node->end)
	{
		return node->end;
	}

	// ���� ������ �ڽ��� �����Ѵٸ� ������ �ڽ��� �� ����(���������ΰ���)
	if (node->right != node->nil)
	{
		return minimum(node->right);
	}

	// ������ġ�� ���� ����� �θ���ϰ�
	RBNode* cur = node->parent;

	// ��尡 cur�� �������ڽ��� �ƴҶ����� cur�� �ø���.
	while (cur != nullptr && node == cur->right)
	{
		node = cur;
		cur = cur->parent;
	}

	return cur;
}
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::RBNode*
JMap<Key, Data, CompareFunctor>::JMap_Iterator::prev(RBNode* node)
{
	// ���� ���� ��尡 �����Ѵٸ� ���� �ڽ��� �� ������(ū �����ΰ���)
	if (node->left != node->nil)
	{
		return maximum(node->left);
	}

	// ������ġ�� ���� ����� �θ���ϰ�
	RBNode* cur = node->parent;
	// ��尡 cur�� ���� �ڽ��� �ƴҶ� ���� cur �� �ø���.
	while (cur != nullptr && node == cur->left)
	{
		node = cur;
		cur = cur->parent;
	}
	return cur;
}

