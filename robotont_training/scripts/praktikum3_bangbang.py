#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import time
from robotont_sensors.msg import LaserScanSplit


velocity_publisher = rospy.Publisher(
    '/robotont/cmd_vel', Twist, queue_size=10)
vel_msg = Twist()


def closing():
    # After the loop, stops the robot
    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0
    # Force the robot to stop
    velocity_publisher.publish(vel_msg)


distances = LaserScanSplit()


def scan_callback(data):
    global distances
    distances = data


def move():
    global distances
    # Starts a new node
    rospy.init_node('robotont_velocity_publisher', anonymous=True)

    rospy.Subscriber('/scan_to_distance', LaserScanSplit, scan_callback)

    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0

    while not rospy.is_shutdown():
        ########################
        # YOUR CODE HERE START #
        ########################
        vel_msg.linear.x = 0
        vel_msg.linear.y = 0
        vel_msg.angular.z = 0
        velocity_publisher.publish(vel_msg)
        time.sleep(0.1)
        ######################
        # YOUR CODE HERE END #
        ######################


if __name__ == '__main__':
    try:
        rospy.on_shutdown(closing)
        move()
    except rospy.ROSInterruptException:
        pass
