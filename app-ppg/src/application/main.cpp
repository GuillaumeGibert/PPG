/**
* \file main.cpp
* \brief Defines the main
* \author Guillaume Gibert
* \date 14/11/2018
*/

#include "application/Application.h"
#include <QApplication>

#include <QtWidgets/QApplication>
 
#include "WebcamManager.h"


int main(int argc, char *argv[]) 
{ 
	//QApplication app(argc, argv);  
	/*
	WebcamManager l_oWebcam;
	l_oWebcam.init();

	for (;;)
	{
		l_oWebcam.grab();
		if (cv::waitKey(10) == 27) 
			break; // stop capturing by pressing ESC 
	}

	l_oWebcam.close();
	*/
	//return app.exec();
	
	
	QApplication a(argc, argv);
	
	Application app;
	MainWindow w;

	w.show();
	app.init(&w);

	return a.exec();
	
}
