�ֱ� ������Ʈ 2018.07.14

Ŭ������    : JArray / JArray_Iterator
Ŭ���� ���� : �迭�� �ݺ��ڸ� Ȱ���� Ŭ���� �迭

�ʿ� �۾� �Լ�
* ���� ������ ���� ó�� ( ���߿� ���� ó�� ���̺귯�� �ۼ��� ���� �ڼ��ϰ� )
* [] �����ڿ� index ����غ��� index�� ������ ��ſ� ���� ���� / []�� �Ҿ����Ѵ�� ���� ����..
* ���� merge�Լ� ���� ( �ٸ� Array ���� �Լ�)

/* JArray_Iterator ���� ������ ������ */
Data* operator->();
Data& operator*();
JArray_Iterator& operator=(const JArray_Iterator& data);
JArray_Iterator& operator++();                  
JArray_Iterator operator++(const int idx);       
JArray_Iterator operator+(const int idx);
JArray_Iterator& operator--();
JArray_Iterator operator--(const int idx);
JArray_Iterator operator-(const int idx);
JArray_Iterator& operator+=(const int idx);
JArray_Iterator& operator-=(const int idx);
bool operator==(const JArray_Iterator& rhs) const;
bool operator!=(const JArray_Iterator& rhs) const;
bool operator>(const JArray_Iterator& rhs) const;
bool operator>=(const JArray_Iterator& rhs) const;
bool operator<(const JArray_Iterator& rhs) const;
bool operator<=(const JArray_Iterator& rhs) const;


/** ������ �� �Ҹ��� */

Function    : JArray()
Explanation : �⺻ ������

Function    : JArray(const size_t size)
Explanation : �޸�ũ�⸦ ���ڷ� �޴� ������
@param const size_t size : �޸� ������

Function    : JArray(const std::initializer_list<Data>& list)
Explanation : ���� �迭�� ���ڷ� �޴� ������
@param const std::initializer_list<Data>& list : �迭 ����Ʈ

Function    : JArray(const JArray& copy)
Explanation : ���� ������
@param const JArray& copy : ������ �迭 ����

Function    : ~JArray()
Explanation : �Ҹ���



/** ���� �� ���� */

Function    : void push_back(const Data& data)
Explanation : �迭�� �ǳ��� ��Ҹ� �߰��Ѵ�.
@param const Data& data : �߰��� ���

Function    : Data& pop_back()
Explanation : �迭�� �� ��Ҹ� �����ϰ� ������ ��Ҹ� ��ȯ�Ѵ�.

Function    : void clear()
Explanation : ��� �迭�� ��ҵ��� �����Ѵ�.

Function    : JArray_Iterator erase(const JArray_Iterator& data)
Explanation : �ش� �ݺ��ڰ� ����Ű�� ��Ҹ� �����Ѵ�.( ��� ��ü�� �������.) ������ ����� ������ġ�� ��ȯ�Ѵ�.
@param const JArray_Iterator& data : ������ ���

Function    : JArray_Iterator erase(const JArray_Iterator& start, const JArray_Iterator& end)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� ������ŭ ��ҵ��� �����Ѵ�.( ��� ��ü�� �������.) ������ ����� ���� ��ġ�� ��ȯ�Ѵ�.
@param const JArray_Iterator& start : ������ �ݺ��� ���� ��ġ
@param const JArray_Iterator& end   : ������ �ݺ��� ������ ��ġ


Function    : JArray_Iterator remove(const JArray_Iterator& data)
Explanation : �ش� �ݺ��ڰ� ����Ű�� ��Ҹ� �����Ѵ�.(��. �����ü�� ��������ʴ´�.) ������ ��ġ�� ���� ��ġ�� ��ȯ�Ѵ�.
@param const JArray_Iterator& data : ������ ��� 

Function    : 	JArray_Iterator remove(const JArray_Iterator& start, const JArray_Iterator& end)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� ������ŭ ��ҵ��� �����Ѵ�.(��. �����ü�� ��������ʴ´�.) ������ ��ġ�� ������ġ�� ��ȯ�Ѵ�.
@param const JArray_Iterator& start : ������ �ݺ��� ���� ��ġ
@param const JArray_Iterator& end   : ������ �ݺ��� ������ ��ġ

Function    : JArray_Iterator remove_if(const std::function<bool(const Data& data)>& func)
Explanation : �ش� �Լ��� true�� ��ȯ�ϴ� ��ҵ��� �����Ѵ�.(��. �����ü�� ��������ʴ´�.) ���������� ��������ġ�� ������ġ�� ��ȯ�Ѵ�.
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�

Function    : JArray_Iterator remove_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : �ݺ��ڸ� ������ ���Ͽ� �ش� �Լ��� true�� ��ȯ�ϴ� ���� �ȿ� ���ϴ� ��ҵ��� �����Ѵ�.(��. �����ü�� ��������ʴ´�.) ���������� ��������ġ�� ������ġ�� ��ȯ�Ѵ�.
@param const JArray_Iterator& start                      : ������ �ݺ��� ���� ��ġ
@param  const JArray_Iterator& end                       : ������ �ݺ��� ������ ��ġ
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�



/* Ž�� */

Function    : JArray_Iterator begin()
Explanation : �迭�� ���� �κ��� �ݺ��ڷ� ��ȯ�Ѵ�.

Function    : JArray_Iterator end()
Explanation : �迭�� �� �κ��� �ݺ��ڷ� ��ȯ�Ѵ�.

