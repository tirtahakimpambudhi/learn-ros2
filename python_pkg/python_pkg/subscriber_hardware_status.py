import rclpy
from rclpy.node import Node
from custom_ros_interfaces.msg import HardwareStatus

class SubscriberHWStatus(Node):
    def __init__(self):
        super().__init__('subcriber_hardware_status_node')
        self.subscriptions_ = self.create_subscription(
            msg_type=HardwareStatus, 
            callback=self.subscribe_data, 
            topic='status', 
            qos_profile=10
        )
    def subscribe_data(self, value : HardwareStatus):
        try:
            self.get_logger().info(f"Received status is {'ready' if value.is_ready_motor else 'not ready'}")
        except Exception as e:
            self.get_logger().error(f"Error when receiving temperature data: {e.__str__()}")
        finally:
            pass 

def main(args=None):
    rclpy.init(args=args)
    node = SubscriberHWStatus()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)

if __name__ == "__main__":
    main()
    