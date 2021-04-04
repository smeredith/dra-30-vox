#include <elapsedMillis.h>
#include "PTT.h"
#include "VOX.h"

const int hbOkOutPin = PB0;
const int pttPin = PB1;
const int hbInPin = PB4;
const int audioInPin = A3;
const int tailTimePotPin = A1;

VOX vox(audioInPin, tailTimePotPin);
PTT ptt(pttPin);

void setup()
{
  pinMode(hbOkOutPin, OUTPUT);
  digitalWrite(hbOkOutPin, LOW);
  analogReference(INTERNAL);

  cli();
  PCMSK |= (1 << PCINT4); // Enable ISR for PB4
  GIMSK |= (1 << PCIE); // Enable PCINT interrupt in the general interrupt mask
  pinMode(hbInPin, INPUT_PULLUP);
  sei();
}

volatile unsigned long lastHeartBeatTime = 0;

ISR(PCINT0_vect)
{
  lastHeartBeatTime = millis();
}

void loop()
{
  const bool commOk = millis() - lastHeartBeatTime < 1000UL;
  digitalWrite(hbOkOutPin, commOk?HIGH:LOW);
  
  if (commOk && vox.audioIsDetected())
  {
    ptt.press();
  }
  else
  {
    ptt.release();
  }
}
