import rclpy
from rclpy.node import Node 

class CounterNode(Node):
    def __init__(self):
        super().__init__('python_pkg_counter_node')
        self._counter = 0
        self._time = self.create_timer(1.0, self.counter_callback)

    def counter_callback(self):
        self._counter += 1
        self.get_logger().info(f"Counter: {self._counter}")

def main(args=None):
    rclpy.init(args=args)
    node = CounterNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)


if __name__ == "__main__":
    main()