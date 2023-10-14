#include "pch.h"
#include "face_dector.h"

FaceDector::FaceDector(const String& faceCascadeFile)
{
	faceCascadeFilePath = faceCascadeFile;
}

FaceDector& FaceDector::getInstance(const String& faceCascadePath)
{
	static FaceDector instance(faceCascadePath);
	return instance;
}

FaceDector::~FaceDector()
{
}
bool FaceDector::detect(const String& imagePath, CPaintDC& dc)
{
	cv::Mat image = cv::imread(imagePath);

	// 检查图像是否加载成功
	if (!image.empty())
	{
		// 创建一个人脸检测器
		cv::CascadeClassifier faceCascade;
		if (faceCascade.load(faceCascadeFilePath))
		{
			// 获取屏幕大小
			CRect screenRect;
			dc.GetClipBox(&screenRect);

			// 缩放图像以适应屏幕
			cv::Mat scaledImage;
			double scale = std::min(static_cast<double>(screenRect.Width()) / image.cols,
									static_cast<double>(screenRect.Height()) / image.rows);
			cv::resize(image, scaledImage, cv::Size(), scale, scale);

			// 转换为灰度图像以提高检测性能
			cv::Mat grayImage;
			cv::cvtColor(scaledImage, grayImage, cv::COLOR_BGR2GRAY);

			// 检测人脸
			std::vector<cv::Rect> faces;
			faceCascade.detectMultiScale(grayImage, faces, 1.1, 3, 0, cv::Size(30, 30));

			// 在图像上绘制检测到的人脸框
			for (const cv::Rect& face : faces)
			{
				// 缩放人脸框以匹配原图像
				cv::Rect originalFace = cv::Rect(face.x / scale, face.y / scale, face.width / scale, face.height / scale);
				cv::rectangle(image, originalFace, cv::Scalar(0, 0, 255), cv::LineTypes::LINE_4); // 绘制红色的人脸框
			}

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

			return true;
		}
		else
		{
			throw std::exception("can't load face cascade");
		}
	}
	else
	{
		throw std::exception("image file load failed");
	}
	return false;
}
