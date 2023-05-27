
- `amcl_start.launch` 演示amcl的定位
- `movebase_start_with_map.launch `演示基于move_base的路径规划

## 激光SLAM
### 1 gmapping 功能包安装
`sudo apt install ros-${ROS_DISTRO}-gmapping`

### 2 cartorgrapher 功能包安装与使用
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
- 首先，我们使用rosdep来安装所需的软件包。如果你在安装ROS后已经执行了 `sudo rosdep init` 命令，将打印出一个错误。这个错误可以被忽略。
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
### 3 LIO-SAM 功能包安装与使用
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
#### 3.4 在仿真环境运行 LIO-SAM 建图
- 基于章节三、四创建的模型和配置的传感器
```
# 启动Gazebo仿真环境
roslaunch demo01_urdf_gazebo display_xacro_gazebo_sensor_all.launch
# `cd lio-sam_ws`启动lio-sam功能包
roslaunch lio_sam run.launch
```
- 效果展示
<img width="549" alt="0166f08c889d984a0277ad015471cf4" src="https://github.com/Bonener/ROS-course-for-undergraduates/assets/97874549/702ee2e6-8cc9-4e47-b22a-36c4e6c6adac">

## 视觉SLAM
### 1 ORB_SLAM3 功能包安装与使用
#### 1.1 安装依赖
- Pangolin安装，若关于Pangolin相关依赖缺失，参考 https://github.com/stevenlovegrove/Pangolin 安装
```
git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build
cd build
cmake ..
cmake --build .
```
- OpenCV安装，源码要求OpenCV 3.2及以上，官网下载源码：https://opencv.org/releases/ 以3.4.3版本为例
解压 `unzip opencv-3.4.3.zip`
安装依赖 `sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg.dev libtiff4.dev libswscale-dev libjasper-dev`
```
cd opencv-3.4.3
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j4
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
```
配置bash
```
sudo gedit /etc/bash.bashrc
```
在末尾加入如下两行代码
```
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig  
export PKG_CONFIG_PATH 
```
保存，使配置生效
```
source /etc/bash.bashrc 
```
- Eigen3安装
```
#github 
git clone https://github.com/eigenteam/eigen-git-mirror
 
#安装
cd eigen-git-mirror
mkdir build
cd build
cmake ..
sudo make install
 
#安装后,头文件安装在/usr/local/include/eigen3/
```
- boost库安装
由此链接进入boost官网：https://www.boost.org/ ，下载源码，以版本1.7.5为例
下载之后解压：
```
tar -xzvf boost_1_75_0.tar.gz
```
解压之后进入解压出来的文件夹，然后执行这个脚本
```
sudo ./bootstrap.sh
```
然后执行如下脚本
```
sudo ./b2 install
```
#### 1.2 ORB_SLAM3的编译和安装
```
git clone https://github.com/UZ-SLAMLab/ORB_SLAM3.git
cd ORB_SLAM3
chmod +x build.sh
./build.sh
```
