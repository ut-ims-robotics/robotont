/*
* This node subscribes to the topic joy and converts joystick data to real SI velocity commands
* Velocity commands will be published on cmd_vel topic
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

#define JOY_TIMEOUT_SEC 0.5
#define MAX_TRANSLATION_SPEED 0.5
#define MAX_ROTATION_SPEED 1.57


class TeleopRobotontChina
{
public:
  TeleopRobotontChina();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void timerCallback(const ros::TimerEvent&);

  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  ros::Timer timer; 
  ros::Time last_joy_time;

};


TeleopRobotontChina::TeleopRobotontChina()
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobotontChina::joyCallback, this);
  timer = nh_.createTimer(ros::Duration(0.1), &TeleopRobotontChina::timerCallback, this);
  last_joy_time = ros::Time::now();
}

void TeleopRobotontChina::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  // check the deadman's switch
  if (!joy->buttons[9])
  {
    return; //We have a problem
  }

  last_joy_time = ros::Time::now();

  geometry_msgs::Twist twist;
  twist.linear.x = joy->axes[1]*MAX_TRANSLATION_SPEED;
  twist.linear.y = joy->axes[0]*MAX_TRANSLATION_SPEED;
  twist.angular.z = joy->axes[2]*MAX_ROTATION_SPEED;

  vel_pub_.publish(twist);
//  ROS_INFO_STREAM(twist);
}

void TeleopRobotontChina::timerCallback(const ros::TimerEvent&)
{
  if (ros::Time::now() - last_joy_time > ros::Duration(JOY_TIMEOUT_SEC))
  {
    geometry_msgs::Twist twist;
    twist.linear.x = 0;
    twist.linear.y = 0;
    twist.angular.z = 0;

    vel_pub_.publish(twist);
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "robotont_teleop_joy");
  TeleopRobotontChina robotont_teleop_joy;

  ros::spin();
}
