#ifndef WEBCAM_MANAGER_H
#define WEBCAM_MANAGER_H

#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"

class WebcamManager : public QObject
{
	Q_OBJECT

public:
	WebcamManager();
	~WebcamManager();

	void init();
	cv::Mat grab();
	void close();

private:
	bool m_bIsWebcamOpened;
	cv::VideoCapture m_oWebcam; // open the default camera

};

#endif