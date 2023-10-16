#include "pch.h"
#include "video_image_view.h"

VideoView::VideoView()
{
}

VideoView::~VideoView()
{
	if (cap.isOpened())
	{
		cap.release();
	}
}

bool VideoView::init()
{
	if (!cap.open(0))
	{
		AfxMessageBox(_T("无法打开摄像头"));
		return false;
	}
	return true;;
}

bool VideoView::showVideo(CStatic* pStaticImage)
{
	cv::Mat frame;
	CImage imageView;
	if (!pStaticImage)
	{
		return false;
	}
	if (!init())
	{
		return false;
	}
	while (true) {
		cap >> frame; // 捕获一帧图像

		if (frame.empty()) {
			break;
		}

		// 将OpenCV的Mat对象转换为MFC的CImage对象
		imageView.Create(frame.cols, frame.rows, 24);
		uchar* dest = (uchar*)imageView.GetBits();
		int destPitch = imageView.GetPitch();
		uchar* src = frame.data;
		size_t srcStep = frame.step;
		for (int i = 0; i < frame.rows; i++) {
			memcpy(dest, src, static_cast<size_t>(frame.cols) * 3); // 3通道图像
			dest += destPitch;
			src += srcStep;
		}
		// 在图像控件中显示图像
		pStaticImage->SetBitmap(imageView.Detach());
		imageView.Destroy();
		// 可以在这里添加适当的延时，以控制帧率
		Sleep(5000);
	}
	return true;
}