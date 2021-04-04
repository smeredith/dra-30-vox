#pragma once

// Controls  the PTT output.
// If on longer than the maximim, turns off.
// Enforces a minimum on time.
class PTT
{
public:
  PTT(int pttPin)
  : m_pttPin(pttPin)
  {
    pinMode(m_pttPin, OUTPUT);

    digitalWrite(m_pttPin, LOW);
  }

  void press()
  {
    if (m_releaseElapsedMs < m_minReleaseTimeMs)
      return;

    if (!m_pressed)
    {
      m_pressElapsedMs = 0;
      m_pressed = true;
      digitalWrite(m_pttPin, HIGH);    
    }

    if (!m_timeOut)
    {
      if (m_pressElapsedMs > m_maxPressTimeMs)
      {
        digitalWrite(m_pttPin, LOW);
        m_timeOut = true;      
      }
    }
  }

  void release()
  {
    if (m_pressElapsedMs < m_minPressTimeMs)
        return;

    if (m_pressed)
    {
      digitalWrite(m_pttPin, LOW);
      m_pressed = false;
      m_timeOut = false;
      m_releaseElapsedMs = 0;
    }
  }
  
private:
  const int m_pttPin;
  const unsigned long m_maxPressTimeMs = 300000;
  const unsigned long m_minPressTimeMs = 100;
  const unsigned long m_minReleaseTimeMs = 100;
  bool m_pressed = false;
  bool m_timeOut = false;
  elapsedMillis m_pressElapsedMs;
  elapsedMillis m_releaseElapsedMs;
};
