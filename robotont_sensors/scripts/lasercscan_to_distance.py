#!/usr/bin/env python
import rospy
import time
from numpy import mean
from std_msgs.msg import Float64
from sensor_msgs.msg import LaserScan
from robotont_sensors.msg import LaserScanSplit

pub = rospy.Publisher('/laserscan_split', Float64, queue_size=2)

def scan_callback(data):
    ls_split = LaserScanSplit()

    ls_split.stamp = rospy.Time()

    distances = data.ranges
    array_len = len(distances)

    left_array = distances[0:array_len/3]
    ls_split.leftMin = min(left_array)
    ls_split.leftMean = mean(left_array)

    center_array = distances[array_len/3:2*array_len/3]
    ls_split.centerMin = min(center_array)
    ls_split.centerMean = mean(center_array)

    right_array = distances[2*array_len/3:]
    ls_split.rightMin = min(right_array)
    ls_split.rightMean = mean(right_array)

    pub.publish(left_dist)

def convert():
    # Starts a new node
    rospy.init_node('laserscan_to_distance', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, scan_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        convert()
    except rospy.ROSInterruptException: pass