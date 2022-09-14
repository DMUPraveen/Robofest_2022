#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Main_Controller.h"
#ifndef MAIN_CONTROLLER_HEADER
#define MAIN_CONTROLLER_HEADER

#include "Motor_Controller.h"
#include "PID.h"

struct MainController
{
    MotorController *m_motors;
    PID m_motor_A;
    PID m_motor_B;
    float m_motor_speed_A =0.0f;
    float m_motor_speed_B = 0.0f;
    MainController(MotorController *motors,PID_data motor_pid_data)
        :m_motors(motors), m_motor_A(PID(motor_pid_data)), m_motor_B(PID(motor_pid_data))
    {

    }

    void set_motor_speed(float motor_speed_A,float motor_speed_B){
        m_motor_speed_A = motor_speed_A;
        m_motor_speed_B = motor_speed_B;
        m_motor_A.set_point(abs(m_motor_speed_A));
        m_motor_B.set_point(abs(m_motor_speed_A));
    }

    void control_speed(float current_speed_A,float current_speed_B,float delta){
        // Serial.println(delta);
        float ca = m_motor_A.control(current_speed_A,delta); 
        float cb = m_motor_B.control(current_speed_B,delta);
        ca = ca >0?ca:0;
        cb = cb >0?cb:0;
    
        ca = m_motor_speed_A >0 ? ca:-ca;
        cb = m_motor_speed_B >0 ? cb:-cb;
        Serial.print("ca: ");
        Serial.print(ca);
        Serial.print(",");
        Serial.print("cb: ");
        Serial.print(cb);
        Serial.print(",");
        m_motors->control(ca,cb);

        

    }
};

#endif