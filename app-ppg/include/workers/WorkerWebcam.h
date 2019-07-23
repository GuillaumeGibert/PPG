#ifndef _WORKER_WEBCAM_H
#define _WORKER_WEBCAM_H

#include "workers\Worker.h"
#include "WebcamManager.h"

class WorkerWebcam : public Worker
{
	Q_OBJECT

public:
	WorkerWebcam();
	~WorkerWebcam();

protected:
	void doWork();
	bool init();

signals:
	void sigBroadcastWebcamFrame(cv::Mat);

private:
	WebcamManager* m_pWebcamManager;

};

#endif