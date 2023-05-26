
- `amcl_start.launch` 演示amcl的定位
- `movebase_start_with_map.launch `演示基于move_base的路径规划

### 1 gmapping 功能包安装
`sudo apt install ros-<ROS版本>-gmapping`

### 2 cartorgrapher 功能包安装与编译
#### 2.1 安装辅助工具
```
sudo apt-get update
sudo apt-get install -y python3-wstool python3-rosdep ninja-build stow
```
#### 2.2 创建一个新的cartographer_ros工作空间
```
mkdir cartographer_ros_ws
cd cartographer_ros_ws
wstool init src
wstool merge -t src https://raw.githubusercontent.com/cartographer-project/cartographer_ros/master/cartographer_ros.rosinstall
wstool update -t src
```
#### 2.3 安装cartographer_ros的依赖项
- 首先，我们使用rosdep来安装所需的软件包。如果你在安装ROS后已经执行了'sudo rosdep init'命令，将打印出一个错误。这个错误可以被忽略。
