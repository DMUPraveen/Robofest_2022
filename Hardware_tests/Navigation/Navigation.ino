
// #include <QMC5883LCompass.h>
#include "Communication.h"
#include "SpeedCal.h"
#include "PID.h"
#include "Motor_Controller.h"
#include "Main_Controller.h"


const int motorA_dir1 = 6;
const int motorA_dir2 = 7;
const int motorB_dir1 = 9;
const int motorB_dir2 = 8;
const int motorA_en = 10;
const int motorB_en = 11;
void setup()
{

    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA), isrA, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderB), isrB, RISING);
    Serial.begin(9600);
}

void test_main_controoler_linear()
{
    PID_data pid_control_variables = {0.225f, 0.36f, 0.0f};
    MotorController motors = MotorController(motorA_dir1,
                                             motorA_dir2,
                                             motorB_dir1,
                                             motorB_dir2,
                                             motorA_en,
                                             motorB_en);
    MainController controller = MainController(&motors,pid_control_variables);
    controller.set_motor_speed(15.0f,-15.0f);

    while(1){
        wait_for_serial();
        uint64_t time = micros();
        float delta = 0.0f;
        while (1)
        {
            controller.control_speed(speedA,speedB,delta);
            if(Serial.available()){
                wait_for_serial();
                motors.Brake_A();
                motors.Brake_B();
                motors.control(0.0f,0.0f);
                break;
            }
            Serial.print("SpeedA: ");
            Serial.print(speedA);
            Serial.print(',');
            Serial.print("SpeedB: ");
            Serial.print(speedB);
            Serial.println();

            delta = float(micros() - time)/1.0e6f;
            time = micros();
            
        }
        
    }
}

void loop()
{
    
    test_main_controoler_linear();
}
