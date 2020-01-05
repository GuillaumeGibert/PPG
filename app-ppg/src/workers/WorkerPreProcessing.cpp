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

	}
	else
		if (m_bVerbose)
			qDebug() << "[WARNING] (WorkerPreProcessing::doWork): Frame is empty!";
}