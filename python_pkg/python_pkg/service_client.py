#!/usr/bin/env python3
import rclpy, os
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
from rclpy.task import Future
from functools import partial
class ServiceClientNode(Node):
    def __init__(self):
        super().__init__('service_client_node_py')
        self.clients_ = self.create_client(
            AddTwoInts, 
            "add_two_ints"
        )

        self.response = AddTwoInts.Response()

    def call(self, a, b):
        while not self.clients_.wait_for_service(1.0):
            self.get_logger().info(f"Waiting for '{AddTwoInts.__str__()}' server")

        request = AddTwoInts.Request(a=a,b=b)
        future = self.clients_.call_async(request)
        future.add_done_callback(partial(self.callback_done, request=request))
        return future
    def callback_done(self, future: Future, request: AddTwoInts.Request):
        response = future.result()
        self.response.sum = response.sum
        # self.get_logger().info(f"{request.a} + {request.b} = {response.sum}")




def main(args=None):
    rclpy.init()
    node = ServiceClientNode()
    while True:
        os.system("clear")
        try:
            is_quit = str(input("Enter to play program or press 'q' to quit\n")).strip().lower() == "q"
            
            if is_quit: break

            number_a = int(input("Number 1: "))
            number_b = int(input("Number 2: "))

            future = node.call(number_a, number_b)
            rclpy.spin_until_future_complete(node, future)
            if future.done():
                print(f"{number_a} + {number_b} = {future.result().sum}")
                
            
            is_quit = str(input("Enter to continue program or press 'q' to quit\n")).strip().lower() == "q"
            
            if is_quit: break

        except ValueError:
            print("Invalid input number must be interger!")
            continue
        except KeyboardInterrupt:
            break 

    node.destroy_node()
    rclpy.shutdown()