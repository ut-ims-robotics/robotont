cmake_minimum_required(VERSION 2.8.3)
project(robotont_description)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  joy
  nav_msgs
  cmake_modules
)

catkin_package(
  CATKIN_DEPENDS
    std_msgs
    joy
    nav_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(gazebo_robotont_teleop_joy src/gazebo_robotont_teleop_joy.cpp) 

target_link_libraries(gazebo_robotont_teleop_joy ${catkin_LIBRARIES})

