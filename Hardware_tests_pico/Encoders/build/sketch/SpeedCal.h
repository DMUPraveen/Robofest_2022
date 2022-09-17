#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\SpeedCal.h"
#ifndef SPEEDCAL_HEADER
#define SPEEDCAL_HEADER
const int encoderA = 6;
const int encoderA_dir = 7;
const int encoderB = 8;
const int encoderB_dir = 9;

const float filter_factor = 0.05;
const float noise_reject = 0.001f;
const float step_angle = 1.0f;

volatile int64_t counterA = 0;
volatile float pre_timeA = 0.0f;
volatile float speedA = 0.0f;

void isrA()
{
    long ct = micros();
    float dt = float(ct - pre_timeA) / float(1.0e6);

    if (dt < noise_reject || digitalRead(encoderA) == 0)
        return;
    if (digitalRead(encoderA_dir) == 1)
    {
        counterA++;
        speedA = step_angle / dt;
    }
    else{
        counterA--;
        speedA = -step_angle / dt;
    }

    pre_timeA = ct;
}

volatile int64_t counterB = 0;
volatile float pre_timeB = 0.0f;
volatile float speedB = 0.0f;

void isrB()
{
    long ct = micros();
    float dt = (ct - pre_timeB) / (1.0e6);
    if (dt < noise_reject || digitalRead(encoderB) == 0)
        return;
    if (digitalRead(encoderB_dir) == 1)
    {
        counterB++;
        speedB = step_angle / dt;
    }
    else{
        counterB--;
        speedB = -step_angle / dt;
    }

    pre_timeB = ct;
}
#endif