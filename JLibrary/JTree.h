#pragma once
#include<iostream>
#include<initializer_list>
#include <assert.h>
#include <functional>
#include"JTrace.h"

template<class Data>
class JTree
{
	typedef struct Tree
	{
		Tree* Left;
		Tree* Right;
		Data data;
	};

public:
	JTree();
	~JTree();

};
