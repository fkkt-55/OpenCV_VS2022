
// App.h: App 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号
#include "CAboutDlg.h"

class CAppApp : public CWinApp
{
public:
	CAppApp() noexcept;

	// 重写
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;

	// 实现

public:
	afx_msg void OnAppAbout();
	afx_msg void OnLoadImg();
	DECLARE_MESSAGE_MAP()
};

extern CAppApp theApp;
