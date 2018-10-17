/* 
* This node communicates with Robotont hardware, subscribes to /cmd_vel and publishes /odom
*/
#include <ros/ros.h>
#include "robotont_driver/robotont_hardware.h"

using namespace robotont;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "driver_node");
  ros::NodeHandle nh;

  RobotontHW hw;

  ros::spin();
}
