#include "WebcamManager.h"

WebcamManager::WebcamManager()
{
	m_bIsWebcamOpened = false;
}

WebcamManager::~WebcamManager()
{

}

void WebcamManager::init()
{
	// opens the default camera
	m_oWebcam.open(0); 

	// checks if it is opened
	if (m_oWebcam.isOpened())
		m_bIsWebcamOpened = true;

}

void WebcamManager::grab()
{
	// checks if the camera is opened
	if (!m_bIsWebcamOpened)
		return;

	// gets a new frame from camera
	cv::Mat l_oFrame;
	m_oWebcam >> l_oFrame; 

	if (!l_oFrame.empty())
	{
		//imshow("test", l_oFrame);
		emit sigBroadcastWebcamFrame(l_oFrame);
	}
}

void WebcamManager::close()
{
	// the camera will be closed automatically upon exit
	m_oWebcam.release();
	m_bIsWebcamOpened = false;
}
