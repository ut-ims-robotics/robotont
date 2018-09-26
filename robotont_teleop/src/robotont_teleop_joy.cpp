/*
* This node subscribes to the topic joy and converts joystick data to real SI velocity commands
* Velocity commands will be published on cmd_vel topic
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

#define JOY_TIMEOUT_SEC 0.5


class TeleopRobotont
{
public:
  TeleopRobotont();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void timerCallback(const ros::TimerEvent&);

  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  ros::Timer timer; 
  ros::Time last_joy_time;

};


TeleopRobotont::TeleopRobotont()
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobotont::joyCallback, this);
  timer = nh_.createTimer(ros::Duration(0.1), &TeleopRobotont::timerCallback, this);
  last_joy_time = ros::Time::now();
}

void TeleopRobotont::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  // check the deadman's switch
  if (!joy->buttons[5])
  {
    return; //We have a problem
  }

  last_joy_time = ros::Time::now();

  geometry_msgs::Twist twist;
  twist.linear.x = joy->axes[1];
  twist.linear.y = joy->axes[0];
  twist.angular.z = joy->axes[3];

  vel_pub_.publish(twist);
  ROS_INFO_STREAM(twist);
}

void TeleopRobotont::timerCallback(const ros::TimerEvent&)
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
  TeleopRobotont robotont_teleop_joy;

  ros::spin();
}
