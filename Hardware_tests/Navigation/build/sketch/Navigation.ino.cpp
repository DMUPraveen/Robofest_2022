#include <Arduino.h>
#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
#include "Communication.h"
#include "SpeedCal.h"
#include "PID.h"
#include "Motor_Controller.h"

const int motorA_dir1 = 6;
const int motorA_dir2 = 7;
const int motorB_dir1 = 9;
const int motorB_dir2 = 8;
const int motorA_en = 10;
const int motorB_en = 11;
#line 12 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
void setup();
#line 24 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
void set_pid_data(PID& pid,Data& my_data);
#line 30 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
void Test_PID();
#line 107 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
void loop();
#line 12 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
void setup()
{

    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA),isrA,RISING);
    attachInterrupt(digitalPinToInterrupt(encoderB),isrB,RISING);
    Serial.begin(9600);
    
}

void set_pid_data(PID& pid,Data& my_data){
    pid.m_K_P = my_data.Kp;
    pid.m_K_D = my_data.Kd;
    pid.m_K_I = my_data.Ki;
    pid.m_set_point = my_data.set_point;
}
void Test_PID(){


    auto controllerA = PID(1,0,0);
    auto controllerB = PID(1,0,0);
    auto sca = Speed_Cal(0.0,20);
    auto scb = Speed_Cal(0.0,20);

    auto motors = MotorController(motorA_dir1,
                            motorA_dir2,
                            motorB_dir1,
                            motorB_dir2,
                            motorA_en,
                            motorB_en);

    Data my_data = get_serial_data();
    digitalWrite(LED_BUILTIN,HIGH);
    set_pid_data(controllerA,my_data);
    set_pid_data(controllerB,my_data);
    wait_for_serial();
    digitalWrite(LED_BUILTIN,LOW);
    uint64_t time = micros();
    uint64_t delta = 0;
    while(1){
        // motors.control(1.0,1.0);
        // continue;
        
        bool stop = false;

        while(Serial.available()){
            Serial.read();
            motors.Brake_A();
            motors.Brake_B();
            stop = true; 
        }

        if(stop) break;

        // float sa =sca.calculate(counterA) ;
        // float sb  = scb.calculate(counterB);
        float ca = controllerA.control(speedA,delta/1e6);
        float cb = controllerB.control(speedB,delta/1e6);
        motors.control(
            ca > 0 ?ca:0,
            cb > 0 ?cb:0
        ); 
        // motors.control(0.2,0.0);
        // motors.control(0,0);
        // Serial.print(delta);
        // Serial.print('\t');
        // Serial.print(sb);
        // Serial.print('\t');
        Serial.print(speedA);
        Serial.print('\t');
        Serial.print(speedB);
        Serial.print('\t');
        Serial.print(ca);
        Serial.print('\t');
        Serial.print(cb);
        // Serial.print((int)counterA);
        Serial.println();
        // Serial.print(digitalRead(2));
        // Serial.print('\t');
        // Serial.print('\t');
        // Serial.print(delta_t,6);
        // Serial.print('\t');
        // Serial.print(pinstate);
        // Serial.println();
        // show = false;
            

        delta = micros() - time;
        time = micros();
    }
}


void loop()
{
	
}

