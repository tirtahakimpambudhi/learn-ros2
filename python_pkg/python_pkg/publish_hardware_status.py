#!/usr/bin/env python3
from random import randint, choice
import rclpy
from rclpy.node import Node 
from custom_ros_interfaces.msg import HardwareStatus 


class PublishHWStatus(Node):
    def __init__(self):
        super().__init__('publish_hardware_status_node')
        self.publish_ = self.create_publisher(HardwareStatus, "status", 10)

        self.timers_ = self.create_timer(
            1.0,
            self.publish_data
        )

    def publish_data(self):
        value = HardwareStatus()
        value.is_ready_motor = choice([True, False])
        value.temperature = float(randint(30, 40))
        value.message = f"{'Hardware is ready to used' if value.is_ready_motor else 'Hardware is not ready to used'}"

        self.publish_.publish(value)



def main(args=None):
    rclpy.init(args=args)
    node = PublishHWStatus()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)
        