#include <Arduino.h>
#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Magentic_Sensor\\Magnetic_Sensor.ino"
#include "Odometry.h"
#include "Wire.h"

#line 4 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Magentic_Sensor\\Magnetic_Sensor.ino"
void test_magentic_sensor();
#line 18 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Magentic_Sensor\\Magnetic_Sensor.ino"
void setup();
#line 25 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Magentic_Sensor\\Magnetic_Sensor.ino"
void loop();
#line 4 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests_pico\\Magentic_Sensor\\Magnetic_Sensor.ino"
void test_magentic_sensor(){
    QMC5883LCompass compass;
    compass.init();
    auto magnetic_angle = Odometry_Angle(&compass);
    magnetic_angle.init_angle();
    while (1)
    {
        float val = magnetic_angle.cal_rotation();
        Serial.println(val);
        delay(100);
    }
    
}

void setup()
{
    Wire.setSDA(4);
    Wire.setSCL(5);
    Serial.begin(9600);
}

void loop()
{
    test_magentic_sensor();
	
}

