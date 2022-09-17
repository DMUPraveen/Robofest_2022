#include "Odometry.h"
#include "Wire.h"

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
