cmake_minimum_required(VERSION 3.8)
project(ros2_tf2)

# Enable C++17 for ROS2 Humble/Iron/Jazzy compatibility
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# -----------------------------------------------------------------------------
# 1. Find Dependencies
# -----------------------------------------------------------------------------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

# -----------------------------------------------------------------------------
# 2. Build the Executable
# -----------------------------------------------------------------------------
# Define the binary name and the source file to compile
add_executable(tf_broadcaster src/tf_broadcaster.cpp)

# Link the ROS2 libraries and include directories
ament_target_dependencies(tf_broadcaster
  rclcpp
  tf2_ros
  geometry_msgs
)

# -----------------------------------------------------------------------------
# 3. Installation
# -----------------------------------------------------------------------------
# This makes the node available to 'ros2 run'
install(TARGETS
  tf_broadcaster
  DESTINATION lib/${PROJECT_NAME})

# -----------------------------------------------------------------------------
# 4. Testing & Packaging
# -----------------------------------------------------------------------------
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
