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

cv::Mat WebcamManager::grab()
{
	cv::Mat l_oFrame;

	// checks if the camera is opened
	if (!m_bIsWebcamOpened)
		return l_oFrame;

	// gets a new frame from camera
	m_oWebcam >> l_oFrame; 

	return l_oFrame;
}

void WebcamManager::close()
{
	// the camera will be closed automatically upon exit
	m_oWebcam.release();
	m_bIsWebcamOpened = false;
}
