cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(custom_ros_interfaces REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(hello_world src/hello_world.cpp)
ament_target_dependencies(hello_world rclcpp)
add_executable(counter src/counter.cpp)
ament_target_dependencies(counter rclcpp)
add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp)
ament_target_dependencies(publisher std_msgs)
add_executable(subscriber src/subscriber.cpp)
add_executable(service_server src/service_server.cpp)
add_executable(srv_client src/srv_client.cpp)
add_executable(service_client src/service_client.cpp)
add_executable(publisher_hardware_status src/publisher_hardware_status.cpp)
add_executable(subscriber_hardware_status src/subscriber_hardware_status.cpp)
ament_target_dependencies(
  subscriber
  rclcpp
  std_msgs
)
ament_target_dependencies(
  service_server
  rclcpp
  example_interfaces
)
ament_target_dependencies(
  service_client
  rclcpp
  example_interfaces
)
ament_target_dependencies(
  srv_client
  rclcpp
  example_interfaces
)
ament_target_dependencies(
  publisher_hardware_status
  rclcpp 
  custom_ros_interfaces
)
ament_target_dependencies(
  subscriber_hardware_status
  rclcpp 
  custom_ros_interfaces
)
install(TARGETS hello_world counter subscriber_hardware_status publisher_hardware_status publisher subscriber service_client srv_client service_server DESTINATION lib/${PROJECT_NAME})


ament_package()
