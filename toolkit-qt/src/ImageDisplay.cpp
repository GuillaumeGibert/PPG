#include "ImageDisplay.h"


#include <QResizeEvent>
#include <iostream>

using namespace std;

ImageDisplay::ImageDisplay() 
{}

ImageDisplay::~ImageDisplay()
{}

void ImageDisplay::paintEvent(QPaintEvent *)
{
	// update  image
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if(m_oQImage.isNull())
	{
		return;
	}

	painter.drawImage(QPoint(), m_oQImage);

}




void ImageDisplay::refreshDisplay(const QImage &oQImage)
{
	m_oQImage = oQImage.copy();
	resize(QSize(m_oQImage.width(), m_oQImage.height()));
	
	update();
}


