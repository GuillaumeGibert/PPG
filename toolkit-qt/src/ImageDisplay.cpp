#include "ImageDisplay.h"


#include <QResizeEvent>
#include <iostream>

using namespace std;

ImageDisplay::ImageDisplay(QWidget* oParent, const bool bScaleImage) : m_oSize(size()), m_bScaleImage(bScaleImage)
{
	this->setParent(oParent); 
	m_bScaleImage = false;
}

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

	painter.drawImage(QPoint(), m_oScaledImage);
}





void ImageDisplay::resizeEvent ( QResizeEvent * event )
{
	m_oSize = event->size();
	resize(m_oSize);
}

void ImageDisplay::refreshDisplay(const QImage &oQImage)
{
	m_oQImage = oQImage.copy();
	update();
}


