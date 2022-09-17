struct Data{
    float Kp = 0.0f;
    float Ki = 0.0f;
    float Kd = 0.0f;
    float set_point = 0.0f;
};

auto my_data = Data();
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,0);
	
}

void loop()
{
    
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
