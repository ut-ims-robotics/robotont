#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>

namespace robotont
{
class Odom
{
public:
  Odom();
  ~Odom();

  void reset();
  void publish();
  void update(float pos_x, float pos_y, float ori_z, float lin_vel_x, float lin_vel_y, float ang_vel_z);
//  inline const nav_msgs::Odometry& getOdomMsg() const {return odom_msg_;};
//  const geometry_msgs::TransformStamped& getTFMsg() const;
//
  void setFrameId(const std::string& frame_id);

  void setChildFrameId(const std::string& child_frame_id);

private:
  nav_msgs::Odometry odom_msg_;
  geometry_msgs::TransformStamped odom_transform_;
  ros::NodeHandle nh_;
  ros::Publisher odom_pub_;
  tf::TransformBroadcaster odom_broadcaster_;
};
}
