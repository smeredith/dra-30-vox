#pragma once

#include <elapsedMillis.h>
#include <limits.h>

class VOX
{
public:
  VOX(int audioInputPin, int tailTimePotPin)
  : m_audioInputPin(audioInputPin)
  , m_tailTimePotPin(tailTimePotPin)
  {
  }
  
  bool audioIsDetected()
  {
    const auto level = analogRead(m_audioInputPin);
    if (level > m_upperLimit || level < m_lowerLimit)
    {
      m_timeBelowThreashold = 0;
      return true;
    }

    return m_timeBelowThreashold < max(m_minTailTime, analogRead(m_tailTimePotPin));
  }

private:
  const int m_minTailTime = 40;
  const int m_upperLimit = 600;
  const int m_lowerLimit = 350;

  int m_audioInputPin;
  int m_tailTimePotPin;
  elapsedMillis m_timeBelowThreashold = 1024;
};
