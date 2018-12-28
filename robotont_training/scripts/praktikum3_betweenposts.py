#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import time
from robotont_sensors.msg import LaserScanSplit

distances = LaserScanSplit()


def scan_callback(data):
    global distances
    distances = data


def move():
    global distances
    # Starts a new node
    rospy.init_node('robotont_velocity_publisher', anonymous=True)
    velocity_publisher = rospy.Publisher(
        '/robotont/cmd_vel', Twist, queue_size=1)
    rospy.Subscriber('/scan_to_distance', LaserScanSplit, scan_callback)
    vel_msg = Twist()

    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0

    while not rospy.is_shutdown():
        try:
            ########################
            # YOUR CODE HERE START #
            ########################
		if distances.centerMin < 0.4:
			vel_msg.linear.x = -0.1
			vel_msg.linear.y = 0
			vel_msg.angular.z = 0
			velocity_publisher.publish(vel_msg)
			time.sleep(0.1)

		elif distances.leftMin > distances.centerMin:
			vel_msg.linear.x = 0
			vel_msg.linear.y = 0
			vel_msg.angular.z = 0.3
			velocity_publisher.publish(vel_msg)
			time.sleep(0.1)
		elif distances.rightMin > distances.centerMin:
			vel_msg.linear.x = 0
			vel_msg.linear.y = 0
			vel_msg.angular.z = -0.3
			velocity_publisher.publish(vel_msg)
			time.sleep(0.1)
		else:
			vel_msg.linear.x = 0.2
			vel_msg.linear.y = 0
			vel_msg.angular.z = 0
			velocity_publisher.publish(vel_msg)
			time.sleep(0.1)


            ######################
            # YOUR CODE HERE END #
            ######################
        except KeyboardInterrupt:
            # After the loop, stops the robot
            vel_msg.linear.x = 0
            vel_msg.linear.y = 0
            vel_msg.linear.z = 0
            vel_msg.angular.x = 0
            vel_msg.angular.y = 0
            vel_msg.angular.z = 0
            # Force the robot to stop
            velocity_publisher.publish(vel_msg)
            time.sleep(1)


if __name__ == '__main__':
    try:
        move()
    except rospy.ROSInterruptException:
        pass
