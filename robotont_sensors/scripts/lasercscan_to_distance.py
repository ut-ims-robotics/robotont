#!/usr/bin/env python
import rospy
from sensor_msgs
import time
from std_msgs.msg import Float64
from sensor_msgs.msg import LaserScan

pub2 = rospy.Publisher('/scan/center', Float64)

def scan_callback(data):
    distances = data.ranges
    array_len = len(distances)
    center_array = distances[array_len/3:2*array_len/3]
    center_dist = min(center_array)


    pub2.publish(center_dist)

def convert():
    # Starts a new node
    rospy.init_node('laserscan_to_distance', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, scan_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        convert()
    except rospy.ROSInterruptException: pass