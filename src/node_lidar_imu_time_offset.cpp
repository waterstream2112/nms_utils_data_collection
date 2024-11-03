
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/common/impl/transforms.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>


class NodeLidarImuTimeOffset : public rclcpp::Node
{
private:

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloudSub_;

public:
    NodeLidarImuTimeOffset() : rclcpp::Node("node_lidar_imu_time_offset")
    {
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeLidarImuTimeOffset>());
    rclcpp::shutdown();
    return 0;
}