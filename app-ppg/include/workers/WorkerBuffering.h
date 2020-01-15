#ifndef _WORKER_BUFFERING_H
#define _WORKER_BUFFERING_H

#include "workers\Worker.h"
#include "Buffering.h"

class WorkerBuffering : public Worker
{
	Q_OBJECT

public:
	WorkerBuffering();
	~WorkerBuffering();

protected:
	void doWork();
	bool init();

public slots:
	void setSignalValues(float, std::vector<float>);

signals:
	void sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>);
	
private:
	Buffering* m_pBuffer;

};

#endif