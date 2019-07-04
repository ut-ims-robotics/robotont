#include <ros/ros.h>
#include <serial/serial.h>
#include "robotont_driver/odom.h"

namespace robotont
{
class RobotontHW
{
public:
  RobotontHW();
  ~RobotontHW();

private:
  void connect();
  void read(const ros::TimerEvent& event);
  void processPacket();
  void write(const std::string& packet);
  void writeRobotSpeed(float lin_vel_x, float lin_vel_y, float ang_vel_z);
  void writeMotorSpeed(float speed_m1, float speed_m2, float speed_m3);
  void cmd_vel_callback(const geometry_msgs::Twist& cmd_vel_msg);

  Odom odom_;
  serial::Serial serial_;
  std::string packet_;

  ros::NodeHandle nh_;
  ros::Timer timer_;
  ros::Subscriber cmd_vel_sub_;
};
}
