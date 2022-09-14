#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Navigation\\Communication.h"
#ifndef COMMUNICATION_HEADER
#define COMMUNICATION_HEADER

struct Data{
        float Kp = 0.0f;
        float Ki = 0.0f;
        float Kd = 0.0f;
        float set_point = 0.0f;
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

Data get_serial_data(){
    Data my_data = Data();
    while(!Serial.available()){

    }
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
    return my_data;
}


#endif