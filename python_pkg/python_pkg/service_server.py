#!/usr/bin/env python3


import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts 

class ServiceServerNode(Node):
    def __init__(self):
        super().__init__('service_server_node_py')
        self.server_ = self.create_service(
            AddTwoInts,
            "add_two_ints",
            self.add_two_ints_callback
        )
        self.get_logger().info("Start to create service server 'add_two_ints'")


    def add_two_ints_callback(self, request : AddTwoInts.Request, response: AddTwoInts.Response):
        response.sum = request.a + request.b 
        self.get_logger().info(str(f"{request.a} + {request.b} = {response.sum}"))
        return response 

def main(args=None):
    rclpy.init(args=args)
    node = ServiceServerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown(context=node.context)

if __name__ == "__main__":
    main()