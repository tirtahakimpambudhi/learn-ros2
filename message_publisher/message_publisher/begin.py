import rclpy
from rclpy.node import Node
from std_msgs.msg import String 
class MessagePublisher(Node):
    def __init__(self):
        super().__init__('begin_message_publisher')
        self.publish = self.create_publisher(String, 'message', 10)

        self.time = self.create_timer(1.0, self.publish_message)

    def publish_message(self): 
        try:
            message = String()
            message.data = "Hello, this is a message from the publisher!"
            self.publish.publish(message)
            self.get_logger().info(f"Sucessfully published message: '{message.data}'")
        except Exception as e:
            self.get_logger().error(f"Error when publishing message: {e.__str__()}")

def main():
    rclpy.init()
    node = MessagePublisher()
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
