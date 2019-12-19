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
	m_pWImageDisplay(nullptr)
{
	ui->setupUi(this);
	//this->setWindowTitle(QString("PPG"));
	
	initWidgets();
	
}

MainWindow::~MainWindow()
{
	if (nullptr != m_pWImageDisplay)
		delete m_pWImageDisplay;
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
	// TODO
}

void MainWindow::updateWebcamDisplay()
{
	imshow("test", m_oWebcamFrame);
	m_pWImageDisplay->refreshDisplay(mat2QImage(m_oWebcamFrame));
}

QImage MainWindow::mat2QImage(const cv::Mat3b & oMat)
{
	std::cout << "oMat = (" << oMat.cols << ", " << oMat.rows << ")" << std::endl;
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