import rclpy
from rclpy.node import Node
from activity04_custom_interfaces.srv import SetLedState
from std_msgs.msg import Int32MultiArray
from typing import List
from rclpy.parameter import Parameter
class LedNode(Node):
    def __init__(self):
        super().__init__('led_node')
        self.declare_parameter("led_states", [0] * 4)
        self.add_post_set_parameters_callback(self.parameters_callback)
        param_value = self.get_parameter("led_states").value
        self.led_states = param_value if type(param_value) is list and len(param_value) == 4 else [0] * 4 
        self.servers_ = self.create_service(
            SetLedState,
            "set_led",
            self.callback 
        )

        self.publishers_ = self.create_publisher(
            Int32MultiArray, 
            "led_panel_states",
            10
        )

        self.timers_ = self.create_timer(
            1.0,
            self.publish_data
        )
        
    def parameters_callback(self, params: List[Parameter]):

        self.get_logger().info("PARAMETER CALLBACK DIPANGGIL!")

        for param in params:

            self.get_logger().info(
                f"Name: {param.name}, Value: {param.value}"
            )

            if param.name == "led_states":
                self.led_states = list(param.value)

                self.get_logger().info(
                    f"LED STATES UPDATED: {self.led_states}"
                )

    def response_out_of_led(self, request: SetLedState.Request, response: SetLedState.Response):
            self.get_logger().error(f"Error when receive call set led cause index out range, the leds range index 0 - 3")
            response.success = False
            response.message = f"Error set led because there are no led with number '{request.led_number}'"
            return response      

    def callback(self, request: SetLedState.Request, response: SetLedState.Response):
        try:
            if request.led_number >= 0 and request.led_number <= (len(self.led_states) - 1):
                self.led_states[request.led_number] = request.state
                response.success = True
                response.message = f"Successfully set led with number '{request.led_number}'"
            else:
                return self.response_out_of_led(request, response)

        except IndexError as err:
            return self.response_out_of_led(request, response)

        return response

    def publish_data(self):

        self.get_logger().info(
            f"Publishing: {self.led_states}"
        )

        self.publishers_.publish(
            Int32MultiArray(data=self.led_states)
        )

def main(args=None):
    rclpy.init(args=args)
    node = LedNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass 
    finally:
        node.destroy_node()
        rclpy.try_shutdown(context=node.context)
        