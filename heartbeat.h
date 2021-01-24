#pragma once

class HeartBeat
{
public:
  HeartBeat(int hbInPin)
  : m_hbInPin(hbInPin)
  {}

  bool isBeating()
  {
    if (analogRead(m_hbInPin) < 500)
    {
      m_timeSinceHbWasLow = 0;
    }
    else
    {
      m_timeSinceHbWasHigh = 0;
    }

    return  m_timeSinceHbWasLow < m_timeoutMs && m_timeSinceHbWasHigh < m_timeoutMs;
  }
  
private:
  const int m_timeoutMs = 1000;
  
  int m_hbInPin; 
  elapsedMillis m_timeSinceHbWasLow = 0;
  elapsedMillis m_timeSinceHbWasHigh = 0;
};
