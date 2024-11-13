#! /usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node



def generate_launch_description():
    
    # Declare remapping
    # remappings = [("/pointcloud", "/livox/lidar"), 
    #               ("/imu", "/livox/imu")]

    remappings = [("/pointcloud", "/lidar_points"), 
                  ("/imu", "/topic_imu")]
    
    # Declare node actions
    node_lidar_imu_time_offset = Node(
        package="nms_utils_data_collection",
        name="node_lidar_imu_time_offset",
        executable="node_lidar_imu_time_offset",
        remappings=remappings,
        output="screen"
    )
    
    # Create the launch description and populate
    ld = LaunchDescription()

    # Add node actions to the launch description
    ld.add_action(node_lidar_imu_time_offset)
    
    return ld