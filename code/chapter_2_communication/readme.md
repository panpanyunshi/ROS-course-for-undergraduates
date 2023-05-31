### 1 话题通讯演示案例

 **相关文件** 
| 话题发布  |  [pub.cpp](src/pub.cpp) |
|---|---|
| 话题接收  | [sub.cpp](src/sub.cpp)  |

 **执行指令** 
```
roscore
rosrun chapter_2_communication pub
rosrun chapter_2_communication sub
```
### 2  服务通讯演示案例

 **相关文件** 
| 服务端  |  [add_two_ints_server.cpp](src/add_two_ints_server.cpp) |
|---|---|
| 客户端  | [add_two_ints_client.cpp](src/add_two_ints_client.cpp)  |

 **执行指令** 
```
roscore
rosrun chapter_2_communication add_two_ints_server
rosrun chapter_2_communication add_two_ints_client 1 2 
```

### 3 参数通讯演示案例

 **相关文件** 
| 配置参数  |  [set_param.cpp](src/set_param.cpp) |
|---|---|
| get参数  | [get_param.cpp](src/get_param.cpp)  |
| delete参数  | [delete_param.cpp](src/delete_param.cpp)  |

 **执行指令** 
```
roscore
rosrun chapter_2_communication set_param
rosrun chapter_2_communication get_param
rosrun chapter_2_communication delete_param
```

### 4 tf变换演示案例


 **相关文件** 
| 静态坐标变换关系 发布方  |  [tf_static_pub.cpp](src/tf_static_pub.cpp) |
|---|---|
| 订阅并得到子坐标系的世界坐标系  | [tf_static_sub.cpp](src/tf_static_sub.cpp.cpp)  |

 **执行指令** 
```
roscore
rosrun chapter_2_communication tf_static_pub
rosrun chapter_2_communication tf_static_sub
```



### 参考资源
| [ROS Tutorials](https://wiki.ros.org/ROS/Tutorials) |
|--|
| [第 2 章 ROS通信机制](http://www.autolabor.com.cn/book/ROSTutorials/di-2-zhang-ros-jia-gou-she-ji.html) |
