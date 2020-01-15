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
		m_pBuffer->setDuration(15.0);
		m_pBuffer->setShift(2.0);

		m_bIsWorkerInitialized = true;
	}

	QObject::connect(m_pBuffer, SIGNAL(sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>)), this, SIGNAL(sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>)));

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
	
}