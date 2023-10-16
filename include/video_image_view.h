#pragma once
#include <opencv2/opencv.hpp>

class VideoView
{
public:
	VideoView();
	virtual ~VideoView();

public:
	bool init();
	bool showVideo(CStatic* pStaticImage);

private:
	CImage imageView;
	// ����ͷ�������
	cv::VideoCapture cap;
};

