#include "rclcpp/rclcpp.hpp"  
#include "rclcpp/node.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node {
    public: 
        rclcpp::Logger logger = get_logger();
        PublisherNode() : Node("cpp_pkg_publisher_node") {
            publisher_ = create_publisher<std_msgs::msg::String>("counter_publish", 10);
            counter_timer_ = create_timer(0.5s, std::bind(&PublisherNode::counter_callback, this));
            publish_timer_ = create_wall_timer(1.5s, std::bind(&PublisherNode::publisher, this));
        };

    private: 

        void counter_callback() {
            count_++;
            RCLCPP_INFO(logger, "Counter: %d", count_);
        };
    
        void publisher() {
            std_msgs::msg::String message = std_msgs::msg::String();
            message.data = std::string("Publish data : {") + std::to_string(count_) + std::string("}\n");
            RCLCPP_INFO(logger, "Publishing data");
            publisher_->publish(message);
        };

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr publish_timer_; 
        rclcpp::TimerBase::SharedPtr counter_timer_; 
        int count_ = 0;

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    PublisherNode::SharedPtr node = std::make_shared<PublisherNode>();

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