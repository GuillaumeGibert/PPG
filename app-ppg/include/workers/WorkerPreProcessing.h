#ifndef _WORKER_PREPROCESSING_H
#define _WORKER_PREPROCESSING_H

#include "workers\Worker.h"
#include "FaceDetection.h"

class WorkerPreProcessing : public Worker
{
	Q_OBJECT

public:
	WorkerPreProcessing();
	~WorkerPreProcessing();

protected:
	void doWork();
	bool init();

public slots:
	void setCurrentFrame(cv::Mat);

signals:
	void sigBroadcastFaceRectangles(std::vector<cv::Rect>);
	void sigBroadcastRGBMeanValues(float, std::vector<float>);

private:
	FaceDetection* m_pFaceDetector;
	cv::Mat m_oCurrentFrame;

};

#endif