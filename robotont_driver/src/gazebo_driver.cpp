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

int wheelAmount;

// initial list for the angles of the wheels
std::vector<float> wheelAngles;

// omniwheel data
float wheelDistanceFromCenter;
float wheelRadius;
float gearboxReductionRatio;
int encoderEdgesPerMotorRevolution;
float pidControlFrequency;

float wheelSpeedToMainboardUnits;

float wheel_ang_scaler = 0.5;
float angular_vel_scaler = 2;

ros::Publisher v_leftCommand;
ros::Publisher v_backCommand;
ros::Publisher v_rightCommand;

std_msgs::Float64 value;

void format_cmd(const geometry_msgs::Twist& cmd_vel_msg) {
  float m0 = 0;
  float m1 = 0;
  float m2 = 0;

  float vel_x = cmd_vel_msg.linear.x;
  float vel_y = cmd_vel_msg.linear.y;
  float vel_t = cmd_vel_msg.angular.z;

  int motorCount = wheelAmount;

  float robotSpeed = 0;

  if (vel_x == 0) {
    robotSpeed = std::abs(vel_y);
  } else if (vel_y == 0) {
    robotSpeed = std::abs(vel_x);
  } else {
    robotSpeed = sqrt(vel_x * vel_x + vel_y * vel_y);
  }

  float robotDirectionAngle = atan2(vel_x, vel_y);

  // ROS_INFO_STREAM("robotDirectionAngle: " << (float)wheelAngles[0]); //debug
  // purpouse

  float robotAngularVelocity = vel_t * angular_vel_scaler;

  float wheelLinearVelocity[motorCount];
  float wheelAngularSpeedMainboardUnits[motorCount];

  for (int i = 0; i < motorCount; i++) {
    wheelLinearVelocity[i] =
        robotSpeed * cos(robotDirectionAngle - wheelAngles[i]) +
        wheelDistanceFromCenter * robotAngularVelocity;
    wheelAngularSpeedMainboardUnits[i] =
        wheelLinearVelocity[i] * wheelSpeedToMainboardUnits;
  }

  m0 = wheelAngularSpeedMainboardUnits[0] * wheel_ang_scaler;
  m1 = wheelAngularSpeedMainboardUnits[1] * wheel_ang_scaler;
  m2 = wheelAngularSpeedMainboardUnits[2] * wheel_ang_scaler;

  value.data = m0;
  v_leftCommand.publish(value);
  value.data = m1;
  v_backCommand.publish(value);
  value.data = m2;
  v_rightCommand.publish(value);
}

/*
* SUBSCRIBER CALLBACK FUNCTION
* The function starts everytime there is a new message published to given topic
*/
void teleop_callback(const geometry_msgs::Twist& cmd_vel_msg) {
  format_cmd(cmd_vel_msg);
}

/*
* THE MAIN FUNCTION
* the function initialises the node and creates a subscriber and a publisher
* Then as long as the program is running, it will publish the velocity command
* to a given topic which will forward everything to harware through serial
* connection
*/
int main(int argc, char** argv) {
  ros::init(argc, argv, "gazebo_driver_node");
  ros::NodeHandle nh;

  std::vector<float> default_wheel_angles;
  default_wheel_angles.push_back(M_PI + 2 * M_PI / 3.0f);
  default_wheel_angles.push_back(M_PI);
  default_wheel_angles.push_back(M_PI - 2 * M_PI / 3.0f);

  nh.param("/wheelAmount", wheelAmount, 3);
  nh.param("/wheelRads", wheelAngles, default_wheel_angles);
  nh.param("/wheelDistanceFromCenter", wheelDistanceFromCenter, 0.125f);
  nh.param("/wheelRadius", wheelRadius, 0.035f);
  nh.param("/gearboxReductionRatio", gearboxReductionRatio, 18.75f);
  nh.param("/encoderEdgesPerMotorRevolution", encoderEdgesPerMotorRevolution,
           64);
  nh.param("/pidControlFrequency", pidControlFrequency, 100.0f);

  wheelSpeedToMainboardUnits = gearboxReductionRatio *
                               encoderEdgesPerMotorRevolution /
                               (2 * M_PI * wheelRadius * pidControlFrequency);
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
  while (ros::ok()) {
    
    ros::spinOnce();

    loop_rate.sleep();
  }
}
