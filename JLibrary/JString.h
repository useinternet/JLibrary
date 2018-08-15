#pragma once
#include<Windows.h>


class JString
{
private:
	char* m_cString;
	wchar_t* m_wString;
public:
	JString();
	~JString();

	char* c_str();
	wchar_t* w_str();
	JString& operator=(const char* str);
};