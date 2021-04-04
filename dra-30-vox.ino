#include <elapsedMillis.h>
#include "PTT.h"
#include "VOX.h"
#include "heartbeat.h"

const int hbOkOutPin = PB0;
const int pttPin = PB1;
const int hbInPin = A2;
const int audioInPin = A3;
const int tailTimePotPin = A1;

VOX vox(audioInPin, tailTimePotPin);
PTT ptt(pttPin);
HeartBeat heart(hbInPin);

void setup()
{
  pinMode(hbOkOutPin, OUTPUT);

  digitalWrite(hbOkOutPin, HIGH);

  analogReference(INTERNAL);
}

void loop()
{
  const bool commOk = heart.isBeating();
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
