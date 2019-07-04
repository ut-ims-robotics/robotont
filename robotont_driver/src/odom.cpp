#include "robotont_driver/odom.h"

namespace robotont
{
Odom::Odom()
{
  ROS_DEBUG("Odom starting...");

  // Set parent and child frame names for odom and its tf
  odom_msg_.header.frame_id = "odom";
  odom_msg_.child_frame_id = "base_footprint";

  odom_transform_.header.frame_id = odom_msg_.header.frame_id;
  odom_transform_.child_frame_id = odom_msg_.child_frame_id;

  reset();

  // Initialize odom publisher
  odom_pub_ = nh_.advertise<nav_msgs::Odometry>("odom", 2);
}

Odom::~Odom()
{
}

void Odom::setFrameId(const std::string& frame_id)
{
  odom_msg_.header.frame_id = frame_id;
  odom_transform_.header.frame_id = frame_id;
}

void Odom::setChildFrameId(const std::string& child_frame_id)
{
  odom_msg_.child_frame_id = child_frame_id;
  odom_transform_.child_frame_id = child_frame_id;
}

void Odom::reset()
{
  odom_msg_.header.stamp = ros::Time::now();
  odom_msg_.pose.pose.position.x = 0;
  odom_msg_.pose.pose.position.y = 0;
  odom_msg_.pose.pose.position.z = 0;
  odom_msg_.pose.pose.orientation.x = 0;
  odom_msg_.pose.pose.orientation.y = 0;
  odom_msg_.pose.pose.orientation.z = 0;
  odom_msg_.pose.pose.orientation.w = 1;

  odom_transform_.header.stamp = odom_msg_.header.stamp;
  odom_transform_.transform.translation.x = 0;
  odom_transform_.transform.translation.y = 0;
  odom_transform_.transform.translation.z = 0;
  odom_transform_.transform.rotation.x = 0;
  odom_transform_.transform.rotation.y = 0;
  odom_transform_.transform.rotation.z = 0;
  odom_transform_.transform.rotation.w = 0;
}

void Odom::update(float pos_x, float pos_y, float ori_z, float lin_vel_x, float lin_vel_y, float ang_vel_z)
{
  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(ori_z);

  odom_transform_.header.stamp = ros::Time::now();

  odom_transform_.transform.translation.x = pos_x;
  odom_transform_.transform.translation.y = pos_y;
  odom_transform_.transform.translation.z = 0.0;
  odom_transform_.transform.rotation = odom_quat;

  odom_msg_.header.stamp = ros::Time::now();

  odom_msg_.pose.pose.position.x = pos_x;
  odom_msg_.pose.pose.position.y = pos_y;
  odom_msg_.pose.pose.position.z = 0.0;
  odom_msg_.pose.pose.orientation = odom_quat;

  odom_msg_.twist.twist.linear.x = lin_vel_x;
  odom_msg_.twist.twist.linear.y = lin_vel_y;
  odom_msg_.twist.twist.angular.z = ang_vel_z;
}

void Odom::publish()
{
	    odom_pub_.publish(odom_msg_);
      odom_broadcaster_.sendTransform(odom_transform_);
}
}  // namespace robotont
