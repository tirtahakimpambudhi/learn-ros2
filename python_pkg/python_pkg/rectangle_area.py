import rclpy
from rclpy.node import Node
from custom_ros_interfaces.srv import RectangleArea

class RectangleAreaServer(Node):
    def __init__(self):
        super().__init__('rectangle_area_server')
        self.server = self.create_service(
            RectangleArea,
            "rectangle_area",
            self.callback
        )

    def callback(self, request: RectangleArea.Request, response: RectangleArea.Response):
        response.area = request.length * request.width
        return response

def main(args=None):
    rclpy.init(args=args)
    node = RectangleAreaServer()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown(context=node.context)

if __name__ == "__main__":
    main()