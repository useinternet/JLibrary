�ֱ� ������Ʈ 2018.07.23

Ŭ������    : JStack
Ŭ���� ���� : ���� �迭�� �̿��Ͽ� ������ ����

�ʿ� �۾� �Լ�
* ���� ������ ���� ó�� ( ���߿� ���� ó�� ���̺귯�� �ۼ��� ���� �ڼ��ϰ� )
* ���� merge�Լ� ���� (  ���� �Լ�)


/* ������ �� �Ҹ��� */

Function    : JStack()
Explanation : �⺻ ������

Function    : JStack(const size_t size)
Explanation : �޸� ����� ���ڷ� �޴� ������
@param size_t size : �޸� ������

Function    : JStack(const JStack& stack)
Explanation : ���� ������

Function    : ~JStack()
Explanation : �⺻ �Ҹ���

/* ���� �� ���� */

Function    : void push(const Data& data)
Explanation : �� ���� ��Ҹ� �����Ѵ�.
@param const Data& data : ������ ���

Function    : Data& pop()
Explanation : �� �� ��Ҹ� �����ϰ� �� ��Ҹ� ��ȯ�Ѵ�.

Function    : void clear(size_t size = JStack_Max)
Explanation : ��� ��Ҹ� ���� �� size ��ŭ �޸𸮸� �ٽ� ���Ҵ��Ѵ�.
@param size_t size : ������ �޸𸮸� �Ҵ��� ������

/* Ž�� �� ������ */

Function    : Data& top()
Explanation : �� ���� ��Ҹ� ��ȯ�Ѵ�.

Function    : bool empty()
Explanation : ������ ������ִ��� �˻��Ѵ�. ����������� true �ƴϸ� false�� ��ȯ�Ѵ�.

Function    : bool full()
Explanation : ������ ��ä�����ִ��� �˻��Ѵ�. ��ä���������� true �ƴϸ� false�� ��ȯ�Ѵ�.

Function    : size_t size()
Explanation : ����� ������ ��ȯ�Ѵ�.

Function    : void resize(const size_t size)
Explanation : size��ŭ �޸𸮸� ���Ҵ��Ѵ�. ��Ҵ� ���������ʴ´�. ��. ���� ����� �������� �޸� ����� ������� �����̸�ŭ �����ȴ�.
@param const size_t size : �޸� ������

/* ��� */

Function    : void Write_cpp()
Explanation : ��ҵ��� ��� -> c,c++������ ��밡��

Function    : void Write_cpp_All()
Explanation : �޸𸮿������� ��� -> c,c++������ ��밡��
