#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <string>

class OdomTransformer
{
public:
  OdomTransformer()
  {
    sub_ = n_.subscribe("odom", 100, &OdomTransformer::odom_callback, this);
  }
  void odom_callback(nav_msgs::Odometry odom)
  {
    geometry_msgs::TransformStamped odom_trans;
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(odom.twist.twist.angular.z);

    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = odom.twist.twist.linear.x;
    odom_trans.transform.translation.y = odom.twist.twist.linear.y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    odom_broadcaster.sendTransform(odom_trans);
  }

private:
  ros::NodeHandle n_;
  tf::TransformBroadcaster odom_broadcaster;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gazebo_odom_node");

  OdomTransformer odom_tr;

  ros::spin();
}
