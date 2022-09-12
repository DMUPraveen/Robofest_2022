#line 1 "c:\\Users\\dell\\Desktop\\Projects\\Robofest\\Dev\\Hardware_tests\\Encoders\\PID.h"
#ifndef PID_HEADER
#define PID_HEADER

struct PID
{

    float m_set_point = 0.0f;
    float m_K_P = 0.0f;
    float m_K_D = 0.0f;
    float m_K_I = 0.0f;


    PID(float K_P, float K_D, float K_I)
        : m_K_P(K_P), m_K_D(K_D), m_K_I(K_I)
    {
    }

    void set_point(float set_point){
        m_set_point = set_point;
    }

    float control(float measurement){
        return m_K_P*(m_set_point - measurement);
    }
};
#endif