from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            # namespace='turtle1',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='hor_d20_batman_turtle',
            executable='batman_draw',
            output='screen',
        ),
    ])