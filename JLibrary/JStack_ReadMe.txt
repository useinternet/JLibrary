최근 업데이트 2018.07.23

클래스명    : JStack
클래스 목적 : 정적 배열을 이용하여 스택을 구현

필요 작업 함수
* 좀더 정밀한 예외 처리 ( 나중에 예외 처리 라이브러리 작성시 좀더 자세하게 )
* 추후 merge함수 구현 (  병합 함수)


/* 생성자 및 소멸자 */

Function    : JStack()
Explanation : 기본 생성자

Function    : JStack(const size_t size)
Explanation : 메모리 사이즈를 인자로 받는 생성자
@param size_t size : 메모리 사이즈

Function    : JStack(const JStack& stack)
Explanation : 복사 생성자

Function    : ~JStack()
Explanation : 기본 소멸자

/* 삽입 및 삭제 */

Function    : void push(const Data& data)
Explanation : 맨 끝에 요소를 삽입한다.
@param const Data& data : 삽입할 요소

Function    : Data& pop()
Explanation : 맨 끝 요소를 삭제하고 그 요소를 반환한다.

Function    : void clear(size_t size = JStack_Max)
Explanation : 모든 요소를 삭제 후 size 만큼 메모리를 다시 재할당한다.
@param size_t size : 삭제후 메모리를 할당할 사이즈

/* 탐색 및 사이즈 */

Function    : Data& top()
Explanation : 맨 끝에 요소를 반환한다.

Function    : bool empty()
Explanation : 스택이 비워져있는지 검사한다. 비어져있으면 true 아니면 false를 반환한다.

Function    : bool full()
Explanation : 스택이 꽉채워져있는지 검사한다. 꽉채워져있으면 true 아니면 false를 반환한다.

Function    : size_t size()
Explanation : 요소의 갯수를 반환한다.

Function    : void resize(const size_t size)
Explanation : size만큼 메모리를 재할당한다. 요소는 삭제되지않는다. 단. 현재 요소의 갯수보다 메모리 사이즈가 작을경우 그차이만큼 삭제된다.
@param const size_t size : 메모리 사이즈

/* 출력 */

Function    : void Write_cpp()
Explanation : 요소들을 출력 -> c,c++에서만 사용가능

Function    : void Write_cpp_All()
Explanation : 메모리영역까지 출력 -> c,c++에서만 사용가능
