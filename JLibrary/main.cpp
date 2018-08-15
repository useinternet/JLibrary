
#include <Windows.h>
#include<crtdbg.h>
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)
#endif

#include<iostream>
#include<string>
#include<conio.h>
#pragma warning(disable : 4996)
#include"JArray.h"
#include"JList.h"
#include"JQueue.h"
#include"JStack.h"
#include"JPriority_Queue.h"
#include"AlgorithmFunctor.h"
#include"JPair.h"
#include"JMap.h"
#include"JHash_Map.h"
#include<map>
#include<list>
#include<chrono>
using namespace std;
void Loop();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Loop();
	getch();
}
void Time(const char* name,const std::function<void()>& func)
{

	std::chrono::system_clock::time_point Start = std::chrono::system_clock::now();
	func();
	std::chrono::system_clock::time_point End = std::chrono::system_clock::now();

	std::chrono::duration<double> sec = End - Start;
	std::cout << name << ": " << sec.count() << " sec" <<endl;
}
void insert()
{


}
void Loop()
{
	JMap<int, int> map;
	std::map<int, int> mmap;
	std::cout << "1000000번(백만번) 속도 비교 \n" << std::endl;
	Time("JMap insert", [&]()
	{
		for (int i = 0; i < 10000; ++i)
		{
			map.insert(JPair<int, int>(i, i));
		}
	});
	Time("map insert", [&]()
	{
		for (int i = 0; i < 10000; ++i)
		{
			mmap.insert(std::pair<int, int>(i, i));
		}
	});
	cout << endl;
	Time("JMap operator[]", [&]()
	{
		map[1000];
	});
	Time("map operator[]", [&]()
	{
		mmap[1000];
	});
	cout << endl;
	Time("JMap Erase", [&]()
	{
		for (int i = 0; i < 10000; ++i)
		{
			map.remove(i);
		}
	});
	Time("map Erase", [&]()
	{
		for (int i = 0; i < 10000; ++i)
		{
			mmap.erase(i);
		}
	});

	JHash_Map<int, int> s;

	s.insert(JPair<int, int>(2, 2));
	s.safe_index(2);



	/*JHash_Map<int, int> m;

	for (int i = 0; i < 500; ++i)
	{
		m.insert(JPair<int, int>(i, i));
	}

	JHash_Map<int, int> m2(m);


	for (auto iter = m2.begin(); iter < m2.end(); ++iter)
	{
		cout << iter->first << endl;
	}

	m.clear();

	for (auto iter = m.begin(); iter < m.end(); ++iter)
	{
		cout << iter->first << endl;
	}*/
	//m.Write_cpp();
}



