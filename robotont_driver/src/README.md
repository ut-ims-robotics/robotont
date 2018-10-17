# README

driver_node.cpp
This node subscribes to cmd_vel (<geometry_msgs::Twist>) topic (teleop output) and formats the data to a form which can be written to serial interface. The formatted data is published to serial_write (<std_msgs::String>) topic.
For individual launch:
        rosrun robotont_driver driver_node

serial_com_node.cpp
This node subscribes to serial_write (<std_msgs::String>) topic. It writes everything published on this topic to serial port (default:port = /dev/ttyACM0, baudrate = 9600). The data is written in format "m0:m1:m2;\n" where m0, m1 and m2 are integers calculated in driver_node. The node also reads data from serial port. Everything read is published on serial_read(<std_msgs::String>) topic.
For individual launch:
        rosrun robotont_driver serial_com_node

robotont_teleop_joy.cpp
This node subscribes to joy (<sensor_msgs::Joy>) topic and formats the data into suitable format, which is then published on cmd_vel (<geometry_msgs::Twist>) topic.
For individual launch:
	rosrun robotont_driver robotont_teleop_joy

odom_node.cpp
This node subsribes to serial_read (<std_msgs::String>) topic. It converts the input from the motors into odometry data and publishes it on /odom (<nav_msgs::Odometry>) topic.

To use without teleop_joy

We can use rosrun teleop_twist_keyboard teleop_twist_keyboard.py
which publishis directly "Twist" and using keyboard as an input
