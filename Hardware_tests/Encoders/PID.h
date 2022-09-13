#ifndef PID_HEADER
#define PID_HEADER

struct PID
{

    float m_set_point = 0.0f;
    float m_K_P = 0.0f;
    float m_K_D = 0.0f;
    float m_K_I = 0.0f;
    float I_error = 0.0f;


    PID(float K_P, float K_D, float K_I)
        : m_K_P(K_P), m_K_D(K_D), m_K_I(K_I)
    {
    }

    void set_point(float set_point){
        m_set_point = set_point;
    }

    float control(float measurement){

        float error = m_set_point - measurement;

        float signal = m_K_P * error + m_K_I * I_error;

        if ( (signal > 1 && error > 0) || ( signal < -1 && error < 0 ))
        {  }

        else
        { I_error = I_error + error}
        
        return signal;
        
    }
};
#endif