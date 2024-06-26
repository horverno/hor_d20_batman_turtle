cmake_minimum_required(VERSION 3.8)
project(hor_d20_batman_turtle)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
  turtlesim
)

add_executable(batman_draw src/batman_draw.cpp)
ament_target_dependencies(batman_draw ${ament_dependencies} )

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
batman_draw
DESTINATION lib/${PROJECT_NAME})

ament_package()