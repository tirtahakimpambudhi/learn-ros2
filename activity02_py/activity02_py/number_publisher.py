#/usr/bin/env python3
import rclpy
# from random import randint
from std_msgs.msg import Int64
from rclpy.node import Node
from rclpy.parameter import Parameter
from typing import List

class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__('number_publisher_node_python')
        self.publishers_ = self.create_publisher(
            Int64,
            "number",
            10
        )

        self.declare_parameter("number", 4)
        self.declare_parameter("time_period", 1.0)
        self.add_post_set_parameters_callback(self.parameters_callback)

        self.number_publish = self.get_parameter("number").value
        self.time_period = self.get_parameter("time_period").value
        self.timers_ = self.create_timer(
            self.time_period,
            self.publish_data
        )

    def parameters_callback(self, params : List[Parameter]):
        for param in params:
            if param.name == "number":
                self.number_publish = param.value
            elif param.name == "time_period":
                self.time_period = param.value

    def publish_data(self):
        value = Int64()
        value.data = self.number_publish
        self.publishers_.publish(value)


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)

if __name__ == "__main__":
    main()

        