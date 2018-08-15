�ֱ� ������Ʈ 2018.07.20

Ŭ������    : JList
Ŭ���� ���� : �����͸� Ȱ���Ͽ� ��ũ ����Ʈ�� ����

�ʿ� �۾� �Լ�
* ���� ������ ���� ó�� ( ���߿� ���� ó�� ���̺귯�� �ۼ��� ���� �ڼ��ϰ� )
* [] �����ڿ� index ����غ��� index�� ������ ��ſ� ���� ���� / []�� �Ҿ����Ѵ�� ���� ����..
* ���� merge�Լ� ���� ( �ٸ� Array ���� �Լ�)


/*  ������ �� �Ҹ��� */ ( ���� �� )

Function    : JList()
Explanation : �⺻ ������

Function    : JList(const std::initializer_list<Data>& list)
Explanation : Data������ �ּڰ��� �޴� ������
@param Data* data : �� Ŭ������ ������ Data������ �ּڰ�

Function    : JList(const JList& copy)
Explanation : �⺻ �Ҹ���

Function    : ~JList()
Explanation : �⺻ �Ҹ���


/** ���� �� ���� */

Function    : void push_back(const Data& data)
Explanation : ����Ʈ�� �ڿ� ��Ҹ� �߰�
@param const Data& data : �߰��� ���

Function    : void push_front(const Data& data)
Explanation : ����Ʈ�� �տ� ��Ҹ� �߰�
@param const Data& data : �߰��� ���

Function    : Data pop_back()
Explanation : ����Ʈ�� ������ ��Ҹ� �����ϰ� �� ����� ���� ��ȯ�Ѵ�.

Function    : Data pop_front()
Explanation : ����Ʈ�� ���� ���� ��Ҹ� �����ϰ� �� ����� ���� ��ȯ�Ѵ�.

Function    : JList_Iterator insert(JList_Iterator Pos, const Data& data)
Explanation : �ش� ��ġ�� �ش��ϴ� ���� ��Ҹ� �߰��ϰ� �߰��� ����� ��ġ�� �ݺ��ڷ� ��ȯ�Ѵ�.
@param JList_Iterator Pos : �߰��� ��ġ �ε���
@param const Data& data   : �߰��� ���

Function    : JList_Iterator insert(const JList_Iterator& Pos, size_t count, const Data& data)
Explanation : �ش� ��ġ�� �ش��ϴ� ���� ������ ������ŭ ��Ҹ� �߰��ϰ� �߰��� ����� ��ġ�� �ݺ��ڷ� ��ȯ�Ѵ�.
@param JList_Iterator Pos : �߰��� ��ġ �ε���
@param size_t count       : �߰��� ��� ���� 
@param const Data& data   : �߰��� ���

Function    : JList_Iterator insert(const JList_Iterator& Pos, const JList_Iterator& start, const JList_Iterator& end)
Explanation : �ش� ��ġ�� �ش��ϴ� ���� �ٸ� ����Ʈ�� �ݺ��ڷ� ���� ������ �ִ� ��ҵ��� �߰��Ѵ�. �߰��� ����� ��������ġ�� ������ ��ȯ�Ѵ�.
@param JList_Iterator Pos          : �߰��� ���� ��ġ
@param const JList_Iterator& start : ������ �ٸ� ����Ʈ�� �ݺ����� ���� ��ġ
@param const JList_Iterator& end   : ������ �ٸ� ����Ʈ�� �ݺ����� ������ ��ġ

Function    : JList_Iterator remove(const JList_Iterator& iter)
Explanation : �ش� ��ġ�� �����ϴ� ��Ҹ� �����Ѵ�. ������ ��ġ�� ��ȯ�Ѵ�.( �� �ݺ��ڴ� ���� ��ġ�� ���� ��ġ�� �־��� ��Ҹ� ����Ű�Եȴ�.)
@param const JList_Iterator& iter : ������ ��ġ

Function    : JList_Iterator remove(const JList_Iterator& start, const JList_Iterator& end)
Explanation : �ش� ������ �����ϴ� ��ҵ��� �����Ѵ�. ������ ������ ��ġ�� ��ȯ�Ѵ�.( �� �ݺ��ڴ� ���� ������ ��ġ�� �־��� ���� ��ġ�� �־��� ��Ҹ� ����Ű�Եȴ�.)
@param const JList_Iterator& start : ������ ó�� ��ġ
@param const JList_Iterator& end   : ������ ������ ��ġ

Function    : JList_Iterator remove_if(const std::function<bool(const Data& data)>& func)
Explanation : func �Լ��� true�� ��ȯ�ϴ� ��ҵ��� �����Ѵ�. ���������� ������ ����� ��ġ�� ��ȯ�Ѵ�.( �� �ݺ��ڴ� ���� ������ ��ġ�� ���� ��ġ���־��� ��Ҹ� ����Ű�Եȴ�.)
@param const std::function<bool(const Data& data)>& func : ������ �����̵Ǵ� �Լ�

