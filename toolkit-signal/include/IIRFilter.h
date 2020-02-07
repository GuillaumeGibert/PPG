#ifndef IIR_FILTER_H
#define IIR_FILTER_H

#include <QObject>
#include <vector>
#include <iostream>
#include <deque>

class IIRFilter : public QObject
{
	Q_OBJECT
	
	public:
		IIRFilter();
		IIRFilter(bool bVerboseMode);
		~IIRFilter();
	
	public:
		void setOrder(int);
	
	public:
		std::vector<float> getAFilterCoefficients();
		std::vector<float> getBFilterCoefficients();
		
	
	private:
		bool m_bVerboseMode;
	
		int m_i32Order;
	
		std::vector<float> m_vAFilterCoefficients;
		std::vector<float> m_vBFilterCoefficients;
};


#endif