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
    // Sample the audio level. Each time a reading is outside the quiet band, reset the timer.
    // When there has been enough time with no readings outside the quiet band, then audio 
    // has stopped.
    
    const auto level = analogRead(m_audioInputPin);
    if (level > m_quietBandUpperLimit || level < m_quietBandLowerLimit)
    {
      m_timeInQuietBand = 0;
      return true;
    }

    return m_timeInQuietBand < max(m_minTailTimeMs, analogRead(m_tailTimePotPin));
  }

private:
  const int m_audioInputPin;
  const int m_tailTimePotPin;

  const int m_minTailTimeMs = 40;

  // When no audio is present, the analog readings are within this band on my hardware:
  const int m_quietBandLowerLimit = 350;
  const int m_quietBandUpperLimit = 580;
  
  elapsedMillis m_timeInQuietBand = 1024;
};
