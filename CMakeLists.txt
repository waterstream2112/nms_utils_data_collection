cmake_minimum_required(VERSION 3.8)
project(nms_utils_data_collection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(pcl_conversions REQUIRED PATHs /opt/ros/humble)
find_package(PCL REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

### include
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
)


### Define common source
# set(common_source
#   src/common_definitions.cpp)


### Executables: node_go2_transform_pointcloud
add_executable(node_lidar_imu_time_offset
  src/node_lidar_imu_time_offset.cpp
  )
ament_target_dependencies(node_lidar_imu_time_offset
  rclcpp 
  std_msgs 
  sensor_msgs 
  geometry_msgs
  PCL
  pcl_conversions
  tf2
  tf2_ros
  tf2_sensor_msgs
  tf2_geometry_msgs
  )
target_link_libraries(node_lidar_imu_time_offset 
	${PCL_LIBRARIES}
	)
install(TARGETS
	node_lidar_imu_time_offset
	DESTINATION lib/${PROJECT_NAME}
  )


### Install
# install(PROGRAMS 
#   src/go2_setup_frames.py 
#   DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/${PROJECT_NAME}/ DESTINATION include/${PROJECT_NAME}/)
install(DIRECTORY config launch DESTINATION share/${PROJECT_NAME}/)

### Find Python modules in the 'src' folder
ament_python_install_package(src)

ament_package()
