### 1 文件说明
---
| [example.cpp](src/example.cpp)  | 模板文件  |
|---|---|
---

| [pcl_ros2pcl_and_segmentation.cpp](src/pcl_ros2pcl_and_segmentation.cpp)| 点云分割  |
|---|---|

运行命令：
```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
rosrun chapter_5_pcl pcl_ros2pcl_and_segmentation 
rviz
```

- fixed_frame为laser
- 点云输入为/scan
- 输出为/scan_output


启动rivz观察这两者的效果即可

---

| [pcl_ros2pcl_and_voxelFilter.cpp](src/pcl_ros2pcl_and_voxelFilter.cpp) | 点云滤波  |
|---|---|

运行命令：
```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
rosrun chapter_5_pcl pcl_ros2pcl_and_voxelFilter
rviz
```
- fixed_frame为laser
- 点云输入为/scan
- 输出为/scan_output

启动rivz观察这两者的效果即可

---


| [pcl_ros2pcl_and_kdtree.cpp](src/pcl_ros2pcl_and_kdtree.cpp)  |  kdtree 半径搜索  |
|---|---|

运行命令：
```
roslaunch chapter_4_sensor display_xacro_gazebo_sensor_all.launch 
rosrun chapter_5_pcl pcl_ros2pcl_and_kdtree
rviz
```

- fixed_frame为laser
- 点云输入为/scan
- 输出为/scan_output

启动rivz观察这两者的效果即可

### 2 备注
此功能包用到了chapter_3_model 中的 display_xacro_gazebo_sensor_all.launch 文件。
切记要将 [my_base_camera_laser_sensor_all.urdf.xacro](../chapter_3_model/xacro/my_base_camera_laser_sensor_all.urdf.xacro)文件中的 **多线雷达插件** 配置好。

### 3 参考资源
[Point Cloud Library](https://pcl.readthedocs.io/en/latest/)
