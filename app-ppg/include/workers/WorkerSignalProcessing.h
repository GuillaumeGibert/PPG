#ifndef _WORKER_SIGNAL_PROCESSING_H
#define _WORKER_SIGNAL_PROCESSING_H

#include "workers\Worker.h"


class WorkerSignalProcessing : public Worker
{
	Q_OBJECT

public:
	WorkerSignalProcessing();
	~WorkerSignalProcessing();

protected:
	void doWork();
	bool init();

public slots:
	

signals:
	

private:
	

};

#endif