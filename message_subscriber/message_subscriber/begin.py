import rclpy
from rclpy.node import Node 
from std_msgs.msg import String

class MessageSubscriber(Node):
    def __init__(self):
        super().__init__('begin_message_subscriber')
        self.subscribe = self.create_subscription(String, 'message', self.receive_message, 10)

    def receive_message(self, message):
        try:
            self.get_logger().info(f"Received message: '{message.data}'")
        except Exception as e:
            self.get_logger().error(f"Error when receiving message: {e.__str__()}")
def main():
    rclpy.init()
    node = MessageSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("Keyboard interrupt, shutting down.")
        node.destroy_node()
        rclpy.shutdown()
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
