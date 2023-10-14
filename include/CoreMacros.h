#pragma once
#ifndef __KT_CORE_MARCOS__
#define __KT_CORE_MARCOS__

#include <windows.h>
#include <tchar.h>

#include <string>

typedef std::string String;

#ifdef _DEBUG
#define MessageD(x) MessageBox(_T(x), L"DEBUG")
#else
#define MessageD(x) (x)
#endif // _DEBUG
#define MessageI(x) MessageBox(_T(x), L"Ã· æ")
#define MessageE(x) MessageBox(_T(x), L"¥ÌŒÛ")

class CoreMacros
{
};

#endif // !__KT_CORE_MARCOS__