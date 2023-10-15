#pragma once
#ifndef __KT_CORE_MARCOS__
#define __KT_CORE_MARCOS__

#include <string>

#include "framework.h"

#if defined(__AFXWIN_H__)
#ifdef _DEBUG
#define MessageD(x) MessageBox(_T(x), L"DEBUG")
#else
#define MessageD(x) (x)
#endif // _DEBUG
#define MessageI(x) MessageBox(_T(x), L"Ã· æ")
#define MessageE(x) MessageBox(_T(x), L"¥ÌŒÛ")
#elif defined(_WINUSER_)
#ifdef _DEBUG
#define MessageD(x) (x)
#else
#define MessageD(x) (x)
#endif // _DEBUG
#define MessageI(x) (x)
#define MessageE(x) (x)
#endif // defined(__AFXWIN_H__)

#ifdef _DEBUG
#define OPENCV_LIB "opencv_world481d.lib"
#else
#define OPENCV_LIB "opencv_world481.lib"
#endif // _DEBUG

typedef std::string String;

#endif // !__KT_CORE_MARCOS__