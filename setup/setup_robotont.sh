#!/bin/bash
#echo 'This script configures ROS_PACKAGE_PATH, ROS_MASTER_URI, and ROS_IP'

source ~/catkin_ws/devel/setup.bash

# Set up robotont-2 as ROS MASTER
export ROS_MASTER_URI=http://10.42.0.${HOSTNAME:10:1}:11311

# Use ifconfig to get the wifi interface IP
#robotont wlp62s0, computer wlo1
export ROS_IP=$(ifconfig wlo1 | grep -oP 'inet addr:\K\S+') # ethernet

  echo -e "ROS_MASTER_URI  =  $ROS_MASTER_URI"
  echo -e "ROS_IP          =  $ROS_IP"
