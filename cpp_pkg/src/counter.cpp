#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"

using namespace std;

class CounterNode : public rclcpp::Node {
    public: 
        rclcpp::Logger logger = get_logger();
        CounterNode() : Node("cpp_pkg_counter_node") {
            timer_ = create_wall_timer(chrono::seconds(1), std::bind(&CounterNode::counter_callback, this));
        }

        void counter_callback() {
            count_++;
            RCLCPP_INFO(logger, "Counter: %d", count_);
        }
    private:
        rclcpp::TimerBase::SharedPtr timer_;
        int count_ = 0;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<CounterNode>();
    try
    {
        rclcpp::spin(node);
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(node->get_logger(), "Exception caught: %s", e.what());
        return 1;
    }
    return 0;
}