Function    : JList_Iterator remove_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : func �Լ��� true�� ��ȯ�ϴ� �ݺ��ڷ� ���� ���� ���� ��ҵ��� �����Ѵ�. ���������� ������ ����� ��ġ�� ��ȯ�Ѵ�.( �� �ݺ��ڴ� ���� ������ ��ġ�� ���� ��ġ���־��� ��Ҹ� ����Ű�Եȴ�.)
@param const JList_Iterator& start                       : ������ ó�� ��ġ
@param const JList_Iterator& end                         : ������ ������ ��ġ
@param const std::function<bool(const Data& data)>& func : ������ �����̵Ǵ� �Լ�

Function    : void clear()
Explanation : ��� ��Ҹ� �����Ѵ�.

/** Ž�� */

Function    : JList_Iterator begin()
Explanation : ����Ʈ�� ó�� ��ġ�� �ݺ��ڷ� ��ȯ�Ѵ�.

Function    : JList_Iterator end()
Explanation : ����Ʈ�� ������ ��ġ�� �ݺ��ڷ� ��ȯ�Ѵ�.

Function    : JList_Iterator find(const Data& data)
Explanation : �ش� ����� ���� �ش�Ǵ� ó�� ��ġ�� ��ȯ�Ѵ�.
@param const Data& data : Ž���� Data ��

Function    : JList_Iterator find(const JList_Iterator& start, const JList_Iterator& end, const Data& data);
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� ������ ����� ���� �ش�Ǵ� ó�� ��ġ�� ��ȯ�Ѵ�.
@param const JList_Iterator& start : Ž���� ó�� ��ġ
@param const JList_Iterator& end   : Ž���� ������ ��ġ
@param const Data& data            : Ž���� Data ��

Function    : JList_Iterator find_if(const std::function<bool(const Data& data)>& func)
Explanation : �ش� �Լ��� true�� ��ȯ�ϴ� ����� ó�� ��ġ�� ��ȯ�Ѵ�.
@param const std::function<bool(const Data& data)>& func : Ž���� ������ �Ǵ� �Լ�

Function    : JList_Iterator find_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� ������ �Լ��� true�� ��ȯ�ϴ� ����� ó�� ��ġ�� ��ȯ�Ѵ�.
@param const JList_Iterator& start                       : Ž���� ó�� ��ġ
@param const JList_Iterator& end                         : Ž���� ������ ��ġ 
@param const std::function<bool(const Data& data)>& func : Ž���� ������ �Ǵ� �Լ�

Function    : Data&  index(const size_t idx)
Explanation : �ش� �ε����� ��ġ�� ���� ��ȯ�Ѵ�.
@param const size_t idx : ����Ʈ �ε���

Function    : size_t count(const Data& data)
Explanation : �ش� ���� �ش�Ǵ� ����� ������ ��ȯ�Ѵ�.
@param const Data& data : Ž���� Data ��

Function    : size_t count_if(const std::function<bool(const Data& data)>& func)
Explanation : �ش� �Լ��� true�� ��ȯ�ϴ� ����� ������ ��ȯ�Ѵ�.
@param const std::function<bool(const Data& data)>& func : Ž���� ������ �Ǵ� �Լ�

Function    : size_t count_if(const JList_Iterator& start, const JList_Iterator& end,const std::function<bool(const Data& data)>& func)
Explanation : �ݺ��ڷ� ���� �ش� �����ȿ��� �Լ��� true�� ��ȯ�ϴ� ����� ������ ��ȯ�Ѵ�.
@param const JList_Iterator& start                       : Ž���� ó�� ��ġ
@param const JList_Iterator& end                         : Ž���� ������ ��ġ 
@param const std::function<bool(const Data& data)>& func : Ž���� ������ �Ǵ� �Լ�

/** ������ �� ũ�� */

Function    : const size_t size()
Explanation : ���� ����Ʈ�� ����� ������ ��ȯ�Ѵ�.

Function    : bool empty()
Explanation : ����Ʈ�� ������ִ��� �˻��Ѵ�. ����������� true �ƴϸ� false �� ��ȯ�Ѵ�.

/** ���� �� ���� �Լ� */

Function    : void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : �ش� �Լ��� �������� �Ͽ� �����Ѵ�. ������ �����ķ� �Ѵ�.
@param const std::function<bool(const Data& data)>& func : ������ ������ �Ǵ� �Լ�

Function    : void sort(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : �ݺ��ڷ� ���� �ش� �����ȿ��� �Լ��� �������� �Ͽ� �����Ѵ�. ������ �����ķ� �Ѵ�.
@param const JList_Iterator& start                       : ������ ó�� ��ġ
@param const JList_Iterator& end                         : ������ ������ ��ġ 
@param const std::function<bool(const Data& data)>& func : ������ ������ �Ǵ� �Լ�

Function    : void swap(JList_Iterator iter1, JList_Iterator iter2)
Explanation : �ݺ��� iter1 �� iter2 �� ���� ���� �ٲ۴�.
@param const JList_Iterator iter1 : �ٲ� �ݺ��� 1
@param const JList_Iterator iter2 : �ٲ� �ݺ��� 2

/** ������ �����ε� */

Function    : Data& operator[](const size_t idx)
Explanation : [] ������

Function    : const JList& operator=(const JList& data);
Explanation : ���� ������


/** ��� */
Function    : void Write_cpp() const
Explanation : c++ ���� ���� ����Ʈ�� ������ ��� ���ش�.












