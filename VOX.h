#pragma once

#include <elapsedMillis.h>

class VOX
{
public:
  VOX(int audioInputPin, int tailTimePotPin)
  : m_audioInputPin(audioInputPin)
  , m_tailTimePotPin(tailTimePotPin)
  {
  }

  // Sample the audio level. Each time a sample is outside the quiet band, reset the timer.
  // When there has been enough time with no samples outside the quiet band, then audio 
  // has stopped.
  //
  // "Enough time" is determined by the larger of m_minTailTimeMs and the value read
  // from the "tail time" trim pot. m_minTailTimeMs was determined experimentally to
  // be the shortest reliable time to notice samples outside the quiet band if they
  // exist.
  bool audioIsDetected()
  {
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
