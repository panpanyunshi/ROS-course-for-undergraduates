
| [amcl_start.launch](launch/amcl_start.launch)  | 演示amcl的定位  |
|---|---|

```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
roslaunch chapter_6_navigation amcl_start.launch
```


| [movebase_start_with_map.launch](launch/movebase_start_with_map.launch)  | 演示基于move_base的路径规划,事先建图  |
|---|---|

```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
roslaunch chapter_6_navigation movebase_start_with_map.launch
```

| [movebase_start_no_map.launch](launch/movebase_start_no_map.launch)  | 演示基于move_base的路径规划，实时建图  |
|---|---|

```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
roslaunch chapter_6_navigation movebase_start_no_map.launch
```

### 注意：

[my_base_camera_laser_sensor_all.urdf.xacro](../chapter_3_model/xacro/my_base_camera_laser_sensor_all.urdf.xacro)中需要配置：单线激光雷达，imu

