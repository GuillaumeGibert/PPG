#ifndef TEMPORAL_FILTER_H
#define TEMPORAL_FILTER_H

#include <QObject>
#include <vector>
#include <iostream>
#include <deque>

class TemporalFilter : public QObject
{
	Q_OBJECT
	
	public:
		TemporalFilter();
		TemporalFilter(bool bVerboseMode);
		~TemporalFilter();
	
	public:
        void filt(std::deque<float>& inSignal, std::deque<float>& outSignal);
	
        void setAFilterCoefficients(std::vector<float> aFilterCoefficients);
        void setBFilterCoefficients(std::vector<float> bFilterCoefficients);
	
	private:
		bool m_bVerboseMode;
	
        std::vector<float> m_aFilterCoefficients;
        std::vector<float> m_bFilterCoefficients;
};


#endif
