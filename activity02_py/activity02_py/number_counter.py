#/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Int64
from rclpy.parameter import Parameter
from typing import List
class NumberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter_node_python")

        self.declare_parameter("start_number", 0)
        self.add_post_set_parameters_callback(self.parameters_callback)
        
        self.start_number = self.get_parameter("start_number").value

        self.subscriptions_ = self.create_subscription(
            Int64, 
            "number",
            self.subscribe_data,
            10
        )
        self.publishers_ = self.create_publisher(
            Int64, 
            "number_count",
            10
        )
        self.total_count = 0

    def subscribe_data(self, value : Int64):
        self.total_count += value.data
        self.publishers_.publish(Int64(data=self.total_count))

    def parameters_callback(self, params: List[Parameter]):
        for param in params:
            if param.name == "start_number":
                self.start_number = param.value

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)

if __name__ == "__main__":
    main()
        