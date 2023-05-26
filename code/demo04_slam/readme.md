
- `amcl_start.launch` 演示amcl的定位
- `movebase_start_with_map.launch `演示基于move_base的路径规划

### 1 gmapping 功能包安装
`sudo apt install ros-${ROS_DISTRO}-gmapping`

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
```
sudo apt-get remove ros-${ROS_DISTRO}-abseil-cpp
```
- ros中其实也有一个abseil库，如果编译过程中造成混乱，可以把原来的库给删了
```
sudo apt-get remove ros-${ROS_DISTRO}-abseil-cpp
```
#### 2.4 安装与编译
```
catkin_make_isolated --install --use-ninja
```
#### 2.5 运行官方数据集进行测试
- 首先下载官方 https://google-cartographer-ros.readthedocs.io/en/latest/data.html 提供的数据包：
```
wget -P ~/Downloads https://storage.googleapis.com/cartographer-public-data/bags/backpack_2d/cartographer_paper_deutsches_museum.bag
```
- 运行cartographer来创建地图，在终端输入如下命令：
```
source ~/cartographer_ws/install_isolated/setup.bash
roslaunch cartographer_ros demo_backpack_2d.launch bag_filename:=${HOME}/Downloads/cartographer_paper_deutsches_museum.bag
```
### 3 LIO-SAM 功能包安装与编译
#### 3.1 安装依赖
- ROS
```
sudo apt-get install -y ros-noetic-navigation
sudo apt-get install -y ros-noetic-robot-localization
sudo apt-get install -y ros-noetic-robot-state-publisher
```
- 安装gtsam 4.0.3(noetic推荐安装版本>=4.0.3)
```
git clone -b 4.0.3 https://github.com/borglab/gtsam.git
mkdir build && cd build
cmake -DGTSAM_BUILD_WITH_MARCH_NATIVE=OFF ..
sudo make install -j4
```
#### 3.2 创建一个新的 LIO-SAM 工作空间
```
mkdir lio-sam_ws
cd lio-sam_ws
wstool init src
cd src
git clone https://github.com/TixiaoShan/LIO-SAM.git
cd ..
catkin_make
```
#### 3.3 运行官方数据集进行测试
- LIO-SAM的github首页 https://github.com/TixiaoShan/LIO-SAM 提供了很多的数据集可供下载
- 启动程序运行示例数据：
```
# 启动lio-sam功能包
roslaunch lio_sam run.launch
# 播放数据集
rosbag play outdoor.bag
```

