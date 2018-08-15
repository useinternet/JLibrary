최근 업데이트 2018.07.20

클래스명    : JList
클래스 목적 : 포인터를 활용하여 링크 리스트를 구현

필요 작업 함수
* 좀더 정밀한 예외 처리 ( 나중에 예외 처리 라이브러리 작성시 좀더 자세하게 )
* [] 연산자와 index 고려해보기 index는 안전한 대신에 느린 연산 / []은 불안전한대신 빠른 연산..
* 추후 merge함수 구현 ( 다른 Array 병합 함수)


/*  생성자 및 소멸자 */ ( 수정 중 )

Function    : JList()
Explanation : 기본 생성자

Function    : JList(const std::initializer_list<Data>& list)
Explanation : Data형식의 주솟값을 받는 생성자
@param Data* data : 이 클래스가 저장할 Data형식의 주솟값

Function    : JList(const JList& copy)
Explanation : 기본 소멸자

Function    : ~JList()
Explanation : 기본 소멸자


/** 삽입 및 삭제 */

Function    : void push_back(const Data& data)
Explanation : 리스트의 뒤에 요소를 추가
@param const Data& data : 추가할 요소

Function    : void push_front(const Data& data)
Explanation : 리스트의 앞에 요소를 추가
@param const Data& data : 추가할 요소

Function    : Data pop_back()
Explanation : 리스트의 마지막 요소를 삭제하고 그 요소의 값을 반환한다.

Function    : Data pop_front()
Explanation : 리스트의 가장 앞의 요소를 삭제하고 그 요소의 값을 반환한다.

Function    : JList_Iterator insert(JList_Iterator Pos, const Data& data)
Explanation : 해당 위치에 해당하는 곳에 요소를 추가하고 추가한 요소의 위치를 반복자로 반환한다.
@param JList_Iterator Pos : 추가할 위치 인덱스
@param const Data& data   : 추가할 요소

Function    : JList_Iterator insert(const JList_Iterator& Pos, size_t count, const Data& data)
Explanation : 해당 위치에 해당하는 곳에 지정한 갯수만큼 요소를 추가하고 추가한 요소의 위치를 반복자로 반환한다.
@param JList_Iterator Pos : 추가할 위치 인덱스
@param size_t count       : 추가할 요소 갯수 
@param const Data& data   : 추가할 요소

Function    : JList_Iterator insert(const JList_Iterator& Pos, const JList_Iterator& start, const JList_Iterator& end)
Explanation : 해당 위치에 해당하는 곳에 다른 리스트의 반복자로 정한 구간에 있는 요소들을 추가한다. 추가한 요소의 마지막위치의 다음을 반환한다.
@param JList_Iterator Pos          : 추가할 시작 위치
@param const JList_Iterator& start : 삽입할 다른 리스트의 반복자의 시작 위치
@param const JList_Iterator& end   : 삽입할 다른 리스트의 반복자의 마지막 위치

Function    : JList_Iterator remove(const JList_Iterator& iter)
Explanation : 해당 위치에 존재하는 요소를 삭제한다. 삭제한 위치를 반환한다.( 즉 반복자는 원래 위치의 다음 위치에 있었던 요소를 가르키게된다.)
@param const JList_Iterator& iter : 삭제할 위치

Function    : JList_Iterator remove(const JList_Iterator& start, const JList_Iterator& end)
Explanation : 해당 구간에 존재하는 요소들을 삭제한다. 삭제한 마지막 위치를 반환한다.( 즉 반복자는 원래 마지막 위치에 있었던 다음 위치에 있었던 요소를 가르키게된다.)
@param const JList_Iterator& start : 삭제할 처음 위치
@param const JList_Iterator& end   : 삭제할 마지막 위치

Function    : JList_Iterator remove_if(const std::function<bool(const Data& data)>& func)
Explanation : func 함수가 true를 반환하는 요소들을 삭제한다. 마지막으로 삭제한 요소의 위치를 반환한다.( 즉 반복자는 원래 삭제한 위치의 다음 위치에있었던 요소를 가르키게된다.)
@param const std::function<bool(const Data& data)>& func : 삭제의 기준이되는 함수

Function    : JList_Iterator remove_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : func 함수가 true를 반환하는 반복자로 정한 구간 안의 요소들을 삭제한다. 마지막으로 삭제한 요소의 위치를 반환한다.( 즉 반복자는 원래 삭제한 위치의 다음 위치에있었던 요소를 가르키게된다.)
@param const JList_Iterator& start                       : 삭제할 처음 위치
@param const JList_Iterator& end                         : 삭제할 마지막 위치
@param const std::function<bool(const Data& data)>& func : 삭제의 기준이되는 함수

