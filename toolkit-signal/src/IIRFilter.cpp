#include "IIRFilter.h"
#include <QDebug>

IIRFilter::IIRFilter(bool bVerboseMode):
	m_bVerboseMode(bVerboseMode)
{
	
}

IIRFilter::IIRFilter() : IIRFilter(true)
{
	
}

IIRFilter::~IIRFilter()
{
	
}

std::vector<float> IIRFilter::getAFilterCoefficients()
{
	return m_vAFilterCoefficients;
}

std::vector<float> IIRFilter::getBFilterCoefficients()
{
	return m_vBFilterCoefficients;
}

void IIRFilter::setOrder(int i32Order)
{
	m_i32Order = i32Order;
}