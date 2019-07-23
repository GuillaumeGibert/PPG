/**
* \file Application.cpp
* \brief Defines Application
* \author Guillaume Gibert
* \date 19/07/2019
*/

#include "application/Application.h"

Application::Application()
{
}


Application::~Application()
{
	stopWorkerThreads();

	deleteWorkers();
}

void Application::init(MainWindow* window)
{
	m_window = window;

	initWorkers();
	registerMetaTypes();
	setWorkerConnections();
	moveWorkersToThread();

	emit sigStartWebcam();
}

void Application::initWorkers()
{
	// WorkerWebcam
	if (nullptr == m_pWorkerWebcam)
	{
		m_pWorkerWebcam = new WorkerWebcam();
		m_pWorkerWebcam->setVerboseMode(true);
		m_pWorkerWebcam->setFps(30.0);
	}
}

void Application::registerMetaTypes()
{
	// register opencv data types
	qRegisterMetaType< cv::Mat >("cv::Mat");
}

void Application::setWorkerConnections()
{
	// WorkerWebcam
	QObject::connect(m_pWorkerWebcam, SIGNAL(sigBroadcastWebcamFrame(cv::Mat)), m_window, SLOT(setWebcamFrame(cv::Mat)));

	QObject::connect(this, SIGNAL(sigStartWebcam()), m_pWorkerWebcam, SLOT(startWork()));
}

void Application::moveWorkersToThread()
{
	// WorkerWebcam
	if (nullptr != m_pWorkerWebcam)
	{
		m_pWorkerWebcam->moveToThread(&m_TWorkerWebcam);
		m_TWorkerWebcam.start();
	}
}

void Application::stopWorkerThreads()
{
	m_TWorkerWebcam.quit();
	m_TWorkerWebcam.wait();
}

void Application::deleteWorkers()
{
	if (nullptr != m_pWorkerWebcam)
		delete m_pWorkerWebcam;
}
