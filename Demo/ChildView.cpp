
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Demo.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	//CPoint points[]{ CPoint(100,100),CPoint(1002,924) };
	//dc.Polygon(points, sizeof(points));

	//CRect rect;
	//GetClientRect(&rect);

	//CClientDC dc(this);
	//dc.MoveTo(rect.left, rect.top);
	//dc.LineTo(rect.right, rect.bottom);
	//dc.MoveTo(rect.right, rect.top);
	//dc.LineTo(rect.left, rect.bottom);


	// 使用 OpenCV 加载图像
	cv::Mat image = cv::imread("c:/opencv/OpenCV_Logo.png");

	// 检查图像是否加载成功
	if (!image.empty())
	{
		// 将 OpenCV 图像转换为位图
		CImage cimg;
		cimg.Create(image.cols, image.rows, 24);
		uchar* ptrDst = (uchar*)cimg.GetBits();
		int bytesPerRow = cimg.GetPitch();

		for (int i = 0; i < image.rows; i++)
		{
			uchar* ptrSrc = image.ptr(i);
			memcpy(ptrDst, ptrSrc, static_cast<size_t>(image.cols) * 3); // 3 channels (BGR)
			ptrDst += bytesPerRow;
		}

		// 绘制位图
		cimg.BitBlt(dc, 0, 0);
	}
}

