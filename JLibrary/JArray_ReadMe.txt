최근 업데이트 2018.07.14

클래스명    : JArray / JArray_Iterator
클래스 목적 : 배열과 반복자를 활용한 클래스 배열

필요 작업 함수
* 좀더 정밀한 예외 처리 ( 나중에 예외 처리 라이브러리 작성시 좀더 자세하게 )
* [] 연산자와 index 고려해보기 index는 안전한 대신에 느린 연산 / []은 불안전한대신 빠른 연산..
* 추후 merge함수 구현 ( 다른 Array 병합 함수)

/* JArray_Iterator 연산 가능한 연산자 */
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


/** 생성자 및 소멸자 */

Function    : JArray()
Explanation : 기본 생성자

Function    : JArray(const size_t size)
Explanation : 메모리크기를 인자로 받는 생성자
@param const size_t size : 메모리 사이즈

Function    : JArray(const std::initializer_list<Data>& list)
Explanation : 가변 배열을 인자로 받는 생성자
@param const std::initializer_list<Data>& list : 배열 리스트

Function    : JArray(const JArray& copy)
Explanation : 복사 생성자
@param const JArray& copy : 복사할 배열 변수

Function    : ~JArray()
Explanation : 소멸자



/** 삽입 및 삭제 */

Function    : void push_back(const Data& data)
Explanation : 배열의 맨끝에 요소를 추가한다.
@param const Data& data : 추가할 요소

Function    : Data& pop_back()
Explanation : 배열의 끝 요소를 삭제하고 마지막 요소를 반환한다.

Function    : void clear()
Explanation : 모든 배열의 요소들을 삭제한다.

Function    : JArray_Iterator erase(const JArray_Iterator& data)
Explanation : 해당 반복자가 가르키는 요소를 삭제한다.( 요소 자체가 사라진다.) 삭제한 요소의 다음위치를 반환한다.
@param const JArray_Iterator& data : 삭제할 요소

Function    : JArray_Iterator erase(const JArray_Iterator& start, const JArray_Iterator& end)
Explanation : 반복자로 구간을 정하여 해당 구간만큼 요소들을 삭제한다.( 요소 자체가 사라진다.) 삭제한 요소의 다음 위치를 반환한다.
@param const JArray_Iterator& start : 삭제할 반복자 시작 위치
@param const JArray_Iterator& end   : 삭제할 반복자 마지막 위치


Function    : JArray_Iterator remove(const JArray_Iterator& data)
Explanation : 해당 반복자가 가르키는 요소를 삭제한다.(단. 요소자체는 사라지지않는다.) 삭제한 위치의 다음 위치를 반환한다.
@param const JArray_Iterator& data : 삭제할 요소 

Function    : 	JArray_Iterator remove(const JArray_Iterator& start, const JArray_Iterator& end)
Explanation : 반복자로 구간을 정하여 해당 구간만큼 요소들을 삭제한다.(단. 요소자체는 사라지지않는다.) 삭제한 위치의 다음위치를 반환한다.
@param const JArray_Iterator& start : 삭제할 반복자 시작 위치
@param const JArray_Iterator& end   : 삭제할 반복자 마지막 위치

Function    : JArray_Iterator remove_if(const std::function<bool(const Data& data)>& func)
Explanation : 해당 함수가 true를 반환하는 요소들을 삭제한다.(단. 요소자체는 사라지지않는다.) 마지막으로 삭제한위치의 다음위치를 반환한다.
@param const std::function<bool(const Data& data)>& func : 탐색할 함수

Function    : JArray_Iterator remove_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : 반복자를 구간을 정하여 해당 함수가 true를 반환하는 구간 안에 속하는 요소들을 삭제한다.(단. 요소자체는 사라지지않는다.) 마지막으로 삭제한위치의 다음위치를 반환한다.
@param const JArray_Iterator& start                      : 삭제할 반복자 시작 위치
@param  const JArray_Iterator& end                       : 삭제할 반복자 마지막 위치
@param const std::function<bool(const Data& data)>& func : 탐색할 함수



/* 탐색 */

Function    : JArray_Iterator begin()
Explanation : 배열의 시작 부분을 반복자로 반환한다.

Function    : JArray_Iterator end()
Explanation : 배열의 끝 부분을 반복자로 반환한다.

Function    : JArray_Iterator find(const Data& data)
Explanation : 해당 매개변수. 요소에 해당하는 위치를 반복자로 반환한다.
@param const Data& data : 찾고자하는 요소

Function    : JArray_Iterator find(const JArray_Iterator& start, const JArray_Iterator& end,const Data& data)
Explanation : 반복자로 구간을 정해 탐색하여 탐색 대상 요소와 같은 요소를 반복자로 반환한다.
@param const JArray_Iterator& start : 반복자 탐색 범위 처음 위치
@param const JArray_Iterator& end   : 반복자 탐색 범위 마지막 위치
@param const Data&            data  : 탐색 대상 요소

