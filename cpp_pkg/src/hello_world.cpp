#include "rclcpp/rclcpp.hpp"
#include  "rclcpp/node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>("cpp_pkg_hello_world_node");
    rclcpp::Logger logger =  node->get_logger();
    RCLCPP_INFO(logger, "Hello World from C++");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0; 
}