Function    : void clear()
Explanation : 모든 요소를 삭제한다.

/** 탐색 */

Function    : JList_Iterator begin()
Explanation : 리스트의 처음 위치를 반복자로 반환한다.

Function    : JList_Iterator end()
Explanation : 리스트의 마지막 위치를 반복자로 반환한다.

Function    : JList_Iterator find(const Data& data)
Explanation : 해당 요소의 값에 해당되는 처음 위치를 반환한다.
@param const Data& data : 탐색할 Data 값

Function    : JList_Iterator find(const JList_Iterator& start, const JList_Iterator& end, const Data& data);
Explanation : 반복자로 구간을 정하여 해당 구간에 요소의 값에 해당되는 처음 위치를 반환한다.
@param const JList_Iterator& start : 탐색할 처음 위치
@param const JList_Iterator& end   : 탐색할 마지막 위치
@param const Data& data            : 탐색할 Data 값

Function    : JList_Iterator find_if(const std::function<bool(const Data& data)>& func)
Explanation : 해당 함수가 true를 반환하는 요소의 처음 위치를 반환한다.
@param const std::function<bool(const Data& data)>& func : 탐색의 기준이 되는 함수

Function    : JList_Iterator find_if(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : 반복자로 구간을 정하여 해당 구간에 함수가 true를 반환하는 요소의 처음 위치를 반환한다.
@param const JList_Iterator& start                       : 탐색할 처음 위치
@param const JList_Iterator& end                         : 탐색할 마지막 위치 
@param const std::function<bool(const Data& data)>& func : 탐색의 기준이 되는 함수

Function    : Data&  index(const size_t idx)
Explanation : 해당 인덱스에 위치한 값을 반환한다.
@param const size_t idx : 리스트 인덱스

Function    : size_t count(const Data& data)
Explanation : 해당 값에 해당되는 요소의 갯수를 반환한다.
@param const Data& data : 탐색할 Data 값

Function    : size_t count_if(const std::function<bool(const Data& data)>& func)
Explanation : 해당 함수가 true를 반환하는 요소의 갯수를 반환한다.
@param const std::function<bool(const Data& data)>& func : 탐색의 기준이 되는 함수

Function    : size_t count_if(const JList_Iterator& start, const JList_Iterator& end,const std::function<bool(const Data& data)>& func)
Explanation : 반복자로 정한 해당 구간안에서 함수가 true를 반환하는 요소의 갯수를 반환한다.
@param const JList_Iterator& start                       : 탐색할 처음 위치
@param const JList_Iterator& end                         : 탐색할 마지막 위치 
@param const std::function<bool(const Data& data)>& func : 탐색의 기준이 되는 함수

/** 사이즈 및 크기 */

Function    : const size_t size()
Explanation : 현재 리스트의 요소의 갯수를 반환한다.

Function    : bool empty()
Explanation : 리스트가 비어져있는지 검사한다. 비어져있으면 true 아니면 false 를 반환한다.

/** 정렬 및 편의 함수 */

Function    : void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : 해당 함수를 기준으로 하여 정렬한다. 정렬은 퀵정렬로 한다.
@param const std::function<bool(const Data& data)>& func : 정렬의 기준이 되는 함수

Function    : void sort(const JList_Iterator& start, const JList_Iterator& end, const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : 반복자로 정한 해당 구간안에서 함수를 기준으로 하여 정렬한다. 정렬은 퀵정렬로 한다.
@param const JList_Iterator& start                       : 정렬할 처음 위치
@param const JList_Iterator& end                         : 정렬할 마지막 위치 
@param const std::function<bool(const Data& data)>& func : 정렬의 기준이 되는 함수

Function    : void swap(JList_Iterator iter1, JList_Iterator iter2)
Explanation : 반복자 iter1 와 iter2 의 값을 서로 바꾼다.
@param const JList_Iterator iter1 : 바꿀 반복자 1
@param const JList_Iterator iter2 : 바꿀 반복자 2

/** 연산자 오버로딩 */

Function    : Data& operator[](const size_t idx)
Explanation : [] 연산자

Function    : const JList& operator=(const JList& data);
Explanation : 대입 연산자


/** 출력 */
Function    : void Write_cpp() const
Explanation : c++ 에서 현재 리스트의 정보를 출력 해준다.












