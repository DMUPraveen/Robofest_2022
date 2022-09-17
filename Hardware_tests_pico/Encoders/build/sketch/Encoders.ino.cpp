#include <Arduino.h>
#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino"
#include "SpeedCal.h"
#line 2 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino"
void setup();
#line 12 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino"
void loop();
#line 2 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino"
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

