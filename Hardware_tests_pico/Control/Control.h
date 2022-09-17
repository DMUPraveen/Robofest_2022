#ifndef CONTROL_HEADER
#define CONTROL_HEADER
#include "PID.h"
#include "Motor_Controller.h"
#include "Odometry.h"

const float MICROS_TO_SECONDS = 1.0e6f;

struct Timer
{
    uint64_t m_time = 0;
    float delta = 0.0f;
    Timer()
    {
        m_time = micros();
    }

    float delta()
    {
        return delta;
    }

    void tick()
    {
        uint64_t nt = micros();
        delta = float(m_time - nt) / (MICROS_TO_SECONDS);
        m_time = nt;
    }
};

struct Basic_Speed_Control
{
    PID m_motor_A;
    PID m_motor_B;
    MotorController *m_motors;
    Basic_Speed_Control(PID_data control_variables, MotorController *motors)
        : m_motors(motors)
    {
        m_motor_A = PID(control_variables);
        m_motor_B = PID(control_variables);
    }

    void set_speed(float va, float vb)
    {
        m_motor_A.set_point(va);
        m_motor_B.set_point(vb);
    }
    void control(float speedA, float speedB, float dt)
    {
        m_motor_A.control(speedA, dt);
        m_motor_B.control(speedB, dt);
    }
};

struct Main_Control
{
    Basic_Speed_Control *m_basic_control;
    Robot_Pose *m_pose;
    Robot_Velocity* m_robot_velocity;
    float m_target_v = 0.0f;
    float m_target_omega = 0.0f;
    float m_target_sa = 0.0f;
    float m_target_sb = 0.0f;
    PID m_rotation;
    float m_target_angle = 0.0f;

    Main_Control(Basic_Speed_Control *basic_control, Robot_Pose *pose, PID_data rotation_data, Robot_Velocity* robot_velocity)
        : m_basic_control(basic_control), m_pose(pose), m_robot_velocity(robot_velocity)
    {

        m_rotation = PID(rotation_data);
        m_rotation.set_point(0.0f);
    }

    void set_target_angle(float target_angle)
    {
        m_target_angle = target_angle;
        m_rotation.clear();
        
    }

    void rotate_to_target_angle_on_spot(float dt){
        m_target_v = 0;
        float difference = normalize_angle_difference(m_target_angle-m_pose->m_theta);
        m_target_omega = m_rotation.control(difference,dt);

    }
    void stop()
    {
        m_target_sa = 0.0f;
        m_target_sb = 0.0f;
    }

    void control(float dt)
    {
        m_robot_velocity->get_iks(m_target_sa,m_target_sb,m_target_v,m_target_omega);
        m_basic_control->control(m_target_sa, m_target_sb, dt);
    }
};

#endif