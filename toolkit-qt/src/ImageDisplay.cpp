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


	if(m_bScaleImage)
	{
		m_oScaledImage = m_oQImage.scaled(m_oSize,
		      Qt::KeepAspectRatio
		      ,Qt::SmoothTransformation
		      );
	}
	else
	{
		m_oScaledImage = m_oQImage;
	}

	painter.drawImage(0,0, m_oScaledImage);

	//painter.drawImage(QPoint(), m_oQImage);

}




void ImageDisplay::refreshDisplay(const QImage &oQImage)
{
	m_oQImage = oQImage.copy();
	resize(QSize(m_oQImage.width(), m_oQImage.height()));
	
	update();
}


