#include "rclcpp/rclcpp.hpp"  
#include "rclcpp/node.hpp"
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;

class NumberPublisher : public rclcpp::Node
{
    public:

        NumberPublisher() : Node("number_publisher")
        {
            publish_ = create_publisher<std_msgs::msg::Int64>(
                "number",
                10
            );
            timer_ = create_timer(
                1.0s, 
                std::bind(&NumberPublisher::publish_data, this)
            );
        }



    private:

        void publish_data() {
            std_msgs::msg::Int64 value = std_msgs::msg::Int64();
            value.data = number_;
            RCLCPP_INFO(this->get_logger(), "Publishing data");
            publish_->publish(value);
        }

        rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publish_ ;
        rclcpp::TimerBase::SharedPtr timer_ ;
        int number_ = 5;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    NumberPublisher::SharedPtr node = std::make_shared<NumberPublisher>();

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