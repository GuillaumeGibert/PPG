/**
* \file MainWindow.h
* \brief Defines Application
* \author Guillaume Gibert
* \date 19/07/2019
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QMessagebox.h>
#include <QFileDialog>

// OpenCV
#include "opencv2/opencv.hpp"

#include "ImageDisplay.h"

// Qt stuff
namespace Ui {
class MainWindow;
}


/**
* \class MainWindow
* \brief Represents the main window of the application.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	* \brief The constructor.
	* \param [in] parent: the widget parent
	*/
    explicit MainWindow(QWidget *parent = 0);

	
	/**
	* \brief The function to delete the object.
	*/
	~MainWindow();

	

public slots:
	void setWebcamFrame(cv::Mat);
	void setFaceRectangles(std::vector<cv::Rect>);

	

signals:
	
private:
	void initWidgets();
	void updateWebcamDisplay();
	QImage mat2QImage(const cv::Mat3b & oMat);

private:
    Ui::MainWindow *ui;									// Also Qt stuff
	
	ImageDisplay* m_pWImageDisplay;
	cv::Mat m_oWebcamFrame;
	std::vector<cv::Rect> m_vFaceRectangles;
};

#endif // MAINWINDOW_H
