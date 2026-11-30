#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;
using namespace std;

class ResetCounter : public rclcpp::Node
{
    public:
        ResetCounter() : Node("reset_counter")
        {
            this->client_ = this->create_client<std_srvs::srv::SetBool>("reset_count");
        }
        void call(bool input) {
            while (!client_->wait_for_service(1s))
            {
                RCLCPP_WARN(this->get_logger(), "Waiting server 'reset_count' to call service");
            }
            auto request = std::make_shared<std_srvs::srv::SetBool::Request>();
            request->data = input;
    
            auto future = this->client_->async_send_request(
                request,
                std::bind(&ResetCounter::callback_done, this, std::placeholders::_1)
            );
        }
    private: 
        void callback_done(rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture future) {
            auto response = future.get();
            RCLCPP_INFO(
                this->get_logger(),
                "Result = %s", response->message.c_str()
            );
        }
        rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ResetCounter>();
  try
  {
    node->call(true);
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