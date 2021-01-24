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
    if (analogRead(m_audioInputPin) > m_threashold)
    {
      m_timeBelowThreashold = 0;
      return true;
    }

    return m_timeBelowThreashold < max(m_minTailTime, analogRead(m_tailTimePotPin));
  }

private:
  const int m_minTailTime = 20;
  const int m_threashold = 700;

  int m_audioInputPin;
  int m_tailTimePotPin;
  elapsedMillis m_timeBelowThreashold = 1024;

};
