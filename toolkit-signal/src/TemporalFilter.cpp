#include "TemporalFilter.h"
#include <QDebug>

TemporalFilter::TemporalFilter(bool bVerboseMode):
	m_bVerboseMode(bVerboseMode)
{
	
}

TemporalFilter::TemporalFilter() : TemporalFilter(true)
{
	
}

TemporalFilter::~TemporalFilter()
{
	
}

void TemporalFilter::filt(std::deque<float>& inSignal, std::deque<float>& outSignal)
{
	if (inSignal.size() == 0 || outSignal.size() == 0 || m_aFilterCoefficients.size() == 0 || m_bFilterCoefficients.size() == 0)
	{
        std::cout << "[ERROR] (TemporalFilter::filt) size of one of the vectors is 0!" << std::endl;
		return;
	}

    int l_sample = inSignal.size()-1;

    double l_dWeightedInputSum = 0.0;
    for (auto l_coef = 0; l_coef < m_bFilterCoefficients.size(); l_coef++)
    {
        if (l_sample - l_coef >= 0)
        {
            l_dWeightedInputSum += m_bFilterCoefficients[l_coef] * inSignal[l_sample - l_coef];
        }
    }

    double l_dWeightedOuputSum = 0.0;
    for (auto l_coef = 1; l_coef < m_aFilterCoefficients.size(); l_coef++)
    {
        if (l_sample - l_coef >= 0)
        {
            l_dWeightedOuputSum += m_aFilterCoefficients[l_coef] * outSignal[l_sample - l_coef];
        }
    }

    outSignal[l_sample] = l_dWeightedInputSum - l_dWeightedOuputSum;

}


void TemporalFilter::setAFilterCoefficients(std::vector<float> aFilterCoefficients)
{
	m_aFilterCoefficients.clear();
	m_aFilterCoefficients = aFilterCoefficients;
}

void TemporalFilter::setBFilterCoefficients(std::vector<float> bFilterCoefficients)
{
	m_bFilterCoefficients.clear();
	m_bFilterCoefficients = bFilterCoefficients;
}


