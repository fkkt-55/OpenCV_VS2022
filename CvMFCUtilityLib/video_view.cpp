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
		AfxMessageBox(_T("�޷�������ͷ"));
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
		cap >> frame; // ����һ֡ͼ��

		if (frame.empty()) {
			break;
		}

		// ��OpenCV��Mat����ת��ΪMFC��CImage����
		imageView.Create(frame.cols, frame.rows, 24);
		uchar* dest = (uchar*)imageView.GetBits();
		int destPitch = imageView.GetPitch();
		uchar* src = frame.data;
		size_t srcStep = frame.step;
		for (int i = 0; i < frame.rows; i++) {
			memcpy(dest, src, static_cast<size_t>(frame.cols) * 3); // 3ͨ��ͼ��
			dest += destPitch;
			src += srcStep;
		}
		// ��ͼ��ؼ�����ʾͼ��
		pStaticImage->SetBitmap(imageView.Detach());
		imageView.Destroy();
		// ��������������ʵ�����ʱ���Կ���֡��
		Sleep(5000);
	}
	return true;
}