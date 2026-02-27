#include <chrono>
#include <functional>
#include <memory>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;

class TFBroadcaster : public rclcpp::Node
{
public:
    TFBroadcaster()
        : Node("tf_broadcaster")
    {
        // 1. Initialize the transform broadcaster
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        // 2. Create a timer that triggers every 100ms
        timer_ = this->create_wall_timer(
            100ms, std::bind(&TFBroadcaster::timer_callback, this));
    }

private:
    void timer_callback()
    {
        geometry_msgs::msg::TransformStamped t;

        // 3. Set header information
        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world";
        t.child_frame_id = "robot";

        // 4. Calculate circular motion (x = 2cos(t), y = 2sin(t))
        double time_seconds = this->get_clock()->now().seconds();
        t.transform.translation.x = 2.0 * std::cos(time_seconds);
        t.transform.translation.y = 2.0 * std::sin(time_seconds);
        t.transform.translation.z = 0.0;

        // 5. Set rotation to identity quaternion (no rotation)
        t.transform.rotation.x = 0.0;
        t.transform.rotation.y = 0.0;
        t.transform.rotation.z = 0.0;
        t.transform.rotation.w = 1.0;

        // 6. Broadcast the transform to the /tf topic
        tf_broadcaster_->sendTransform(t);
    }

    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFBroadcaster>());
    rclcpp::shutdown();
    return 0;
}
