# README

driver_basic.launch
Launches nodes:
	robotont_driver driver_node
	robotont_driver serial_com_node
	robotont_driver odom_node
to launch:
	roslaunch robotont_driver driver_basic.launch

driver_teleop_joy.launch
Launches nodes:
        robotont_driver driver_node
        robotont_driver serial_com_node
        joy joy_node
        robotont_driver robotont_teleop_joy
to launch:
        roslaunch robotont_driver driver_teleop_joy.launch


