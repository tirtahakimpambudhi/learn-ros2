#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>


class NumberCounterNode : public rclcpp::Node
{
public:
    NumberCounterNode() : Node("number_counter_node_cpp")
    {
        subscription_ = create_subscription<std_msgs::msg::Int64>(
            "number", 
            10, 
            std::bind(&NumberCounterNode::subscriber_data, this, std::placeholders::_1)
        );
        publisher_ = create_publisher<std_msgs::msg::Int64>(
            "number_count",
            10
        );
    }
private:
    void subscriber_data(const std_msgs::msg::Int64::SharedPtr value) {
        this->count_ += value->data;
        std_msgs::msg::Int64 count = std_msgs::msg::Int64();
        count.data = this->count_;
        publisher_->publish(count);
    }
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    u_int64_t count_ = 0;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    NumberCounterNode::SharedPtr node = std::make_shared<NumberCounterNode>();

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