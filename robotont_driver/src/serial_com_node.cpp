/***
* This node listens to topic serial_write and forwards everything to serialport
* Everything that the node reads from serialport will be published on the topic serial_read
*/

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

serial::Serial ser;

void write_callback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->data);
    ser.write(msg->data);
}

int main (int argc, char** argv){
    ros::init(argc, argv, "serial_com_node");
    ros::NodeHandle nh;

    ros::Subscriber write_sub = nh.subscribe("serial_write", 1000, write_callback);
    ros::Publisher read_pub = nh.advertise<std_msgs::String>("serial_read", 1000);

    try // Open serial communication
    {
        ser.setPort("/dev/ttyACM0");
	ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(100);
    while(ros::ok()){

        ros::spinOnce();

        //if(ser.available() > 6){
        //    //ROS_INFO_STREAM("Reading from serial port");
        //    std_msgs::String result;
        //    result.data = ser.readline();
        //    ROS_INFO_STREAM("Read data: " << result.data);
        //    read_pub.publish(result);
        //}
        loop_rate.sleep();

    }
}

