#include "SignalProcessing.h"



SignalProcessing::SignalProcessing()
{
    m_pFilter = new TemporalFilter();

    // butterworth low-pass, 6th order, Sampling rate = 100 Hz, Cutoff Frequency = 3 Hz
    m_i32FilterOrder = 6;
    std::vector<float> l_aFilterCoefs = { 1.00000f,   -5.27192f,   11.61993f,  -13.70270f,    9.11607f,   -3.24342f,    0.48207f};
    std::vector<float> l_bFilterCoefs = { 0.00000049535f,   0.00000297211f,   0.00000743028f,   0.00000990704f,   0.00000743028f,   0.00000297211f,   0.00000049535f};

    m_pFilter->setAFilterCoefficients(l_aFilterCoefs);
    m_pFilter->setBFilterCoefficients(l_bFilterCoefs);
}


SignalProcessing::~SignalProcessing()
{
    if (nullptr != m_pFilter)
    {
        delete m_pFilter;
        m_pFilter = nullptr;
    }
}

void SignalProcessing::setNbSignals(int nbSignal)
{
    m_i32NbSignals = nbSignal;
    m_vBufferedSignals.resize(m_i32NbSignals);
    m_vBufferedFilteredSignals.resize(m_i32NbSignals);
}

void SignalProcessing::setFps(float fFps)
{
    m_fFps = fFps;
}

void SignalProcessing::setSignalValues(float timestamp, std::vector<float> vInputData)
{
    std::vector<float> vOutputSignal;

    for (int l_signal=0; l_signal < vInputData.size(); l_signal++)
    {
        m_vBufferedSignals[l_signal].push_back(vInputData[l_signal]);
        if ( m_vBufferedSignals[l_signal].size() > m_i32FilterOrder + 1)
            m_vBufferedSignals[l_signal].pop_front();

        m_vBufferedFilteredSignals[l_signal].push_back(0.0);
        if (m_vBufferedFilteredSignals[l_signal].size() > m_i32FilterOrder + 1)
            m_vBufferedFilteredSignals[l_signal].pop_front();

        m_pFilter->filt(m_vBufferedSignals[l_signal], m_vBufferedFilteredSignals[l_signal]);
        vOutputSignal.push_back(m_vBufferedFilteredSignals[l_signal][m_vBufferedFilteredSignals[l_signal].size()-1]);
    }

    emit sigBroadcastFilteredSignalValues(vOutputSignal);
}
