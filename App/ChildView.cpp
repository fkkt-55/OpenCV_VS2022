
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "App.h"
#include "ChildView.h"
#include <face_dector.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	view = std::make_unique<VideoView>();
}

CChildView::~CChildView()
{
	if (view)
	{
		view.reset();
	}
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
	CPaintDC dc(this);

	cv::VideoCapture cap(0);  // 打开默认摄像头，或者提供摄像头编号
	cv::Mat frame;

	if (!cap.isOpened()) {
		// 处理摄像头未能打开的情况
		return;
	}

	cv::CascadeClassifier faceCascade;
	if (!faceCascade.load("c:/tools/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml")) {
		// 处理人脸检测器加载失败的情况
		return;
	}

	//while (true)
	//{
	cap >> frame; // 捕获一帧图像

	if (!frame.empty()) {
		CImage imageView;
		imageView.Create(frame.cols, frame.rows, 24);
		uchar* dest = (uchar*)imageView.GetBits();
		int destPitch = imageView.GetPitch();
		uchar* src = frame.data;
		size_t srcStep = frame.step;
		for (int i = 0; i < frame.rows; i++) {
			memcpy(dest, src, static_cast<size_t>(frame.cols) * 3);
			dest += destPitch;
			src += srcStep;
		}

		// 进行人脸检测
		std::vector<cv::Rect> faces;
		cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY); // 将图像转换为灰度图
		faceCascade.detectMultiScale(frame, faces);

		// 绘制检测到的人脸
		for (const cv::Rect& faceRect : faces) {
			// 缩放人脸框以匹配原图像
			cv::Rect originalFace = cv::Rect(faceRect.x / 1.0, faceRect.y / 1.0, faceRect.width / 1.0, faceRect.height / 1.0);
			cv::rectangle(frame, originalFace, cv::Scalar(0, 0, 255), cv::LineTypes::LINE_4); // 绘制红色的人脸框
		}

		// 绘制图像
		imageView.Draw(dc.GetSafeHdc(), CRect(0, 0, frame.cols, frame.rows));

		// 释放图像资源
		imageView.Destroy();

		Sleep(1.000);
	}
	//}
	cap.release();  // 释放摄像头资源
}


//void CChildView::OnPaint()
//{
//	CPaintDC dc(this); // 用于绘制的设备上下文
//	//String imagePath("D:/Sample/images/合影.jpg");
//	//String faceCascadeFile = "c:/tools/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
//	//FaceDector faceDector = FaceDector::getInstance(faceCascadeFile);
//	//faceDector.detect(imagePath, dc);
//
//	//// 创建和初始化CStatic控件
//	//CRect rect; // 定义控件的位置和大小
//	//rect.left = 10; // 左上角X坐标
//	//rect.top = 10;  // 左上角Y坐标
//	//rect.right = 1000; // 右下角X坐标
//	//rect.bottom = 500; // 右下角Y坐标
//
//	//m_static.Create(_T("你的文本或内容"), WS_CHILD | WS_VISIBLE, rect, this);
//	////view->init();
//	////view->showVideo(&m_static);
//	//// 创建并启动视频处理线程
//
//	//std::thread videoThread([this]() {
//	//	cv::VideoCapture cap;
//	//	cv::Mat frame;
//	//	CImage imageView;
//	//	cap.open(0);
//	//	// 在这里处理视频捕获和显示的代码
//	//	while (1) {
//	//		cap >> frame; // 捕获一帧图像
//	//		if (frame.empty()) {
//	//			break;
//	//		}
//	//		// 将OpenCV的Mat对象转换为MFC的CImage对象
//	//		imageView.Create(frame.cols, frame.rows, 24);
//	//		uchar* dest = (uchar*)imageView.GetBits();
//	//		int destPitch = imageView.GetPitch();
//	//		uchar* src = frame.data;
//	//		size_t srcStep = frame.step;
//	//		for (int i = 0; i < frame.rows; i++) {
//	//			memcpy(dest, src, static_cast<size_t>(frame.cols) * 3); // 3通道图像
//	//			dest += destPitch;
//	//			src += srcStep;
//	//		}
//	//		// 在图像控件中显示图像
//	//		m_static.SetBitmap(imageView.Detach());
//	//		imageView.Destroy();
//	//		// 可以在这里添加适当的延时，以控制帧率
//	//		//Sleep(5000);
//	//	}}
//	//);
//
//	//// 等待线程完成
//	//videoThread.detach();
//}
