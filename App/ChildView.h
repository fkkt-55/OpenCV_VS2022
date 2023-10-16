
// ChildView.h: CChildView 类的接口
//


#pragma once
#include <memory>
#include <video_view.h>

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

// 实现
public:
	virtual ~CChildView();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	CStatic m_static;
	std::unique_ptr<VideoView> view;
};
