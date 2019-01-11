#!/usr/bin/env python
import rospy
import time
from std_msgs.msg import Float64
from sensor_msgs.msg import LaserScan
from robotont_sensors.msg import LaserScanSplit

pub = rospy.Publisher('/scan_to_distance', LaserScanSplit, queue_size=1)

def scan_callback(data):
    laserscan_distance = LaserScanSplit()

    laserscan_distance.stamp = rospy.Time.now()

    distances = data.ranges
    array_len = len(distances)

    right_array = distances[0:array_len/3]
    laserscan_distance.rightMin = min(right_array)

    center_array = distances[array_len/3:2*array_len/3]
    laserscan_distance.centerMin = min(center_array)

    left_array = distances[2*array_len/3:]
    laserscan_distance.leftMin = min(left_array)

    pub.publish(laserscan_distance)

def convert():
    # Starts a new node
    rospy.init_node('laserscan_to_distance', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, scan_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        convert()
    except rospy.ROSInterruptException: pass