Function    : JArray_Iterator find(const Data& data)
Explanation : �ش� �Ű�����. ��ҿ� �ش��ϴ� ��ġ�� �ݺ��ڷ� ��ȯ�Ѵ�.
@param const Data& data : ã�����ϴ� ���

Function    : JArray_Iterator find(const JArray_Iterator& start, const JArray_Iterator& end,const Data& data)
Explanation : �ݺ��ڷ� ������ ���� Ž���Ͽ� Ž�� ��� ��ҿ� ���� ��Ҹ� �ݺ��ڷ� ��ȯ�Ѵ�.
@param const JArray_Iterator& start : �ݺ��� Ž�� ���� ó�� ��ġ
@param const JArray_Iterator& end   : �ݺ��� Ž�� ���� ������ ��ġ
@param const Data&            data  : Ž�� ��� ���

Function    : JArray_Iterator find_if(const std::function<bool(const Data& data)>& func)
Explanation : �ش� �Լ��� true�� ��ȯ�ϴ� ��Ҹ� �ݺ��ڷ� ��ȯ�Ѵ�. �� �Լ��� ������ bool func(Data&) �� �����̾���Ѵ�.
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�.

Function    : JArray_Iterator find_if(const JArray_Iterator& start, const JArray_Iterator& end,const std::function<bool(const Data& data)>& func)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� �Լ��� true�� ��ȯ�ϴ� �������� ��Ҹ� �ݺ��ڷ� ��ȯ�Ѵ�. �� �Լ��� ������ bool func(Data&) �� �����̾���Ѵ�.
@param const JArray_Iterator& start                      : �ݺ��� Ž�� ���� ó�� ��ġ
@param const JArray_Iterator& end                        : �ݺ��� Ž�� ���� ������ ��ġ
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�.

Function    : const Data& index(const size_t idx) const
Explanation : idx�� ��ġ�� �����ϴ� ��Ҹ� ��ȯ�Ѵ�.
@param const size_t idx : ����� ��ġ

Function    : const size_t count(const Data& data) const
Explanation : data ������ ���� ��Ҹ� ã�� �� ������ ��ȯ�Ѵ�.
@param const Data& data : Ž���� ���

Function    : const size_t count_if(const std::function<bool(const Data& data)>& func)
Explanation : �ش� �Լ��� true�� ��ȯ�ϴ� ��ҵ��� ã�� �� ������ ��ȯ�Ѵ�.
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�

Function    : const size_t count_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �ش� �Լ��� true�� ��ȯ�ϴ� �������� ��ҵ��� ã�� �� ������ ��ȯ�Ѵ�.
@param const JArray_Iterator& start                      : �ݺ��� Ž�� ���� ó�� ��ġ
@param const JArray_Iterator& end                        : �ݺ��� Ž�� ���� ������ ��ġ
@param const std::function<bool(const Data& data)>& func : Ž���� �Լ�.

/** ������ �� ũ�� */

Function    : void resize(const size_t size)
Explanation : �迭�� ũ�⸦ �����Ѵ�.
@param const size_t size : �迭�� �� ����� �ִ� ����

Function    : void reserve(const size_t size)
Explanation : �迭�� �޸� ũ�⸦ �ٽ� ���Ͽ� �Ҵ��Ѵ�.
@param const size_t size : �Ҵ��� �޸� ũ��

Function    : const size_t size() const
Explanation : ����� ������ ��ȯ�Ѵ�.

Function    : const size_t memorysize() const
Explanation : �޸��� ũ�⸦ ��ȯ�Ѵ�.

Function    : bool empty() const
Explanation : ������ִ��� Ȯ���Ѵ�. ����������� true ���� �ݴ��false�� ��ȯ�Ѵ�.

/** ���� �� ���� �Լ� */

Function    : void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : �Ű������� ���� �Լ��� ����� �����ķ� ��ҵ��� ���Ľ�Ų��. ( �⺻ Less(��������) ���ķ��Ѵ�.)
@param const std::function<bool(const Data& data1, const Data& data2)>& func : ���Ľ�ų ������ �Լ�

Function    : void sort(const JArray_Iterator& start, const JArray_Iterator& last, const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : �ݺ��ڷ� ������ ���Ͽ� �������� ��ҵ��� �ŰԺ����� ���� �Լ��� ����� �����ķ� ��ҵ��� ���Ľ�Ų��.(�⺻ Less(��������) ���ķ��Ѵ�.)
@param const JArray_Iterator& start                                          : �ݺ��� ���� ���� ó�� ��ġ
@param const JArray_Iterator& last                                           : �ݺ��� ���� ���� ������ ��ġ
@param const std::function<bool(const Data& data1, const Data& data2)>& func : ���Ľ�ų ������ �Լ�

Function    : void swap(JArray_Iterator data1, JArray_Iterator data2)
Explanation : ���� �ݺ����� ���� �ٲ۴�.
@param JArray_Iterator data1 : �ٲ� ���
@param JArray_Iterator data2 : �ٲ� ���2



/**  ������ �����ε� */

Function    : Data& operator[](const size_t idx)
Explanation : �迭�� []������ �����ε�.
@param const size_t idx : ��� ��ġ

Function    : const JArray& operator=(const JArray& data)
Explanation : �迭�� = ������ �����ε�.
@param const JArray& data : ���� ��ų JArray Ŭ����

/*  ���  */
Function    : void Write_cpp() const
Explanation : cpp �ڵ忡�� �ܼ�â�� ���� �迭�� ��Ȳ�� ����Ѵ�.