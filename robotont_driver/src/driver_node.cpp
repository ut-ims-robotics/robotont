/* 
* This node listens to teleop (cmd_vel), then formats the command accordingly 
* and publishes the formatted string to serial (topic:'write')
*/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <string>

/*
* THINGS TO CONSIDER
*
* Maybe a std_msg::String should also be declared in the beginning (doea it update
* the data if it is done so?)
*/

// The String that contains the command that is being broadcasted to hardware
std::string output_cmd = "a0b0c0\n";

void format_cmd(const geometry_msgs::Twist& cmd_vel_msg){
    
    float maxV = 1.0; // maximum linear velocity
    float radius = 0.15;
    float maxRV = maxV/radius; // angular velocity that cossesponds to the steps
    float steps = 255; // maximum value to send to motors
    float unitV = steps/maxV; // value for velocity 1 m/s
    float unitRV = steps/maxRV; // value for angular velocity 1 rad/s

    /* 
    Don't have to provide maximum values actually - it would be easier to check if
    sent value is too big or not.
    But it is important that the maxV and steps values correspond to each other
    eg. if you send motor dac value 255, it rotates at a velocity of 0.2 m/s
    */

    float m0 = 0;
    float m1 = 0;
    float m2 = 0;

    float vel_x = cmd_vel_msg.linear.x; 
    float vel_y = cmd_vel_msg.linear.y; 
    float vel_t = cmd_vel_msg.angular.z; 

//    ROS_INFO_STREAM("I heard: \n" << cmd_vel_msg);
    m0 += vel_x * unitV;
    m1 += vel_x * unitV;// * (-1);
    m2 += vel_x * unitV * 0;

//    ROS_INFO_STREAM("I calculated: \n" << unitV);

    m0 += vel_y * unitV * 0.866;// * (-1);
    m1 += vel_y * unitV * 0.866;
    m2 += vel_y * unitV;// * (-1);

    m0 += vel_t * unitRV;
    m1 += vel_t * unitRV;
    m2 += vel_t * unitRV;


    // http://stackoverflow.com/questions/191757/how-to-concatenate-a-stdstring-and-an-int 
    // important note about speed

    std::stringstream sstm;
    sstm << 'a' << static_cast<int>(m0) << 'b' << static_cast<int>(m1) << 'c' << static_cast<int>(m2) << '\n';
//    ROS_INFO_STREAM("I calculated: \n" << sstm.str());
    output_cmd = sstm.str();
}


/*
* SUBSCRIBER CALLBACK FUNCTION
* The function starts everytime there is a new message published to given topic
*/
void teleop_callback(const geometry_msgs::Twist& cmd_vel_msg){
    // TODO: take cmd_vel and format it to a00b00c00. Write the value to output_cmd
    ROS_INFO_STREAM("I heard: \n" << cmd_vel_msg);
    format_cmd(cmd_vel_msg);
    ROS_INFO_STREAM("I will publish: \n" << output_cmd);
}


/*
* THE MAIN FUNCTION
* the function initialises the node and creates a subscriber and a publisher
* Then as long as the program is running, it will publish the velocity command 
* to a given topic which will forward everything to harware through serial 
* connection
*/
int main (int argc, char** argv){
    ros::init(argc, argv, "driver_node");
    ros::NodeHandle nh;
    
    // Subscriber that subscribes to cmd_vel
    ros::Subscriber teleop_sub = nh.subscribe("turtlebot_teleop/cmd_vel", 1000, teleop_callback);

    // Publisher that publishes correctly formated command to serial
    ros::Publisher formated_cmd_pub = nh.advertise<std_msgs::String>("write", 1000);

    // The rate at which the program publishes to serial
    ros::Rate loop_rate(10);
    while(ros::ok()){
        // Check for new messages in queue
        ros::spinOnce();

        //ROS_INFO_STREAM("Reading velocity..");
        std_msgs::String result;
        result.data = output_cmd;
        ROS_INFO_STREAM("Publishing: " << result);
        formated_cmd_pub.publish(result);

        loop_rate.sleep();

    }
}
