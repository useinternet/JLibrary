#pragma once
#include"JPair.h"
#include"AlgorithmFunctor.h"

// 탐색을 중위순위로해서 문제.. 다시 변경
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
	// 레드블랙노드
	// @param left    : 왼쪽 자식 노드
	// @param right   : 오른쪽 자식 노드
	// @param parent  : 부모 노드
	// @param end     : 마지막노드( 반복자 저장용 )
	// @param nil     : 잎새노드(반복자 저장용)
	// @param data    : JPair<Key,Data> 키값과 데이터값을 가지고있는 데이터
	// @param color   : 노드 색 ( 레드, 블랙 )
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
	// @param m_Root   : 루트노드
	// @param m_End    : 마지막노드 (반복자 훼이크 노드)
	// @param m_Nil    : 잎새노드
	// @param m_Size   : 요소 갯수
	// @param func     : 비교 함수
	RBNode* m_Root;
	RBNode* m_End;
	RBNode* m_Nil;
	size_t m_Size;
	CompareFunctor func;
public:
	// 생성자 및 소멸자
	JMap();
	JMap(const JMap& copy);
	~JMap();

	// 삽입 및 삭제
	void insert(const NodeData& data);
	JMap_Iterator remove(const Key& key);
	void clear();

	// 탐색
	JMap_Iterator begin();
	JMap_Iterator end();
	JMap_Iterator find(const Key& key);
	bool empty();
	size_t size();

	// 연산자 오버로딩
	Data& operator[](const Key& key);
	JMap& operator=(JMap& map);
private:
	void EquipEndNode();
	void DeleteEnd();
	RBNode* NodeFind(const Key& key, RBNode* node);
public:
	// 출력 임시
	void Write_cpp();

