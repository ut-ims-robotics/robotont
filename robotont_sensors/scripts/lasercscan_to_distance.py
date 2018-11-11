#!/usr/bin/env python
import rospy
import time
from std_msgs.msg import Float64
from sensor_msgs.msg import LaserScan

pub1 = rospy.Publisher('/scan/left', Float64, queue_size=2)
pub2 = rospy.Publisher('/scan/center', Float64, queue_size=2)
pub3 = rospy.Publisher('/scan/right', Float64, queue_size=2)

def scan_callback(data):
    distances = data.ranges
    array_len = len(distances)

    left_array = distances[0:array_len/3]
    left_dist = min(left_array)

    center_array = distances[array_len/3:2*array_len/3]
    center_dist = min(center_array

    right_array = distances[2*array_len/3:]
    right_dist = min(right_array)

    pub1.publish(left_dist)
    pub2.publish(center_dist)
    pub3.publish(rights_dist)

def convert():
    # Starts a new node
    rospy.init_node('laserscan_to_distance', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, scan_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        convert()
    except rospy.ROSInterruptException: pass