cmake_minimum_required(VERSION 2.8.3)
project(robotont_driver)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  serial
)

catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    std_msgs
    serial
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(serial_com_node src/serial_com_node.cpp)
add_executable(driver_node src/driver_node.cpp)

target_link_libraries(serial_com_node ${catkin_LIBRARIES})
target_link_libraries(driver_node ${catkin_LIBRARIES})