private:
	RBNode* CreateNode(RBNode* node);
	void DestoryNode(RBNode** node);
	RBNode* GetBrotherNode(RBNode* node);

	// 삽입 관련 함수
	RBNode* CompareDataInsert(RBNode* Root,RBNode* newNode);
	void RunAdditionalTasks(RBNode* node);
	void Case1_RootNode_is_nullptr(RBNode* node);
	void Case2_Parent_is_Black(RBNode* node);
	void Case3_Parent_And_Parent_Brother_is_Red(RBNode* node);
	void Case4_Parent_And_Child_is_Red(RBNode* node);
	void Case5_Additional_Parent_Brother_is_Black(RBNode* node);
	void LeftRotation(RBNode* parentnode);
	void RightRotation(RBNode* parentnode);

	// 삭제 관련 함수
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
		// 연산자 오버로딩
		NodeData* operator->();
		NodeData& operator*();

		//대입 연산자
		JMap_Iterator& operator=(const JMap_Iterator& iter);

		// 반복자 이동 연산자
		JMap_Iterator& operator++();
		JMap_Iterator operator++(const int idx); //후위 연산자

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
	// 편의를 위해 End 노드 삭제
	DeleteEnd();

	// 새로운 노드 작성
	RBNode* newNode = nullptr;
	newNode = CreateNode(newNode);
	newNode->left = m_Nil;
	newNode->right = m_Nil;
	*(newNode->data) = data;


	// 루트 노드가 nullptr 이라면
	if (m_Root == nullptr)
	{
		m_Root = newNode;
	}
	else
	{
		// 데이터 삽입
		newNode = CompareDataInsert(m_Root, newNode);
	}

	if (newNode == nullptr)
	{
		//예외처리 키 값이 똑같은것이 왔다는것
		return;
	}

	// 삽입후 재구성
	RunAdditionalTasks(newNode);

	// End 노드 다시 붙이기
	EquipEndNode();
	m_Size++;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::clear()
{
	// m_Root노드가 비어져있다면.. 그냥 리턴
	if (m_Root == nullptr)
	{
		return;
	}
	// 순차적으로 삭제시킨다.
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
	// 반복자 작업 셋팅
	JMap_Iterator result(nullptr);

	// 비어져있다면 그냥 리턴
	if (empty())
	{
		return result;
	}
	// 삭제 시작
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
		// 예외처리
		// 키 값이 존재하지않음
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
	// 게속 오른쪽 노드로 접근하여 맨끝에 End 노드를 붙인다.
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
	// 노드가 잎새노드 / End노드 / nullptr이라면 nullptr을 반환한다.
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
	// 비교함수의 반환값으로 우선순위를 정하여 노드 삽입
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
	// 노드이 부모가 없는경우 Root 노드라고 결정
	if (node->parent == nullptr)
	{
		node->color = Black;
		return;
	}

	// 위에 사항에 해당이 되지 않는경우 다음 케이스 실행
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


	// 부모 형제가 nullptr이 아니고 Red색 이라면
	if (parent_brother != nullptr && parent_brother->color == Red)
	{
		// 부모와 부모 형제의 색을 Black으로 바꾸고 할아부지의 색을 Red로 바꾼다.
		parent->color         = Black;
		parent_brother->color = Black;
		grand_parent->color   = Red;

		// 할아부지가 Root 일경우도 있으므로 Case1 부터 다시검사한다.
		Case1_RootNode_is_nullptr(grand_parent);

		return;
	}

	// 다음 케이스 실행
	Case4_Parent_And_Child_is_Red(node);
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Case4_Parent_And_Child_is_Red(RBNode* node)
{
	RBNode* child = node;
	RBNode* parent = child->parent;
	RBNode* grand_parent = child->parent->parent;


	// 부모 노드가 할아부지 노드의 왼쪽 && 자식노드가 부모노드의 오른쪽에 존재할경우
	if (grand_parent->left == parent && parent->right == child)
	{

		// 왼쪽 회전
		LeftRotation(parent);
		child = child->left;
	}
	// 반대
	else if (grand_parent->right == parent && parent->left == child)
	{
		// 오른쪽 회전
		RightRotation(parent);
		child = child->right;
	}

	// 다음 작업
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

	/* 내 왼쪽 자식와과  부모 노드 오른쪽을 연결 */
	parentnode->right = cur->left;
	if (cur->left!= m_Nil) {
		cur->left->parent = parentnode;
	}

	/* 나와 부모의 위치를 바꾼다. */
	cur->parent = parentnode->parent;
	if (parentnode->parent == nullptr) {
		/* parent가 root라는 의미이므로 root를 변경한다. */
		m_Root = cur;
	}
	else {
		if (parentnode == parentnode->parent->left) {
			/* 부모 node가 할아버지 node의 왼쪽에 있는 경우. */
			parentnode->parent->left = cur;
		}
		else {
			/* 부모 node가 할아버지 node의 오른쪽에 있는 경우. */
			parentnode->parent->right = cur;
		}
	}

	/* 바뀐 위치의 나와 부모를 연결 */
	parentnode->parent = cur;
	cur->left = parentnode;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::RightRotation(RBNode* parentnode)
{
	RBNode *cur = parentnode->left;

	/* 내 오른쪽 자식과 부모 왼쪽 자식노드를 연결 */
	parentnode->left = cur->right;
	if (cur->right != m_Nil) {
		cur->right->parent = parentnode;
	}

	/* 나와 parent의 위치를 바꾼다. */
	cur->parent = parentnode->parent;
	if (parentnode->parent == nullptr) {
		/* parent가 root라는 의미이므로 root를 변경한다. */
		m_Root = cur;
	}
	else {
		if (parentnode == parentnode->parent->left) {
			/* 부모 node가 할아버지 node의 왼쪽에 있는 경우. */
			parentnode->parent->left = cur;
		}
		else {
			/* 부모 node가 할아버지 node의 오른쪽에 있는 경우. */
			parentnode->parent->right = cur;
		}
	}

	/* 바뀐 위치의 나와 부모를 연결 */
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

	// 편의를 위해 End노드를 잠시 없앤다.
	DeleteEnd();

	// 타겟이 단말 노드이면 그대로 삭제노드로 지정한다.
	if (Target->right == m_Nil && Target->left == m_Nil)
	{
		RemoveNode = Target;
	}
	// 타겟의 대체할 다음 우선순의 노드를 탐색한다.
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


	// 탐색이 완료되면 타겟 데이터를 탐색된 노드의 값으로 대체
	FindDeleteNodeReplace(Target, RemoveNode);

	// 타겟의 색이 블랙이면
	if (Target->color == Black)
	{
		// 삭제 노드의 색이 레드색이면
		if (RemoveNode->color == Red)
		{
			RemoveNode->color = Black;
		}
		// 삭제노드의 색이 블랙이면
		else
		{
			// 케이스 1을 실행
			Remove_Case1(RemoveNode);
		}
	}

	// 삭제 노드의 부모가 있고 삭제노드가 부모의 오른쪽 노드이면
	if (RemoveNode->parent && RemoveNode == RemoveNode->parent->right)
	{
		// 삭제노드의 부모 노드의 오른쪽 노드를 잎새노드로 대체하고 해당 삭제노드를 삭제한다.
		RemoveNode->parent->right = m_Nil;
		DestoryNode(&RemoveNode);
	}
	// 삭제 노드의 부모가 있고 삭제노드가 부모의 왼쪾 노드이면
	else if(RemoveNode->parent && RemoveNode == RemoveNode->parent->left)
	{
		// 삭제노드의 부모 노드의 왼쪽 노드를 잎새노드로 대체하고 해당 삭제노드를 삭제한다.
		RemoveNode->parent->left = m_Nil;
		DestoryNode(&RemoveNode);
	}
	// 위에 해당조건이 만족되지않는경우에는 삭제노드가 루트노드이므로 루트노드를 삭제한다.
	else if(RemoveNode->parent == nullptr)
	{
		DestoryNode(&m_Root);
		return end();
	}

	// 삭제노드의 다음 을 가르키는 반복자를 생성한다.
	RBNode* ResultNode = NodeFind(resultKey,m_Root);
	result.set(ResultNode);


	// 편의상 End 노드를 뗴엇던것을 다시 붙인다.
	EquipEndNode();
	return result;
}
template<class Key, class Data, class CompareFunctor>
void JMap<Key, Data, CompareFunctor>::Remove_Case1(RBNode* node)
{
	// 노드의 부모가 존재한다면
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


// 연산자 오버로딩
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

//대입 연산자
template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator=(const JMap_Iterator& iter)
{
	this->pointer = iter.pointer;

	return *this;
}

// 반복자 이동 연산자

template<class Key, class Data, class CompareFunctor>
typename JMap<Key, Data, CompareFunctor>::JMap_Iterator& 
JMap<Key, Data, CompareFunctor>::JMap_Iterator::operator++()
{
	pointer = next(pointer);
	return *this;
	// 전위 연산자
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

	// 둘중 하나가 nullptr이라면 바로 중단한다.
	if (node1 == nullptr || node2 == nullptr)
	{
		return false;
	}
	RBNode* end = node1->end;
	// node1 와 node2 둘중하나가 마지막 노드가 나올때까지 돌린다.
	while (node1 != end && node2 != end)
	{
		node1 = next(node1);
		node2 = next(node2);
	}
	// 만약 node2가 마지막 노드까지 도달하지 못했다면 true를 반환한다.
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
	// 말단 오른쪽 노드 이면 반환
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
	// 말단 왼쪽 노드 이면 반환
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
	// 마지막 전 노드라면 end를 반환
	if (node == node->end)
	{
		return node->end;
	}

	// 만약 오른쪽 자식이 존재한다면 오른쪽 자식의 맨 왼쪽(작은곳으로가라)
	if (node->right != node->nil)
	{
		return minimum(node->right);
	}

	// 현재위치를 들어온 노드의 부모로하고
	RBNode* cur = node->parent;

	// 노드가 cur의 오른쪽자식이 아닐때까지 cur을 올린다.
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
	// 만약 왼쪽 노드가 존재한다면 왼쪽 자식의 맨 오른쪽(큰 곳으로가라)
	if (node->left != node->nil)
	{
		return maximum(node->left);
	}

	// 현재위치를 들어온 노드의 부모로하고
	RBNode* cur = node->parent;
	// 노드가 cur의 왼쪽 자식이 아닐때 까지 cur 을 올린다.
	while (cur != nullptr && node == cur->left)
	{
		node = cur;
		cur = cur->parent;
	}
	return cur;
}

