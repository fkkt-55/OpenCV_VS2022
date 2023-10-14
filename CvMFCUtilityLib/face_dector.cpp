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

	// ���ͼ���Ƿ���سɹ�
	if (!image.empty())
	{
		// ����һ�����������
		cv::CascadeClassifier faceCascade;
		if (faceCascade.load(faceCascadeFilePath))
		{
			// ��ȡ��Ļ��С
			CRect screenRect;
			dc.GetClipBox(&screenRect);

			// ����ͼ������Ӧ��Ļ
			cv::Mat scaledImage;
			double scale = std::min(static_cast<double>(screenRect.Width()) / image.cols,
									static_cast<double>(screenRect.Height()) / image.rows);
			cv::resize(image, scaledImage, cv::Size(), scale, scale);

			// ת��Ϊ�Ҷ�ͼ������߼������
			cv::Mat grayImage;
			cv::cvtColor(scaledImage, grayImage, cv::COLOR_BGR2GRAY);

			// �������
			std::vector<cv::Rect> faces;
			faceCascade.detectMultiScale(grayImage, faces, 1.1, 3, 0, cv::Size(30, 30));

			// ��ͼ���ϻ��Ƽ�⵽��������
			for (const cv::Rect& face : faces)
			{
				// ������������ƥ��ԭͼ��
				cv::Rect originalFace = cv::Rect(face.x / scale, face.y / scale, face.width / scale, face.height / scale);
				cv::rectangle(image, originalFace, cv::Scalar(0, 0, 255), cv::LineTypes::LINE_4); // ���ƺ�ɫ��������
			}

			// �� OpenCV ͼ��ת��Ϊλͼ
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

			// ����λͼ
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
