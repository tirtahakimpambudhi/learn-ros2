#include <rclcpp/rclcpp.hpp>
#include <rclcpp/node.hpp>
#include <std_msgs/msg/int64.hpp>

using namespace std::chrono_literals;
using namespace std;

class NumberPublisherNode : public rclcpp::Node
{
    public:
        NumberPublisherNode() : Node("number_publisher_node_cpp")
        {
            publisher_ = create_publisher<std_msgs::msg::Int64>(
                "number", 
                10
            );
            timers_ = create_timer(
                1.0s,
                bind(&NumberPublisherNode::publish_data, this)
            );
        };
    private:
        void publish_data() {
            count_++;
            std_msgs::msg::Int64 value = std_msgs::msg::Int64();
            value.data = count_;
            publisher_->publish(value);
        };
        rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timers_;
        u_int64_t count_ = 0;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    NumberPublisherNode::SharedPtr node = std::make_shared<NumberPublisherNode>();
    try {
        rclcpp::spin(node);
    } catch (const exception& e) {
        RCLCPP_ERROR(node->get_logger(), "Exception caught %s", e.what());
        rclcpp::shutdown();
        return 1;
    }
    rclcpp::shutdown();
    return 0;
}