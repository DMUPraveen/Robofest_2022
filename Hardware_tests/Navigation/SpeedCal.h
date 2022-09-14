#ifndef SPEEDCAL_HEADER
#define SPEEDCAL_HEADER
const int encoderA = 2;
const int encoderB = 3;




const float filter_factor = 0.05;
const float noise_reject = 0.001f;

volatile uint64_t counterA = 0;
volatile float pre_timeA = 0.0f;
volatile float speedA = 0.0f;
// volatile bool show = false;
// volatile float delta_t=0.0f ;
// volatile uint8_t pinstate = 0;

void isrA(){
    long ct = micros();
    float dt = float(ct - pre_timeA)/float(1.0e6);

    if(dt < noise_reject || digitalRead(encoderA)==0) return;
    counterA++;
    // pinstate = digitalRead(encoderA);
    
    speedA = (PI/10)/dt;
    pre_timeA = ct;
    // show = true;
    // delta_t = dt;
}

volatile uint64_t counterB = 0;
volatile float pre_timeB = 0.0f;
volatile float speedB = 0.0f;

void isrB(){
    long ct = micros();
    float dt = (ct - pre_timeB)/(1.0e6);
    if(dt <noise_reject || digitalRead(encoderB)==0) return;
    counterB++;
    speedB = PI/10/dt;
    pre_timeB = ct;
}
#endif