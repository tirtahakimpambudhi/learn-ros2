import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from rcl_interfaces.msg import SetParametersResult
import random


class TemperatureSensorNode(Node):
    def __init__(self):
        super().__init__('python_pkg_temperature_sensor_node')
        self.declare_parameter('sensor_type', 'dht11')

        self.sensor_type = self.get_parameter('sensor_type').value
        # Callback function to get sensor type runtime
        self.add_on_set_parameters_callback(self.parameter_callback)

        self.publishers_ = self.create_publisher(String, 'c', 10)
        self.timer_ = self.create_timer(1.0, self.publish_temperature_data)

    def parameter_callback(self, params):
        for param in params:
            if param.name == 'sensor_type':
                self.sensor_type = param.value
                self.get_logger().info(f"Type sensor set to: {param.value}")
        return SetParametersResult(successful=True)

    def read_temperature_data(self):
        # Simulate reading temperature data from the sensor
        # In a real implementation, you would interface with the actual sensor hardware
        return random.randint(20, 41)  # Example temperature value

    def publish_temperature_data(self):
        msg = String()
        msg.data = f"Temperature data from {self.sensor_type} sensor is {self.read_temperature_data()}"
        self.publishers_.publish(msg)
        self.get_logger().info(f"Published temperature data: {msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = TemperatureSensorNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)
        