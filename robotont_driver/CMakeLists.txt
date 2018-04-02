cmake_minimum_required(VERSION 2.8.3)
project(robotont_driver)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  serial
  joy
  tf
  nav_msgs
  cmake_modules
)
find_package(Eigen REQUIRED)


catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    std_msgs
    serial
    joy
    tf
    nav_msgs
    DEPENDS Eigen
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

add_executable(serial_com_node src/serial_com_node.cpp)
add_executable(driver_node src/driver_node.cpp)
add_executable(robotont_teleop_joy src/robotont_teleop_joy.cpp)
add_executable(odom_node src/odom_node.cpp)

target_link_libraries(serial_com_node ${catkin_LIBRARIES})
target_link_libraries(driver_node ${catkin_LIBRARIES})
target_link_libraries(robotont_teleop_joy ${catkin_LIBRARIES})
target_link_libraries(odom_node ${catkin_LIBRARIES})