Function    : JArray_Iterator find_if(const std::function<bool(const Data& data)>& func)
Explanation : 해당 함수가 true를 반환하는 요소를 반복자로 반환한다. 단 함수의 형식은 bool func(Data&) 의 형식이어야한다.
@param const std::function<bool(const Data& data)>& func : 탐색할 함수.

Function    : JArray_Iterator find_if(const JArray_Iterator& start, const JArray_Iterator& end,const std::function<bool(const Data& data)>& func)
Explanation : 반복자로 구간을 정하여 해당 함수가 true를 반환하는 구간안의 요소를 반복자로 반환한다. 단 함수의 형식은 bool func(Data&) 의 형식이어야한다.
@param const JArray_Iterator& start                      : 반복자 탐색 범위 처음 위치
@param const JArray_Iterator& end                        : 반복자 탐색 범위 마지막 위치
@param const std::function<bool(const Data& data)>& func : 탐색할 함수.

Function    : const Data& index(const size_t idx) const
Explanation : idx의 위치에 존재하는 요소를 반환한다.
@param const size_t idx : 요소의 위치

Function    : const size_t count(const Data& data) const
Explanation : data 변수와 같은 요소를 찾아 그 갯수를 반환한다.
@param const Data& data : 탐색할 대상

Function    : const size_t count_if(const std::function<bool(const Data& data)>& func)
Explanation : 해당 함수가 true를 반환하는 요소들을 찾아 그 갯수를 반환한다.
@param const std::function<bool(const Data& data)>& func : 탐색할 함수

Function    : const size_t count_if(const JArray_Iterator& start, const JArray_Iterator& end, const std::function<bool(const Data& data)>& func)
Explanation : 반복자로 구간을 정하여 해당 함수가 true를 반환하는 구간안의 요소들을 찾아 그 갯수를 반환한다.
@param const JArray_Iterator& start                      : 반복자 탐색 범위 처음 위치
@param const JArray_Iterator& end                        : 반복자 탐색 범위 마지막 위치
@param const std::function<bool(const Data& data)>& func : 탐색할 함수.

/** 사이즈 및 크기 */

Function    : void resize(const size_t size)
Explanation : 배열의 크기를 셋팅한다.
@param const size_t size : 배열에 들어갈 요소의 최대 갯수

Function    : void reserve(const size_t size)
Explanation : 배열의 메모리 크기를 다시 정하여 할당한다.
@param const size_t size : 할당할 메모리 크기

Function    : const size_t size() const
Explanation : 요소의 갯수를 반환한다.

Function    : const size_t memorysize() const
Explanation : 메모리의 크기를 반환한다.

Function    : bool empty() const
Explanation : 비어져있는지 확인한다. 비어져있으면 true 그의 반대는false를 반환한다.

/** 정렬 및 편의 함수 */

Function    : void sort(const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : 매개변수로 받은 함수로 기반해 퀵정렬로 요소들을 정렬시킨다. ( 기본 Less(오름차순) 정렬로한다.)
@param const std::function<bool(const Data& data1, const Data& data2)>& func : 정렬시킬 기준의 함수

Function    : void sort(const JArray_Iterator& start, const JArray_Iterator& last, const std::function<bool(const Data& data1, const Data& data2)>& func = Less<Data>)
Explanation : 반복자로 구간을 정하여 구간안의 요소들을 매게변수로 받은 함수로 기반해 퀵정렬로 요소들을 정렬시킨다.(기본 Less(오름차순) 정렬로한다.)
@param const JArray_Iterator& start                                          : 반복자 정렬 범위 처음 위치
@param const JArray_Iterator& last                                           : 반복자 정렬 범위 마지마 위치
@param const std::function<bool(const Data& data1, const Data& data2)>& func : 정렬시킬 기준의 함수

Function    : void swap(JArray_Iterator data1, JArray_Iterator data2)
Explanation : 서로 반복자의 값을 바꾼다.
@param JArray_Iterator data1 : 바꿀 요소
@param JArray_Iterator data2 : 바꿀 요소2



/**  연산자 오버로딩 */

Function    : Data& operator[](const size_t idx)
Explanation : 배열의 []연산자 오버로딩.
@param const size_t idx : 요소 위치

Function    : const JArray& operator=(const JArray& data)
Explanation : 배열의 = 연산자 오버로딩.
@param const JArray& data : 대입 시킬 JArray 클래스

/*  출력  */
Function    : void Write_cpp() const
Explanation : cpp 코드에서 콘솔창에 현재 배열의 상황을 출력한다.