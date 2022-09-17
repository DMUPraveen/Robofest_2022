#include "SpeedCal.h"
void setup()

{
    attachInterrupt(digitalPinToInterrupt(encoderA),isrA,RISING);
    pinMode(encoderA_dir,INPUT);
    Serial.begin(9600);

	
}

void loop()
{
    Serial.println((int)counterA);
    delay(10);
	
}
