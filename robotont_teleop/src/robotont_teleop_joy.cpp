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

  double speed = 0.5; // speed multiplier that can be increased/decreased using buttons A and B

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
  // Increase decrease max speed
  if (joy->buttons[0])
  {
    speed-=0.1;
    speed = std::max(speed,0.1);
    ros::Duration(0.5).sleep();
  }
  if (joy->buttons[1])
  {
    speed+=0.1;
    speed = std::min(speed,1.0);
    ros::Duration(0.5).sleep();
  }

  // check the deadman's switch
  if (joy->axes[4] >= 0)
  {
    return; //We have a problem
  }

  last_joy_time = ros::Time::now();

  geometry_msgs::Twist twist;
  twist.linear.x = joy->axes[1]*speed*MAX_TRANSLATION_SPEED;
  twist.linear.y = joy->axes[0]*speed*MAX_TRANSLATION_SPEED;
  twist.angular.z = joy->axes[2]*speed*MAX_ROTATION_SPEED;

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
