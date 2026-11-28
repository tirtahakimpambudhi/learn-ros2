#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>
#include <std_srvs/srv/set_bool.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

class NumberCounter : public rclcpp::Node
{
public:
    NumberCounter() : Node("number_counter")
    {
        publish_ = create_publisher<std_msgs::msg::Int64>(
            "number_count",
            10);

        subscription_ = create_subscription<std_msgs::msg::Int64>(
            "number",
            10,
            std::bind(&NumberCounter::subscribe_data, this, std::placeholders::_1));

        timer_ = create_timer(
            1.0s,
            std::bind(&NumberCounter::publish_data, this));

        server_ = create_service<std_srvs::srv::SetBool>(
            "reset_count",
            std::bind(&NumberCounter::callback_service, this, _1, _2)
        );
    }

private:
    void callback_service(std_srvs::srv::SetBool::Request::SharedPtr request, std_srvs::srv::SetBool::Response::SharedPtr response)
    {
        try
        {
            if (request->data)
            {
                RCLCPP_INFO(
                    this->get_logger(),
                    "Receive data reset count it's 'true' set to '0'");
                this->count_ = 0;
                response->message = "Successfully reset count to '0'";
            } else {
                response->message = "Do nothing with count";
            }
            response->success = true;
            return;
        }
        catch (const std::exception &e)
        {
            response->message = e.what();
            response->success = false;
        }
    }

    void subscribe_data(const std_msgs::msg::Int64::SharedPtr value)
    {
        count_ += value->data;
    }

    void publish_data()
    {

        std_msgs::msg::Int64 count = std_msgs::msg::Int64();
        count.data = this->count_;
        publish_->publish(count);
    }

    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publish_;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr server_;
    rclcpp::TimerBase::SharedPtr timer_;
    u_int64_t count_ = 0;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    NumberCounter::SharedPtr node = std::make_shared<NumberCounter>();

    try
    {
        rclcpp::spin(node);
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(node->get_logger(), "Exception caught %s", e.what());
        rclcpp::shutdown();
        return 1;
    }
    rclcpp::shutdown();
    return 0;
}