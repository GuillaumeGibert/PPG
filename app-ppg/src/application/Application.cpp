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
	// sends a signal to stop the webcam timer
	emit sigStopWebcam();
	emit sigStopPreProcessing();

	// stops the threads
	stopWorkerThreads();

	// deletes the workers
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
	emit sigStartPreProcessing();
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

	// WorkerPreProcessing
	if (nullptr == m_pWorkerPreProcessing)
	{
		m_pWorkerPreProcessing = new WorkerPreProcessing();
		m_pWorkerPreProcessing->setVerboseMode(true);
		m_pWorkerPreProcessing->setFps(30.0);
	}
}

void Application::registerMetaTypes()
{
	// register opencv data types
	qRegisterMetaType< cv::Mat >("cv::Mat");
	qRegisterMetaType< std::vector<cv::Rect> >("std::vector<cv::Rect>");
	qRegisterMetaType< std::vector<float> >("std::vector<float>");
}

void Application::setWorkerConnections()
{
	// WorkerWebcam
	QObject::connect(m_pWorkerWebcam, SIGNAL(sigBroadcastWebcamFrame(cv::Mat)), m_window, SLOT(setWebcamFrame(cv::Mat)));
	QObject::connect(m_pWorkerWebcam, SIGNAL(sigBroadcastWebcamFrame(cv::Mat)), m_pWorkerPreProcessing, SLOT(setCurrentFrame(cv::Mat)));

	QObject::connect(this, SIGNAL(sigStartWebcam()), m_pWorkerWebcam, SLOT(startWork()));
	QObject::connect(this, SIGNAL(sigStopWebcam()), m_pWorkerWebcam, SLOT(stopWork()), Qt::BlockingQueuedConnection);

	// WorkerPreProcessing
	QObject::connect(this, SIGNAL(sigStartPreProcessing()), m_pWorkerPreProcessing, SLOT(startWork()));
	QObject::connect(this, SIGNAL(sigStopPreProcessing()), m_pWorkerPreProcessing, SLOT(stopWork()), Qt::BlockingQueuedConnection);

	QObject::connect(m_pWorkerPreProcessing, SIGNAL(sigBroadcastFaceRectangles(std::vector<cv::Rect>)), m_window, SLOT(setFaceRectangles(std::vector<cv::Rect>)));
	QObject::connect(m_pWorkerPreProcessing, SIGNAL(sigBroadcastRGBMeanValues(std::vector<float>)), m_window, SLOT(setRGBMeanValues(std::vector<float>)));
}

void Application::moveWorkersToThread()
{
	// WorkerWebcam
	if (nullptr != m_pWorkerWebcam)
	{
		m_pWorkerWebcam->moveToThread(&m_TWorkerWebcam);
		m_TWorkerWebcam.start();
	}

	// WorkerPreProcessing
	if (nullptr != m_pWorkerPreProcessing)
	{
		m_pWorkerPreProcessing->moveToThread(&m_TWorkerPreProcessing);
		m_TWorkerPreProcessing.start();
	}
}

void Application::stopWorkerThreads()
{
	m_TWorkerWebcam.quit();
	m_TWorkerWebcam.wait();

	m_TWorkerPreProcessing.quit();
	m_TWorkerPreProcessing.wait();
}

void Application::deleteWorkers()
{
	if (nullptr != m_pWorkerWebcam)
	{
		delete m_pWorkerWebcam;
		m_pWorkerWebcam = nullptr;
	}
		

	if (nullptr != m_pWorkerPreProcessing)
	{
		delete m_pWorkerPreProcessing;
		m_pWorkerPreProcessing = nullptr;
	}
		
}
