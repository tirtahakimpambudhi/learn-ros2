#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;
using namespace std;

class ServiceClientNode : public rclcpp::Node
{
    public:
        ServiceClientNode() : Node("service_client_node_cpp")
        {
            this->client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        }
        void call_add_two_ints(int64_t a, int64_t b) {
            while (!client_->wait_for_service(1s))
            {
                RCLCPP_WARN(this->get_logger(), "Waiting server 'add_two_ints' to call service");
            }
            auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            request->a = a;
            request->b = b;
    
            auto future = this->client_->async_send_request(
                request,
                std::bind(&ServiceClientNode::callback_done, this, std::placeholders::_1)
            );
        }
    private: 
        void callback_done(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future) {
            auto response = future.get();
            RCLCPP_INFO(
                this->get_logger(),
                "Result = %d", (int) response->sum
            );
        }
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ServiceClientNode>();
  try
  {
    node->call_add_two_ints(12,45);
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