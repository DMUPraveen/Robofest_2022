
#ifndef ODOMETRY_HEADER
#define ODOMETRY_HEADER

#include <QMC5883LCompass.h>

const float compass_filter_cof = 1.0f;
const float encoder_filter_cof = 0.0f;
const float imu_filter_cof = 0.0f;

float normalize_angle_difference(float angle_difference)
{
  // returns the difference in angle in the range of [-PI,PI]
  if (angle_difference < -M_PI)
  {
    return M_2_PI + angle_difference;
  }

  else if (angle_difference > M_PI)
  {
    return angle_difference - M_2_PI;
  }

  return angle_difference;
}

struct Compass_Angle
{
  float m_set_angle = 0.0f;
  QMC5883LCompass *m_compass;
  const int set_iterations = 100;
  Compass_Angle(QMC5883LCompass *compass)
  {
    m_compass = compass;
  }

  float _raw_angle()
  {
    return atan2(m_compass->getY(), m_compass->getX());
  }
  void init_angle()
  {
    float acc = 0.0f;
    for (int i = 0; i < set_iterations; i++)
    {
      m_compass->read();
      acc += _raw_angle();
    }
    m_set_angle = acc / set_iterations;
  }

  float cal_rotation()
  {
    m_compass->read();
    normalize_angle_difference(_raw_angle() - m_set_angle);
  }
};

struct Robot_Velocity
{
  float m_wheel_radius = 0.0f;
  float m_robot_diameter = 0.0f;

  float linear_velocity(float sa, float sb)
  {
    return (sa + sb) * m_wheel_radius / 2;
  }

  float angular_velocity(float sa, float sb)
  {
    return (sa - sb) * m_wheel_radius / m_robot_diameter;
  }

  void get_iks(float &sa, float &sb, float vl, float omega)
  {
    sa = 1 / m_wheel_radius * vl + m_robot_diameter / (2 * m_wheel_radius) * omega;
    sb = 1 / m_wheel_radius * vl - m_robot_diameter / (2 * m_wheel_radius) * omega;
  }
};

struct Robot_Pose
{
  float m_x = 0.0f;
  float m_y = 0.0f;
  float m_theta = 0.0f;
  uint64_t m_time = 0;
  Robot_Velocity *m_robot_velocity;
  Compass_Angle *m_compass;
  float m_omega = 0.0f;
  float m_velocity = 0.0f;
  float m_dt = 0.0f;
  Robot_Pose(Robot_Velocity *robot_velocity, Compass_Angle *compass)
      : m_robot_velocity(robot_velocity), m_compass(compass)
  {
  }

  void set_pose(float x, float y, float theta)
  {
    m_x = x;
    m_y = y;
    m_theta = theta;
  }

  void update_dynamics(float sa, float sb)
  {
    uint64_t new_time = micros();
    m_dt = float(new_time - m_time) / 1.0e6f;
    m_velocity = m_robot_velocity->linear_velocity(sa, sb);
    m_omega = m_robot_velocity->angular_velocity(sa, sb);
  }

  void update_pose()
  {
    float theta_compass = m_compass->cal_rotation();
    float theta_encoders = m_omega * m_dt + m_theta;

    // if necessary code for updateing theta using gyro values can be added here
    m_theta = theta_compass * compass_filter_cof + theta_encoders * encoder_filter_cof;
    // code to update x and y positions go here

    //
  }
};

#endif
