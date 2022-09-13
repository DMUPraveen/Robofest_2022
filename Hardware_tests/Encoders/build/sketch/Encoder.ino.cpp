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
#line 68 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void wait_for_serial();
#line 81 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void set_pid_data(PID& pid,Data& my_data);
#line 88 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void set_data(Data& my_data);
#line 122 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void Test_PID();
#line 162 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
void setup();
#line 172 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\Encoder.ino"
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
struct Data{
    float Kp = 0.0f;
    float Ki = 0.0f;
    float Kd = 0.0f;
    float set_point = 0.0f;
};

auto my_data = Data();


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

void set_pid_data(PID& pid,Data& my_data){
    pid.m_K_P = my_data.Kp;
    pid.m_K_D = my_data.Kd;
    pid.m_K_I = my_data.Ki;
    pid.m_set_point = my_data.set_point;
}

void set_data(Data& my_data){
    while(!Serial.available()){

    }
    digitalWrite(LED_BUILTIN,1);
    float buffer[4] = {0};
    Serial.readBytes((uint8_t*)buffer,4*4);
    my_data.Kp = buffer[0];
    my_data.Ki = buffer[1];
    my_data.Kd = buffer[2];
    my_data.set_point = buffer[3];
    Serial.print("Kp: ");
    Serial.print(my_data.Kp);
    Serial.print(",");
    Serial.print("Ki: ");
    Serial.print(my_data.Ki);
    Serial.print(",");
    Serial.print("Kd: ");
    Serial.print(my_data.Kd);
    Serial.print(",");
    Serial.print("set_point: ");
    Serial.print(my_data.set_point);
    Serial.println();

    if(Serial.available()){ //clean up
        while (Serial.available())
        {
            Serial.read();
        }
        
    }
}


void Test_PID(){

    controllerA.set_point(1);
    controllerB.set_point(1);

    wait_for_serial();
    while(1){
        bool stop = false;

        while(Serial.available()){
            Serial.read();
            motors.Brake_A();
            motors.Brake_B();
            stop = true; 
        }

        if(stop) break;

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
}

void setup()
{
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA),isrA,RISING);
    attachInterrupt(digitalPinToInterrupt(encoderB),isrB,RISING);
    Serial.begin(9600);
    wait_for_serial();
}

void loop()
{


    
}

