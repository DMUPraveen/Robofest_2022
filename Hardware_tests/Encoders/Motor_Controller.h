
#ifndef MOTOR_CONTROLLER
#define MOTOR_CONTROLLER
#define ANALOG_OUTPUT_SCALE 255

void clamp(float& val,float c){
    if(val < -c){
        val = -c;
    }
    if(val > c){
        val = c;
    }
}

struct MotorController
{

    uint8_t ma_in1 = 2;
    uint8_t ma_in2 = 3;
    uint8_t mb_in1 = 4;
    uint8_t mb_in2 = 5;
    uint8_t ena = 9;
    uint8_t enb = 10;

    MotorController(uint8_t ma_in1, uint8_t ma_in2, uint8_t mb_in1, uint8_t mb_in2, uint8_t ena,uint8_t enb)
        :ma_in1(ma_in1),ma_in2(ma_in2),mb_in1(mb_in1),mb_in2(mb_in2),ena(ena),enb(enb)
    {
        pinMode(ma_in1,OUTPUT);
        pinMode(ma_in2,OUTPUT);
        pinMode(mb_in1,OUTPUT);
        pinMode(ma_in2,OUTPUT);

        pinMode(ena,OUTPUT);
        pinMode(enb,OUTPUT);
    }

    void Brake_A(){
        pinMode(ma_in1,LOW);
        pinMode(ma_in2,LOW);
    }

    void Brake_B(){
        pinMode(mb_in1,LOW);
        pinMode(mb_in2,LOW);
    }

    void control(float ma_v, float mb_v){
        /*
        ma_v : velocity of motor A normalized (between -1 and 1)
        mb_v : velocity of motor B normalized (between -1 and 1)
        
        */
        clamp(ma_v,1);
        clamp(mb_v,1);
         
        analogWrite(ena,abs(ma_v)*ANALOG_OUTPUT_SCALE);
        analogWrite(enb,abs(mb_v)*ANALOG_OUTPUT_SCALE);
        if(ma_v >= 0){
            digitalWrite(ma_in1,HIGH);
            digitalWrite(ma_in2,LOW);
        }
        else{
            digitalWrite(ma_in1,LOW);
            digitalWrite(ma_in2,HIGH);
        }

        if(mb_v >=0){
            digitalWrite(mb_in1,HIGH);
            digitalWrite(mb_in2,LOW);
        }
        else{
            digitalWrite(mb_in1,LOW);
            digitalWrite(mb_in2,HIGH);
        }   


        

    }
};



void check_motors(MotorController& motors,uint32_t dtime){
    motors.control(1,1);
}
#endif