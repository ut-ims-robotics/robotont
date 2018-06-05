/*
* This node subscribes to the topic joy and converts joystick data to real SI velocity commands
* Velocity commands will be published on cmd_vel topic
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class TeleopRobotont
{
public:
  TeleopRobotont();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


TeleopRobotont::TeleopRobotont()
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobotont::joyCallback, this);
}

void TeleopRobotont::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.linear.x = joy->axes[1];
  twist.linear.y = joy->axes[0];
  twist.angular.z = joy->axes[3];

  vel_pub_.publish(twist);
  ROS_INFO_STREAM(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "robotont_teleop_joy");
  TeleopRobotont robotont_teleop_joy;

  ros::spin();
}
