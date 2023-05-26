
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
```
sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src --rosdistro=${ROS_DISTRO} -y
```
- Cartographer使用abseil-cpp库，需要使用这个脚本手动安装：
`sudo apt-get remove ros-${ROS_DISTRO}-abseil-cpp`
- ros中其实也有一个abseil库，如果编译过程中造成混乱，可以把原来的库给删了
`sudo apt-get remove ros-${ROS_DISTRO}-abseil-cpp`
#### 2.4 安装与编译
`catkin_make_isolated --install --use-ninja`
