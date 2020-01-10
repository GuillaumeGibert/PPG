#include "workers/WorkerBuffering.h"

WorkerBuffering::WorkerBuffering()
{
	m_pBuffer = nullptr;
	m_bIsWorkerInitialized = false;

	init();
}

WorkerBuffering::~WorkerBuffering()
{
	if (nullptr != m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = nullptr;
	}
}

bool WorkerBuffering::init()
{
	if (nullptr == m_pBuffer)
	{
		m_pBuffer = new Buffering();
		m_pBuffer->setFps(30);
		m_pBuffer->setNbSignals(3);
		m_pBuffer->setDuration(2.0);
		m_pBuffer->setShift(1.0);

		m_bIsWorkerInitialized = true;
	}

	QObject::connect(m_pBuffer, SIGNAL(sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>)), this, SLOT(sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>)));

	return m_bIsWorkerInitialized;
}


void WorkerBuffering::setSignalValues(float fTimestamp, std::vector<float> vSignalValues)
{
	m_oWorkerMutex.lockForWrite();
		m_pBuffer->setSignalValues(fTimestamp, vSignalValues);
	m_oWorkerMutex.unlock();
}

void WorkerBuffering::doWork()
{
	/*
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
		if (l_vFaceRectangles.size() <= 0)
			return;

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
	*/
}