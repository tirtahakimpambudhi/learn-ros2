cmake_minimum_required(VERSION 3.8)
project(activity03_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(number_publish src/number_publish.cpp)
ament_target_dependencies(
  number_publish
  rclcpp
  std_msgs
)

add_executable(number_counter src/number_counter.cpp)
ament_target_dependencies(
  number_counter
  rclcpp
  std_srvs
  std_msgs
)


add_executable(reset_counter src/reset_counter.cpp)
ament_target_dependencies(
  reset_counter
  rclcpp
  std_srvs
)


install(TARGETS number_publish reset_counter number_counter DESTINATION lib/${PROJECT_NAME})
ament_package()


