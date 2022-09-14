#ifdef ODOMETRY_HEADER
#define ODOMETRY_HEADER

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

};



#endif
