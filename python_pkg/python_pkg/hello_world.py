#!/usr/bin/env python3

import rclpy 
from rclpy.node import Node

def main(args=None): 
    rclpy.init(args=args)
    node = Node("python_pkg_hello_world_node")
    try:
        node.get_logger().info("Hello World")

        rclpy.spin(node)
    except KeyboardInterrupt: 
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)

if __name__ == "__main__":
    main()

        