from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os 
def generate_launch_description():
    launch_desc = LaunchDescription()

    params = os.path.join(get_package_share_directory("main"), "config", "params.yaml") 

    node_number = Node(
        package="activity02_py",
        executable="number",
        name="number_publish",
        remappings=[("number", "abcnumber123")],
        parameters=[params]
    )


    node_number_counter = Node(
        package="activity02_py",
        executable="number_counter",
        name="number_count",
        remappings=[("number", "abcnumber123")]
    )

    launch_desc.add_action(node_number)
    launch_desc.add_action(node_number_counter)

    return launch_desc