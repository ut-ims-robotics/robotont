/*
* This node listens to teleop (cmd_vel), then formats the command accordingly
* and publishes the formatted string to Gazebo JointVelocityControllers
*/
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <cmath>
#include <string>

// initial list for the angles of the wheels
std::vector<float> wheelAngles;

ros::Publisher v_leftCommand;
ros::Publisher v_backCommand;
ros::Publisher v_rightCommand;

std_msgs::Float64 value;

//Calculate and publish 3 wheel omnirobot wheel speeds
void format_cmd(const geometry_msgs::Twist &cmd_vel_msg)
{
  float m0 = 0;
  float m1 = 0;
  float m2 = 0;

  float vel_x = cmd_vel_msg.linear.x;
  float vel_y = cmd_vel_msg.linear.y;
  float robotAngularVelocity = cmd_vel_msg.angular.z;

  float robotSpeed = 0;

  robotSpeed = sqrt(vel_x * vel_x + vel_y * vel_y);

  float robotDirectionAngle = atan2(vel_y, vel_x);

  float wheelLinearVelocity[3];

  for (int i = 0; i < 3; i++)
  {
    wheelLinearVelocity[i] =
        (robotSpeed * sin(robotDirectionAngle - wheelAngles[i]) + robotAngularVelocity*0.3)*80; //Last multiplication is scaling
  }

  m0 = wheelLinearVelocity[0];
  m1 = wheelLinearVelocity[1];
  m2 = wheelLinearVelocity[2];

  value.data = m0;
  v_leftCommand.publish(value);
  value.data = m1;
  v_backCommand.publish(value);
  value.data = m2;
  v_rightCommand.publish(value);
}

void teleop_callback(const geometry_msgs::Twist &cmd_vel_msg)
{
  format_cmd(cmd_vel_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gazebo_driver_node");
  ros::NodeHandle nh;

  //Where the wheels are if straight in front is 0
  wheelAngles.push_back(M_PI - 2 * M_PI / 3.0f);
  wheelAngles.push_back(M_PI);
  wheelAngles.push_back(M_PI + 2 * M_PI / 3.0f);

  //Controller speed publishers
  v_leftCommand = nh.advertise<std_msgs::Float64>(
      "left_joint_velocity_controller/command", 1);
  v_backCommand = nh.advertise<std_msgs::Float64>(
      "back_joint_velocity_controller/command", 1);
  v_rightCommand = nh.advertise<std_msgs::Float64>(
      "right_joint_velocity_controller/command", 1);

  // Subscriber that subscribes to cmd_vel
  ros::Subscriber teleop_sub = nh.subscribe("cmd_vel", 1, teleop_callback);

  ros::Rate loop_rate(50);
  while (ros::ok())
  {

    ros::spinOnce();

    loop_rate.sleep();
  }
}
