#ifndef IMAGE_DISPLAY_
#define IMAGE_DISPLAY_

#include <QPainter>
#include <QWidget>


class ImageDisplay : public QWidget
{
	Q_OBJECT

	public:

		/**
		* \brief Default constructor of ImageDisplay
		* \param [in] oParent : QWidget parent
		* \param [in] bScaleImage : true to scale image
		*/		
		ImageDisplay();

		/**
		* \brief Destructor of ImageDisplay
		*/	    
		~ImageDisplay();
		
		
	public slots:

		/**
		* \brief Sets the new image and update the display.
		* \param [in] oQImage : qimage to display in the widget
		*/		
		void refreshDisplay(const QImage &oQImage);

		
	protected:

		/**
		* \brief Paints event.
		* \param [in] QPaintEvent : a pointer to QPaintEvent
		*/		    
		void paintEvent(QPaintEvent *);

signals :
		
		


	private:

		QImage m_oQImage;	/**< rgb image to display */
		
		QSize m_oSize;  /**< size of the image */

};


#endif 
