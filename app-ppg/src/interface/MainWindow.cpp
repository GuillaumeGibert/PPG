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
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);


	
}



MainWindow::~MainWindow()
{
	
}