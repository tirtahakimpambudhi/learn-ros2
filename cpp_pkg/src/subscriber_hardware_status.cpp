#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include <random>
#include "custom_ros_interfaces/msg/hardware_status.hpp"

using namespace std::chrono_literals;

class SubscribeHardwareStatus : public rclcpp::Node
{
    public:
        SubscribeHardwareStatus() : Node("subscribe_hardware_status_node")
        {
            subscription_ = create_subscription<custom_ros_interfaces::msg::HardwareStatus>(
                "status",
                10,
                std::bind(&SubscribeHardwareStatus::subscribe_data, this, std::placeholders::_1)
            );
        }
    private:
        rclcpp::Subscription<custom_ros_interfaces::msg::HardwareStatus>::SharedPtr subscription_;


        void subscribe_data(custom_ros_interfaces::msg::HardwareStatus::SharedPtr value) {
            RCLCPP_INFO(get_logger(), value->is_ready_motor ? "Received status is ready" : "Received status is not ready");
        }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    SubscribeHardwareStatus::SharedPtr node = std::make_shared<SubscribeHardwareStatus>();

    try
    {
        rclcpp::spin(node);
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(node->get_logger(), "Exception caught %s", e.what());
        rclcpp::shutdown();
        return 1;
    }
    rclcpp::shutdown();
    return 0;
}