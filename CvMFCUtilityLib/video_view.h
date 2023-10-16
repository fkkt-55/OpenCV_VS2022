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
	// 摄像头捕获对象
	cv::VideoCapture cap;
};

