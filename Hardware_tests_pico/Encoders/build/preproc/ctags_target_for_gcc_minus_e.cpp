# 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino"
# 2 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Encoders\\Encoders.ino" 2
void setup()

{
    attachInterrupt((encoderA),isrA,RISING);
    pinMode(encoderA_dir,INPUT);
    Serial.begin(9600);


}

void loop()
{
    Serial.println((int)counterA);
    delay(10);

}
