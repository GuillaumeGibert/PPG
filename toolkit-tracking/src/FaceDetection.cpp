#include "FaceDetection.h"


FaceDetection::FaceDetection() :
	m_pCascadeClassifier(nullptr)
{

}

FaceDetection::~FaceDetection()
{
	if (nullptr != m_pCascadeClassifier)
	{
		delete m_pCascadeClassifier;
		m_pCascadeClassifier = nullptr;
	}
}


bool FaceDetection::loadConfigFile()
{
	bool l_bIsConfigFileLoaded = true;

	cv::FileStorage l_fsConfigFile(m_sConfigFilename, cv::FileStorage::READ);

	if (l_fsConfigFile.isOpened() == false)
	{
		std::cout << "[ERROR](FaceDetection->loadConfigFile()) Cannot load config file" << std::endl;
		return false;
	}
	l_fsConfigFile["haarcascade"] >> m_sCascadeClassifierFilename;
	
	l_fsConfigFile.release();

	return l_bIsConfigFileLoaded;
}

bool FaceDetection::init()
{
	if (nullptr == m_pCascadeClassifier)
	{
		m_pCascadeClassifier = new cv::CascadeClassifier;
	}
	//TODO REMOVE THIS LINE
	m_sCascadeClassifierFilename = "haarcascade_frontalface_alt.xml";
	if (!m_pCascadeClassifier->load("../data/classifier/" + m_sCascadeClassifierFilename))
	{ 
		std::cout << "[ERROR](FaceDetection->init()) Cannot load cascade classifier file!" << std::endl;
		return false; 
	}

	return true;
}

std::vector<cv::Rect> FaceDetection::detect(cv::Mat frame)
{
	// converts to grayscale
	cv::Mat frameGray;
	cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

	// detects faces in the image
	std::vector<cv::Rect> faceRectangles;
	m_pCascadeClassifier->detectMultiScale(frameGray, faceRectangles);


	for (size_t i = 0; i < faceRectangles.size(); i++)
	{
		int x1 = (int)(faceRectangles[i].x );
		int y1 = (int)(faceRectangles[i].y );
		int x2 = (int)((faceRectangles[i].x + faceRectangles[i].width) );
		int y2 = (int)((faceRectangles[i].y + faceRectangles[i].height) );
		cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 1, 4);
	}

	cv::imshow("OpenCV - HAAR Face Detection", frame);
	//if (faceRectangles.size() > 0)
	//	emit sigBroadcastFaceRectangle(faceRectangles);

	return faceRectangles;
}

