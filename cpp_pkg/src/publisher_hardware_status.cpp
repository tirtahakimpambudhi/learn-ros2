#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include <random>
#include "custom_ros_interfaces/msg/hardware_status.hpp"

using namespace std::chrono_literals;

class PublisHardwareStatus : public rclcpp::Node
{
    public:
        PublisHardwareStatus() : Node("publish_hardware_status_node")
        {
            publish_ = create_publisher<custom_ros_interfaces::msg::HardwareStatus>(
                "status",
                10
            );

            timers_ = create_timer(
                1.0s, 
                std::bind(&PublisHardwareStatus::publish_data, this)
            );
        }
    private:
        rclcpp::Publisher<custom_ros_interfaces::msg::HardwareStatus>::SharedPtr publish_;
        rclcpp::TimerBase::SharedPtr timers_;

        void publish_data() {
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_real_distribution<float> range(30.0f, 40.0f);
            std::bernoulli_distribution random_bool(0.5);
            
            custom_ros_interfaces::msg::HardwareStatus value = custom_ros_interfaces::msg::HardwareStatus();
            value.is_ready_motor = (bool) random_bool(gen);
            value.temperature = range(gen);
            value.message = value.is_ready_motor ? "Hardware is ready" :"Hardware is not ready";
            
            publish_->publish(value);
        }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    PublisHardwareStatus::SharedPtr node = std::make_shared<PublisHardwareStatus>();

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