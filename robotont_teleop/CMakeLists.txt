cmake_minimum_required(VERSION 2.8.3)
project(robotont_teleop)

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

add_executable(robotont_teleop_joy src/robotont_teleop_joy.cpp) 
add_executable(robotont_teleop_joy_china src/robotont_teleop_joy_china.cpp) 

target_link_libraries(robotont_teleop_joy ${catkin_LIBRARIES})
target_link_libraries(robotont_teleop_joy_china ${catkin_LIBRARIES})

