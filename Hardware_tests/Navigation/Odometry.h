
#ifndef ODOMETRY_HEADER
#define ODOMETRY_HEADER

#include <QMC5883LCompass.h>


struct Odometry_Angle
{
    float set_angle;
    QMC5883LCompass* m_compass;
    Odometry_Angle(QMC5883LCompass* compass)
    {
        m_compass = compass;

    }

    void init_angle()
    {
        m_compass->read();

        set_angle = m_compass->getAzimuth();
        for( int i = 0 ; i < 100 ; i++)
        {
          m_compass->read();
          set_angle = 0.9 * set_angle + 0.1*m_compass->getAzimuth();
        }
        
    }

    float cal_rotation( )
    {
        m_compass->read();
//        Serial.println(m_compass->getAzimuth());

        float rotation = m_compass->getAzimuth() - set_angle;

        if( rotation < 0)
        { 
          return ( rotation + 360 );
        }
        else
        {
          return rotation;
        }
        //return ( m_compass->getAzimuth() - set_angle );
    }

    float target_difference( float target_angle ){
      
      float current_angle = cal_rotation() ;

      float difference = abs( target_angle - current_angle );

      if( difference <= 180 ){
        if target_angle >= current_angle{
          return difference;
        }
        else{
          return -difference;
        }
      }
      else{
        if( target_angle > current_angle){
            return ( difference-360);
        }

        else{
            return ( -difference + 360 );
        }

      }
    

    }



};



#endif
