cmake_minimum_required(VERSION 3.8)
project(joystick_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

#cpp部分
#include
include_directories(include/joystick_control)
aux_source_directory(./src SRC_LIST)
#executable
#add_executable(Joy_node src/Joy_node.cpp src/JoyListener.cpp src/TwistPub.cpp)
add_executable(Joy_node ${SRC_LIST})
ament_target_dependencies(Joy_node rclcpp std_msgs geometry_msgs std_srvs)
#install
install(TARGETS
Joy_node
  DESTINATION lib/${PROJECT_NAME}  
)

#py部分
#install python modules
ament_python_install_package(py_pkg)
#install python exe
install(PROGRAMS
  scripts/joy_publisher_node.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
