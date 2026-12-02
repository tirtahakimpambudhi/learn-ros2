
import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32, Int32MultiArray
from activity04_custom_interfaces.srv import SetLedState


class BatteryNode(Node):

    def __init__(self):
        super().__init__('battery_node')

        self.battery_state = 100
        self.led_states = []

        # Service Client
        self.clients_ = self.create_client(
            SetLedState,
            "set_led"
        )

        # Publisher battery status
        self.publishers_ = self.create_publisher(
            Int32,
            "battery_status",
            10
        )

        # Timer publisher
        self.timers_publish = self.create_timer(
            1.0,
            self.publish_data
        )

        # Timer battery
        self.timers_battery = self.create_timer(
            5.0,
            self.change_battery
        )

        # Subscriber LED states
        self.subscriptions_ = self.create_subscription(
            Int32MultiArray,
            "led_panel_states",
            self.subscribe_data,
            10
        )

    def change_battery(self):
        self.battery_state -= 25

        if self.battery_state <= 0:
            self.battery_state = 100

        self.get_logger().info(
            f"Battery state: {self.battery_state}%"
        )

        self.call_service()

    def subscribe_data(self, value: Int32MultiArray):
        self.led_states = value.data

        self.get_logger().info(
            f"Receive LED states: {value.data}"
        )

    def publish_data(self):
        msg = Int32()
        msg.data = self.battery_state

        self.publishers_.publish(msg)

    def call_service(self):

        # Check service availability
        if not self.clients_.service_is_ready():
            self.get_logger().warning(
                "LED service is not available yet!"
            )
            return

        states = [0] * 4

        # Determine LED states
        if 0 <= self.battery_state <= 25:
            states = [1, 0, 0, 0]

        elif 26 <= self.battery_state <= 50:
            states = [1, 1, 0, 0]

        elif 51 <= self.battery_state <= 75:
            states = [1, 1, 1, 0]

        elif 76 <= self.battery_state <= 100:
            states = [1, 1, 1, 1]

        # Send service requests
        for number, value in enumerate(states):

            request = SetLedState.Request()
            request.led_number = number
            request.state = value

            future = self.clients_.call_async(request)

            future.add_done_callback(
                self.callback_service
            )

    def callback_service(self, future):
        try:
            response = future.result()

            self.get_logger().info(
                response.message
            )

        except Exception as e:
            self.get_logger().error(
                f"Service call failed: {e}"
            )


def main(args=None):
    rclpy.init(args=args)

    node = BatteryNode()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
