# 文件说明

### urdf建模
---
|   [display_urdf_rviz.launch](launch/display_urdf_rviz.launch)  |  urdf编程，模型在rivz中显示 |
|--|--|
|   [display_urdf_gazebo.launch](launch/display_urdf_gazebo.launch)   |   urdf编程，模型在gazebo中显示  |
---

### xacro建模
|  [display_xacro_rviz.launch](launch/display_xacro_rviz.launch) |   xacro编程，模型在rivz中显示 |
|---|---|
|  [display_xacro_gazebo.launch](launch/display_xacro_gazebo.launch)  |   xacro编程，模型在gazebo中显示   |
|  [display_xacro_gazebo_move.launch](launch/display_xacro_gazebo_move.launch) |  - 配置了差速模型插件libgazebo_ros_diff_drive.so，可以通过话题/cmd_vel控制机器人运动<br>   - 终端输入`rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear: {x: 0.2, y: 0, z: 0}, angular: {x: 0, y: 0, z: 0.5}}'`可以控制机器人转圈                                                                               <br>  - 键盘控制程序[teleop_twist_keyboard.cpp](src/teleop_twist_keyboard.cpp)，启动后会有控制机器人运动的说明,启动方式：`rosrun chapter_3_model teleop_teist_keyboard`|
| [display_xacro_gazebo_sensor_camera.launch](launch/display_xacro_gazebo_sensor_camera.launch)  |    增加了单目相机传感器libgazebo_ros_camera.so |
|  [display_xacro_gazebo_sensor_laser.launch](launch/display_xacro_gazebo_sensor_laser.launch) |  增加了单线雷达传感器 libgazebo_ros_laser.so   |
---


| [display_xacro_gazebo_sensor_all.launch](launch/display_xacro_gazebo_sensor_all.launch) | - 包含全部传感器：单目、双目、深度相机，单线、多线雷达，imu,gps <br> - 可在文件[my_base_camera_laser_sensor_all.urdf.xacro](xacro/my_base_camera_laser_sensor_all.urdf.xacro)启用/取消相应传感器  |
|---|---|

