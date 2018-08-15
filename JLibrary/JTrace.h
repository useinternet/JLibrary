#pragma once


#include<Windows.h>
/**  2018.07.08  �۾�

** Trace ���� �ʾ� (��ǥ)

DebugLog  :  ����� ����Ͻÿ��� ���â�� ���(����, ����,��������)
DebugLog  :  ���� �����ϳ� ���ڿ��� ����

*/
#include<Windows.h>
#define Text(x) Lx

inline void DebugLog(const WCHAR* format, ...)
{
#if _DEBUG
	WCHAR buffer[256];

	va_list Arglist;
	va_start(Arglist, format);
	wsprintfW(buffer, format, Arglist);
	OutputDebugStringW(buffer);
	va_end(Arglist);
#endif 
}

inline void DebugLog(const TCHAR* format, ...)
{
#if _DEBUG
	TCHAR buffer[256];

	va_list Arglist;
	va_start(Arglist, format);
	wvsprintf(buffer, format, Arglist);
	OutputDebugString(buffer);
	va_end(Arglist);
#endif 
}






