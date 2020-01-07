#include "workers/WorkerPreProcessing.h"

WorkerPreProcessing::WorkerPreProcessing()
{
	m_pFaceDetector = nullptr;
	m_bIsWorkerInitialized = false;

	init();
}

WorkerPreProcessing::~WorkerPreProcessing()
{
	if (nullptr != m_pFaceDetector)
	{
		delete m_pFaceDetector;
		m_pFaceDetector = nullptr;
	}
}

bool WorkerPreProcessing::init()
{
	if (nullptr == m_pFaceDetector)
	{
		m_pFaceDetector = new FaceDetection();
		m_pFaceDetector->init();
		m_bIsWorkerInitialized = true;
	}

	return m_bIsWorkerInitialized;
}

void WorkerPreProcessing::setCurrentFrame(cv::Mat oCurrentFrame)
{
	m_oWorkerMutex.lockForWrite();
		m_oCurrentFrame = oCurrentFrame;
	m_oWorkerMutex.unlock();
}

void WorkerPreProcessing::doWork()
{
	if (!m_bIsWorkerInitialized)
	{
		return;
		if (m_bVerbose)
			qDebug() << "[WARNING] (WorkerPreProcessing::doWork): Worker not initialized!";
	}

	m_oWorkerMutex.lockForRead();
		cv::Mat l_oCurrentFrame = m_oCurrentFrame;
	m_oWorkerMutex.unlock();

	if (!l_oCurrentFrame.empty())
	{
		// detects face(s) in the current image
		std::vector<cv::Rect> l_vFaceRectangles = m_pFaceDetector->detect(l_oCurrentFrame);
		if (l_vFaceRectangles.size() > 0)
			emit sigBroadcastFaceRectangles(l_vFaceRectangles);

		// TODO resize the rectangle to take into account the forehead only

		// estimates the average R, G, B value in the ROI
		cv::Mat l_oFaceFrame = l_oCurrentFrame(l_vFaceRectangles[0]);
		cv::Scalar l_oMeanRGB = cv::mean(l_oFaceFrame);
		std::vector<float> l_vRGBMeanValues{ (float)l_oMeanRGB[0], (float)l_oMeanRGB[1], (float)l_oMeanRGB[2] };
		emit sigBroadcastRGBMeanValues(l_vRGBMeanValues);
		//std::cout << "mean R,G,B = (" << l_oMeanRGB[0] << ", " << l_oMeanRGB[1] << ", " << l_oMeanRGB[2] << ", " << l_oMeanRGB[3]<<  ")" << std::endl;
	}
	else
		if (m_bVerbose)
			qDebug() << "[WARNING] (WorkerPreProcessing::doWork): Frame is empty!";
}