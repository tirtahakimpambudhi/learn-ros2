import rclpy
from rclpy.node import Node
from std_msgs.msg import String
class SubscriberTemperatureSensor(Node):
    def __init__(self):
        super().__init__('python_pkg_subscriber_temperature_sensor_node')
        self.subscriptions_ = self.create_subscription(
            callback=self.temperature_data_callback,
            topic='temperature_data',
            msg_type=String,
            qos_profile=10
        )

    def temperature_data_callback(self, msg):
        try:
            self.get_logger().info(f"Received temperature data: {msg.data}")
        except Exception as e:
            self.get_logger().error(f"Error when receiving temperature data: {e.__str__()}")
        finally:
            pass

def main(args=None):
    rclpy.init(args=args)
    node = SubscriberTemperatureSensor()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)

if __name__ == "__main__":
    main()
    