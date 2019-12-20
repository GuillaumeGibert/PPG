#ifndef FACE_DETECTION_
#define FACE_DETECTION_

#include <opencv2/core/persistence.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui.hpp"

#include <iostream>

class FaceDetection
{
	public:
		FaceDetection();
		virtual ~FaceDetection();

		bool init();
		bool loadConfigFile();
		bool detect(cv::Mat);

private:
	std::string m_sConfigFilename;
	
	std::string m_sCascadeClassifierFilename;
	cv::CascadeClassifier* m_pCascadeClassifier;

};

#endif