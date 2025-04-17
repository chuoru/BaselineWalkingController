import os
import launch
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node

def generate_launch_description():
    pkg_share = FindPackageShare("baseline_walking_controller").find("baseline_walking_controller")
    rviz_config_file = os.path.join(pkg_share, "rviz", "display.rviz")

    return launch.LaunchDescription([
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            arguments=["-d", rviz_config_file]
        ),
    ])