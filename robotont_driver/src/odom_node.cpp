#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
#include <string>
#include <Eigen/Dense>

int wheelAmount;
// initial list for the angles of the wheels
std::vector<float> wheelAngles;

// omniwheel data
float wheelDistanceFromCenter;
float wheelRadius;
float gearboxReductionRatio;
float encoderEdgesPerMotorRevolution;
int pidControlFrequency;

float wheelSpeedToMainboardUnits;

float vx;
float vy;
float vth;

Eigen::MatrixXf odomMatrix(3,3);
Eigen::MatrixXf odomMatrixInv(3,3);

void format_input(std_msgs::String msg){

	int encIn[3] = {0, 0, 0};
	char c;
	float phi0, phi1, phi2;
	
	std::string t0, t1, t2, t3;

	std::stringstream(msg.data) >> encIn[0] >> t1;
	t1.erase(t1.begin());
	std::stringstream(t1) >> encIn[1] >> t2;
	t2.erase(t2.begin());
	std::stringstream(t2) >> encIn[2] >> t3;

	//ROS_INFO_STREAM("sstm: " << t1 << " " << t2);

	//ROS_INFO_STREAM("ODOMETRY motors: " << encIn[0] << " " << encIn[1] << " " << encIn[2] << "\n"); //debug purpose

	phi0 = (encIn[0])/wheelSpeedToMainboardUnits;
	phi1 = (encIn[1])/wheelSpeedToMainboardUnits;
	phi2 = (encIn[2])/wheelSpeedToMainboardUnits;

	ROS_INFO_STREAM("phi: " << phi0 << " " << phi1 << " " << phi2);

	int motorCount = wheelAmount;

	for(int i= 0; i < motorCount; i++){
		odomMatrix.row(i) << (cos(wheelAngles[i])), (sin(wheelAngles[i])), wheelDistanceFromCenter;
	}

	odomMatrixInv = odomMatrix.inverse();

	//ROS_INFO_STREAM("matrix :" << odomMatrixInv); //debug purpose

	vy = (-1)*(odomMatrixInv(0,0)*phi0 + odomMatrixInv(0,1)*phi1 + odomMatrixInv(0,2)*phi2);
	vx = (odomMatrixInv(1,0)*phi0 + odomMatrixInv(1,1)*phi1 + odomMatrixInv(1,2)*phi2);
	vth = (-1)*(odomMatrixInv(2,0)*phi0 + odomMatrixInv(2,1)*phi1 + odomMatrixInv(2,2)*phi2);

	//ROS_INFO_STREAM("ODOMETRY FOMRAT INPUT: " << vx << " " << vy << " " << vth << "\n"); //debug purpose
}

void write_callback(std_msgs::String msg){
	ROS_INFO_STREAM("I heard: \n" << msg);
	format_input(msg);
	//ROS_INFO_STREAM("I will publish: \n" << output_cmd);
}


int main(int argc, char** argv) {
	ROS_INFO_STREAM("ODOMETRY pre\n");
	ros::init(argc, argv, "odom_node");	
	ros::NodeHandle nh;

	nh.getParam("/wheelAmount", wheelAmount);    
    	nh.getParam("/wheelRads", wheelAngles);
	nh.getParam("/wheelDistanceFromCenter", wheelDistanceFromCenter);
	nh.getParam("/wheelRadius", wheelRadius);
	nh.getParam("/gearboxReductionRatio", gearboxReductionRatio);
	nh.getParam("/encoderEdgesPerMotorRevolution", encoderEdgesPerMotorRevolution);
	nh.getParam("/pidControlFrequency", pidControlFrequency);

	wheelSpeedToMainboardUnits = gearboxReductionRatio * encoderEdgesPerMotorRevolution / (2 * M_PI * wheelRadius * pidControlFrequency);

	ros::Subscriber serial_sub = nh.subscribe("serial_write", 50, write_callback);
	ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
	tf::TransformBroadcaster odom_broadcaster;
	
	float x = 0.0;
	float y = 0.0;
	float th = 0.0;
	
	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();

	ROS_INFO_STREAM("ODOMETRY START!\n");
	
	ros::Rate loop_rate(10);
	while(ros::ok()){
	    
	    ros::spinOnce();
	    current_time = ros::Time::now();
	    
	    float dt = (current_time - last_time).toSec();
	    float delta_x = (vx * cos(th) - vy * sin(th)) * dt;
	    float delta_y = (vx * sin(th) + vy * cos(th)) * dt;
	    float delta_th = vth * dt;

	    x += delta_x;
	    y += delta_y;
	    th += delta_th;
	    
	    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
	    
	    geometry_msgs::TransformStamped odom_trans;
	    odom_trans.header.stamp = current_time;
	    odom_trans.header.frame_id = "odom";
	    odom_trans.child_frame_id = "base_link";
	    
	    odom_trans.transform.translation.x = x;
	    odom_trans.transform.translation.y = y;
	    odom_trans.transform.translation.z = 0.0;
	    odom_trans.transform.rotation = odom_quat;
	    
	    odom_broadcaster.sendTransform(odom_trans);
	    
	    nav_msgs::Odometry odom;
	    odom.header.stamp = current_time;
	    odom.header.frame_id = "odom";
	    
	    odom.pose.pose.position.x = x;
	    odom.pose.pose.position.y = y;
	    odom.pose.pose.position.z = 0.0;
	    odom.pose.pose.orientation = odom_quat;
	    
	    odom.child_frame_id = "base_link";
	    odom.twist.twist.linear.x = vx;
	    odom.twist.twist.linear.y = (-1)*vy;
	    odom.twist.twist.angular.z = vth;
	    
	    odom_pub.publish(odom);
	    
	    last_time = current_time;
	    loop_rate.sleep();    
	}
}
