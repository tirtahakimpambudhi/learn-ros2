#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::placeholders;


class ServiceServerNode : public rclcpp::Node
{
    public:
        ServiceServerNode() : Node("service_server_node_cpp")
        {
            this->servers_ = create_service<example_interfaces::srv::AddTwoInts>(
                "add_two_ints",
                std::bind(&ServiceServerNode::callback, this, _1, _2)
            );
        }
    private:
        
        void callback(example_interfaces::srv::AddTwoInts::Request::SharedPtr request, example_interfaces::srv::AddTwoInts::Response::SharedPtr response) {
            response->sum = request->a + request->b;
            RCLCPP_INFO(
                this->get_logger(),
                "%d + %d = %d", (int) request->a, (int) request->b, (int) response->sum
            );
        }
        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr servers_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  ServiceServerNode::SharedPtr node = std::make_shared<ServiceServerNode>();
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