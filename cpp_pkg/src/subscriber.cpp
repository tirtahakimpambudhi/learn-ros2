#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "std_msgs/msg/string.hpp"

class SubscriberNode : public rclcpp::Node
{
    public:
        rclcpp::Logger logger = get_logger();
        SubscriberNode() : Node("cpp_pkg_subscriber_node")
        {
            subscription_ = create_subscription<std_msgs::msg::String>("counter_publish", 10, std::bind(&SubscriberNode::subscriber_callback, this, std::placeholders::_1));
        }

    private: 
        void subscriber_callback(const std_msgs::msg::String::SharedPtr message) {
            RCLCPP_INFO(logger, "Receive message: %s", message->data.c_str());
        };
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
        
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  SubscriberNode::SharedPtr node = std::make_shared<SubscriberNode>();
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