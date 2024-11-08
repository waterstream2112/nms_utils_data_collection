
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time.hpp"
#include <sensor_msgs/msg/imu.hpp>
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/common/impl/transforms.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>


class NodeLidarImuTimeOffset : public rclcpp::Node
{
private:
    rclcpp::Time imuTimeStamp = this->now();
    rclcpp::Time pointcloudTimeStamp = this->now();

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imuSub_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloudSub_;


public:
    NodeLidarImuTimeOffset() : rclcpp::Node("node_lidar_imu_time_offset")
    {

        // Subscription
        imuSub_ = this->create_subscription<sensor_msgs::msg::Imu>(
                                "/imu", 
                                10, 
                                std::bind(&NodeLidarImuTimeOffset::imuCallback, this, std::placeholders::_1));
        pointcloudSub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
                                "/pointcloud", 
                                10, 
                                std::bind(&NodeLidarImuTimeOffset::pointcloudCallback, this, std::placeholders::_1));
    }


    void imuCallback(const sensor_msgs::msg::Imu::ConstSharedPtr &msg) {
        // RCLCPP_INFO(this->get_logger(), "Orientation: [%f, %f, %f]",
        //             msg->orientation.x, msg->orientation.y, msg->orientation.z);
        // RCLCPP_INFO(this->get_logger(), "Angular Velocity: [%f, %f, %f]",
        //             msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);
        // RCLCPP_INFO(this->get_logger(), "Linear Acceleration: [%f, %f, %f]",
        //             msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z);

        rclcpp::Duration elapse = this->now() - imuTimeStamp;

        imuTimeStamp = msg->header.stamp;

        // RCLCPP_INFO(this->get_logger(), "imu: %ld ", imuTimeStamp.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "imu elapsed time: %ld ", elapse.nanoseconds());


    }


    void pointcloudCallback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg)
    {
        rclcpp::Time current = this->now();
        pointcloudTimeStamp = msg->header.stamp;

        // Calculate the duration
        rclcpp::Duration duration = pointcloudTimeStamp - imuTimeStamp;
        // rclcpp::Duration duration = pointcloudTimeStamp - current;

        // Log the duration
        // RCLCPP_INFO(this->get_logger(), "Now     : %ld", current.nanoseconds());
        // RCLCPP_INFO(this->get_logger(), "pcl rcv : %ld ", pointcloudTimeStamp.nanoseconds());
        // RCLCPP_INFO(this->get_logger(), "imu rcv : %ld ", imuTimeStamp.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "Duration: %ld", duration.nanoseconds());
    }
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeLidarImuTimeOffset>());
    rclcpp::shutdown();
    return 0;
}