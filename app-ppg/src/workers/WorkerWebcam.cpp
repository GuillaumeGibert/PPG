#include "workers/WorkerWebcam.h"

WorkerWebcam::WorkerWebcam()
{
	m_pWebcamManager = nullptr;
	m_bIsWorkerInitialized = false;

	init();
}

WorkerWebcam::~WorkerWebcam()
{
	if (nullptr != m_pWebcamManager)
	{
		m_pWebcamManager->close();
		delete m_pWebcamManager;
	}
}

bool WorkerWebcam::init()
{
	if (nullptr == m_pWebcamManager)
	{
		m_pWebcamManager = new WebcamManager();
		m_pWebcamManager->init();
		m_bIsWorkerInitialized = true;
	}

	return m_bIsWorkerInitialized;
}

void WorkerWebcam::doWork()
{
	if (!m_bIsWorkerInitialized)
	{
		return;
		if (m_bVerbose)
			qDebug() << "[WARNING] (WorkerWebcam::doWork): Worker not initialized!";
	}

	cv::Mat l_oFrame = m_pWebcamManager->grab();

	if (!l_oFrame.empty())
		emit sigBroadcastWebcamFrame(l_oFrame);
	else
		if (m_bVerbose)
			qDebug() << "[WARNING] (WorkerWebcam::doWork): Frame is empty!";
}