cmake_minimum_required(VERSION 2.8.3)
project(robotont_driver)

# Setup Eigen3 variables
find_package(Eigen3 REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  joy
  tf
  nav_msgs
  cmake_modules
  serial
)

catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    std_msgs
    joy
    tf
    nav_msgs
    serial
    DEPENDS EIGEN3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(driver_node src/driver_node.cpp src/robotont_hardware.cpp src/odom.cpp ) 
add_executable(gazebo_driver_node src/gazebo_driver.cpp) 
add_executable(gazebo_odom_node src/gazebo_odom.cpp) 



target_link_libraries(driver_node ${catkin_LIBRARIES})
target_link_libraries(gazebo_driver_node ${catkin_LIBRARIES})
target_link_libraries(gazebo_odom_node ${catkin_LIBRARIES})

