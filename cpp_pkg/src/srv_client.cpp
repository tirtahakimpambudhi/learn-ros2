#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("srv_client_node_cpp");
  auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
  try
  {
    while (!client->wait_for_service(1s))
    {
        RCLCPP_WARN(node->get_logger(), "Waiting server 'add_two_ints' to call service");
    }
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 10;
    request->b = 23;

    auto future = client->async_send_request(request);
    
    rclcpp::spin_until_future_complete(node, future);

    auto response = future.get();
    RCLCPP_INFO(
        node->get_logger(),
        "%d + %d = %d", (int) request->a, (int) request->b, (int) response->sum
    );
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