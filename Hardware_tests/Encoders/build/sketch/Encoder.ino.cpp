#include <Arduino.h>
#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
#include "Motor_Controller.h"
#include <util/atomic.h> 
#include "PID.h"



const int encoderA = 2;
const int encoderB = 3;


const int motorA_dir1 = 6;
const int motorA_dir2 = 7;
const int motorB_dir1 = 9;
const int motorB_dir2 = 8;
const int motorA_en = 10;
const int motorB_en = 11;


const float filter_factor = 0.05;
const float noise_reject = 0.1f;

volatile uint64_t counterA = 0;
volatile float pre_timeA = 0.0f;
volatile float speedA = 0.0f;

#line 26 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void isrA();
#line 39 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void isrB();
#line 91 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void wait_for_serial();
#line 104 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void setup();
#line 120 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void loop();
#line 26 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void isrA(){
    long ct = micros();
    float dt = (ct - pre_timeA)/(1.0e6);
    if(dt <noise_reject) return;
    counterA++;
    speedA = (PI/10)/dt;
    pre_timeA = ct;
}

volatile uint64_t counterB = 0;
volatile float pre_timeB = 0.0f;
volatile float speedB = 0.0f;

void isrB(){
    long ct = micros();
    float dt = (ct - pre_timeB)/(1.0e6);
    if(dt <noise_reject) return;
    counterB++;
    speedB = PI/10/dt;
    pre_timeB = ct;
}


auto motors = MotorController(motorA_dir1,
                         motorA_dir2,
                         motorB_dir1,
                         motorB_dir2,
                         motorA_en,
                         motorB_en);

auto controllerA = PID(1,0,0);
auto controllerB = PID(1,0,0);



struct Speed_Cal
{
    uint64_t pre_count=0;
    uint64_t time;
    uint64_t divs;
    float speed;
    Speed_Cal(uint64_t time,uint64_t divisions)
    :time(time) , divs(divisions)
    {
        speed = 0.0f;
    }
    float calculate(uint64_t count){
        int divisions = count - pre_count;
        float  dt = float(micros()-time)/(1.0e6f);
        // Serial.println(dt);
        if(divisions == 0){
            float anlge = (1.0f/float(divs))*2*PI;
            float ss = anlge/dt;
            if(ss < speed) return ss;
            return speed;
        }
        float angle =   (float(divisions)/float(divs))*2*PI ;
        pre_count = count;
        time = micros();
        speed = angle/dt;
        return speed;


    }
};
void wait_for_serial(){
    while (!Serial.available())
    {
        /* code */
    }
    while(Serial.available()){
        Serial.read();
    }

}
auto sca = Speed_Cal(0.0,20);
auto scb = Speed_Cal(0.0,20);

void setup()
{
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA),isrA,RISING);
    attachInterrupt(digitalPinToInterrupt(encoderB),isrB,RISING);

    controllerA.set_point(1);
    controllerB.set_point(1);

    Serial.begin(9600);
    wait_for_serial();
    
    
}

void loop()
{

    bool stopped = false;
    while(Serial.available()){
        Serial.read();
        motors.Brake_A();
        motors.Brake_B();
        stopped = true;
    }
    if(stopped){
        wait_for_serial();
        stopped = false;
    }
    motors.control(1.0,1.0);
    return;

    float sa =sca.calculate(counterA) ;
    float sb  = scb.calculate(counterB);
    float ca = controllerA.control(sa);
    float cb = controllerB.control(sb);
    motors.control(
        ca > 0 ?ca:0,
        cb > 0 ?cb:0
    ); 
    Serial.print(sa);
    Serial.print('\t');
    Serial.print(sb);
    Serial.print('\t');
    Serial.print(ca);
    Serial.print('\t');
    Serial.print(cb);
    Serial.println();

    
}

