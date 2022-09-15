# 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"

// #include <QMC5883LCompass.h>
# 4 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 5 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 6 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 7 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 8 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2


const int motorA_dir1 = 6;
const int motorA_dir2 = 7;
const int motorB_dir1 = 9;
const int motorB_dir2 = 8;
const int motorA_en = 10;
const int motorB_en = 11;
void setup()
{

    pinMode(encoderA, 0x0);
    pinMode(encoderB, 0x0);
    pinMode(13, 0x1);
    attachInterrupt(((encoderA) == 2 ? 0 : ((encoderA) == 3 ? 1 : -1)), isrA, 3);
    attachInterrupt(((encoderB) == 2 ? 0 : ((encoderB) == 3 ? 1 : -1)), isrB, 3);
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




void test_go_distance(){

    PID_data pid_control_variables = {0.225f, 0.36f, 0.0f};
    MotorController motors = MotorController(motorA_dir1,
                                             motorA_dir2,
                                             motorB_dir1,
                                             motorB_dir2,
                                             motorA_en,
                                             motorB_en);
    MainController controller = MainController(&motors,pid_control_variables);
    while(1){
        wait_for_serial();
        controller.set_linear_distance(counterA,counterB,15.0f);
        uint64_t time = micros();
        float delta = 0.0f;
        while (1)
        {
            bool status = controller.go_linear_distance(counterA,counterB,speedA,speedB,delta);
            if(status){
                break;
            }
            Serial.print((int)counterA);
            Serial.print('\t');
            Serial.print((int)counterB);
            Serial.print('\t');
            Serial.print((int)controller.m_target_countA);
            Serial.print('\t');
            Serial.print((int)controller.m_target_countB);
            Serial.println();
            delta = float(micros() - time)/1.0e6f;
            time = micros();
        }

    }
}

void loop()
{

    test_go_distance();
}
