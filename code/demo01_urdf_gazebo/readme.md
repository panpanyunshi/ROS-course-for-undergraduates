#文件说明
---

- display_urdf_rviz.launch 
    show urdf in rviz
- display_urdf_gazebo.launch
    show urdf in gazebo
- display_urdf_exercise.launch 
    class exercise
---
- display_xacro_rviz.launch
    show xacro in rviz
- display_xacro_gazebo.launch
    show xacro in gazebo
- display_xacro_gazebo_move.launch
    move the car
    rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear: {x: 0.2, y: 0, z: 0}, angular: {x: 0, y: 0, z: 0.5}}'

- display_xacro_gazebo_sensor_camera.launch
    add camera sensor
- display_xacro_gazebo_sensor_laser.launch
    add laser sensor
---
- display_xacro_gazebo_sensor_all.launch
包含全部传感器
