﻿
// Demo.h: Demo 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号
#include "CAboutDlg.h"

// CDemoApp:
// 有关此类的实现，请参阅 Demo.cpp
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp() noexcept;

	// 重写
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;

	// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDemoApp theApp;