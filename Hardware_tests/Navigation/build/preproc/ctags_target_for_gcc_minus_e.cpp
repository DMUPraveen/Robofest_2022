# 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino"
# 2 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 3 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 4 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2
# 5 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Navigation.ino" 2

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
    pinMode(13,0x1);
    attachInterrupt(((encoderA) == 2 ? 0 : ((encoderA) == 3 ? 1 : -1)),isrA,3);
    attachInterrupt(((encoderB) == 2 ? 0 : ((encoderB) == 3 ? 1 : -1)),isrB,3);
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
    digitalWrite(13,0x1);
    set_pid_data(controllerA,my_data);
    set_pid_data(controllerB,my_data);
    wait_for_serial();
    digitalWrite(13,0x0);
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
