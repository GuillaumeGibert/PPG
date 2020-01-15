/**
* \file MainWindow.cpp
* \brief Defines the main Qt window
* \author Guillaume Gibert
* \date 19/07/2019
*/

#include "interface/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	m_pWImageDisplay(nullptr), m_pWTemporalSignalDisplay(nullptr), m_pWBufferedSignalDisplay(nullptr)
{
	ui->setupUi(this);
	//this->setWindowTitle(QString("PPG"));
	
	initWidgets();
	
}

MainWindow::~MainWindow()
{
	if (nullptr != m_pWImageDisplay)
	{
		delete m_pWImageDisplay;
		m_pWImageDisplay = nullptr;
	}

	if (nullptr != m_pWTemporalSignalDisplay)
	{
		delete m_pWTemporalSignalDisplay;
		m_pWTemporalSignalDisplay = nullptr;
	}
	
	if (nullptr != m_pWBufferedSignalDisplay)
	{
		delete m_pWBufferedSignalDisplay;
		m_pWBufferedSignalDisplay = nullptr;
	}
}

void MainWindow::initWidgets()
{
	// Image display
	if (nullptr == m_pWImageDisplay)
	{
		m_pWImageDisplay = new ImageDisplay();
		m_pWImageDisplay->setMinimumSize(600, 600);
		ui->vlWebcam->addWidget(m_pWImageDisplay);
	}

	// Signal display
	if (nullptr == m_pWTemporalSignalDisplay)
	{
		m_pWTemporalSignalDisplay = new TemporalSignalDisplay();
		m_pWTemporalSignalDisplay->setMinimumSize(600, 600);
		m_pWTemporalSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B"); 
		m_pWTemporalSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWTemporalSignalDisplay->setFps(30.0);
		m_pWTemporalSignalDisplay->setXYRange(QSize(0, 5), QSize(0, 250));
		m_pWTemporalSignalDisplay->setLegends("Time (s)", "Color amplitude");
		m_pWTemporalSignalDisplay->setTicks(1, 50);
		m_pWTemporalSignalDisplay->setDrawLine(true);
			   		 
		ui->vlSignal->addWidget(m_pWTemporalSignalDisplay);
	}

	// Buffered Signal display
	if (nullptr == m_pWBufferedSignalDisplay)
	{
		m_pWBufferedSignalDisplay = new BufferedSignalDisplay();
		m_pWBufferedSignalDisplay->setMinimumSize(600, 600);
		m_pWBufferedSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWBufferedSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWBufferedSignalDisplay->setFps(30.0);
		m_pWBufferedSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWBufferedSignalDisplay->setLegends("Time (s)", "Color amplitude");
		m_pWBufferedSignalDisplay->setTicks(1, 50);
		m_pWBufferedSignalDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWBufferedSignalDisplay);
	}
	
}

void MainWindow::updateWebcamDisplay()
{
	// do not display an empty frame
	if (m_oWebcamFrame.empty())
		return;

	// check if face(s) was(were) detected
	if (m_vFaceRectangles.size() > 0)
	{
		for (size_t i = 0; i < m_vFaceRectangles.size(); i++)
		{
			int x1 = (int)(m_vFaceRectangles[i].x);
			int y1 = (int)(m_vFaceRectangles[i].y);
			int x2 = (int)((m_vFaceRectangles[i].x + m_vFaceRectangles[i].width));
			int y2 = (int)((m_vFaceRectangles[i].y + m_vFaceRectangles[i].height));
			cv::rectangle(m_oWebcamFrame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 1, 4);
		}
	}

	m_pWImageDisplay->refreshDisplay(mat2QImage(m_oWebcamFrame));
}

QImage MainWindow::mat2QImage(const cv::Mat3b & oMat)
{
	QImage l_oQImage(oMat.cols, oMat.rows, QImage::Format_ARGB32);

	for (int jj = 0; jj < oMat.rows; ++jj)
	{
		const cv::Vec3b *l_oMatRow = oMat[jj];

		QRgb *l_oQIRow = (QRgb*)l_oQImage.scanLine(jj);

		for (int ii = 0; ii < oMat.cols; ++ii)
		{
			l_oQIRow[ii] = qRgba(l_oMatRow[ii][2], l_oMatRow[ii][1], l_oMatRow[ii][0], 255);
		}
	}

	return l_oQImage;
}

void MainWindow::setWebcamFrame(cv::Mat oWebcamFrame)
{
	m_oWebcamFrame = oWebcamFrame;
	updateWebcamDisplay();
}

void MainWindow::setFaceRectangles(std::vector<cv::Rect> vFaceRectangles)
{
	m_vFaceRectangles = vFaceRectangles;
	updateWebcamDisplay();
}

void MainWindow::setRGBMeanValues(float timestamp, std::vector<float> vRGBMeanValues)
{
	m_pWTemporalSignalDisplay->setNewValues(vRGBMeanValues);
}

void MainWindow::setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues)
{
	m_pWBufferedSignalDisplay->setNewValues(vBufferedSignalValues);
}