#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

/*turtle's pose*/
turtlesim::Pose pose;
bool flag_pose  = false;
double init_x = 0;
double init_y = 0;

/**
 * @brief
 * @note   get turttle's pose
 * @retval None
 */
void poseCallback(const turtlesim::Pose::ConstPtr &msg)
{
    pose.x = msg->x;
    pose.y = msg->y;

    pose.angular_velocity = msg->angular_velocity;
    pose.linear_velocity = msg->linear_velocity;
    pose.theta = msg->theta;
    
    if(!flag_pose){
    init_x = pose.x;
    init_y = pose.y;
    }
    flag_pose = true;

}

/**
 * @brief
 * @note   main function,tracking path:"8"
 * @link  8:https://blog.csdn.net/jh1513/article/details/117791061 model:https://blog.csdn.net/heyijia0327/article/details/44983551
 * @param  argc:
 * @param  *argv[]:
 * @retval
 */
int main(int argc, char *argv[])
{
    // 初始化 ROS 节点:命名(唯一)
    //  参数1和参数2 后期为节点传值会使用
    //  参数3 是节点名称，是一个标识符，需要保证运行后，在 ROS 网络拓扑中唯一
    ros::init(argc, argv, "turtle_ctr");
    // 实例化 ROS 句柄
    ros::NodeHandle nh; // 该类封装了 ROS 中的一些常用功能

    // 实例化 发布者 对象
    // 泛型: 发布的消息类型
    // 参数1: 要发布到的话题
    // 参数2: 队列中最大保存的消息数，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 10, poseCallback);

    // 逻辑(一秒10次)
    double frequency = 20;
    double internal = 1 / frequency;
    ros::Rate r(frequency);

    /*tracking parameter*/
    double a = 0;  //the size 
    double t = 0 + M_PI / 2; // make turtle in the center of 8


    // cycle
    while (ros::ok())
    {
        // caculate goal
        if(flag_pose){
        t += internal*1; // scale

        //path "8" 
        a = 4;
        double goal_x = init_x + a * cos(t) / (1 + sin(t) * sin(t));
        double goal_y = init_y + a * sin(t) * cos(t) / (1 + sin(t) * sin(t));
        //path heart 
        // a = 3;
        // double goal_x = init_x + a * (1 - sin(t))*cos(t);
        // double goal_y = init_y + a * (1 - sin(t))*sin(t) + 4;

        double goal_theta = 0;

        goal_theta = atan2(goal_y - pose.y, goal_x - pose.x) ;//(-pi,pi)
        
        goal_theta = goal_theta - pose.theta;
        if (goal_theta > M_PI)
            goal_theta = goal_theta - 2 * M_PI;
        if (goal_theta < -M_PI)
            goal_theta = goal_theta + 2 * M_PI;

        // caculate speed
        geometry_msgs::Twist msg;


        //case 1:
        //依靠高频处理频率解决误差问题,但是误差会使开始的时候有小摆动  hz:20
        double dis = sqrt(pow(goal_x - pose.x, 2) + pow(goal_y - pose.y, 2));
        msg.linear.x = dis / internal; 
        msg.angular.z = goal_theta/ internal;
        //case 2:
        //依靠精确模型解决误差问题，但是需要高频的pose calllback : pose.theta 事实证明不太精确，因为有y向的速度，而旋转速度没变。
        // msg.linear.x = cos(pose.theta)* (goal_x - pose.x)/internal + sin(pose.theta)* (goal_y - pose.y)/internal;
        // msg.linear.y = -sin(pose.theta)* (goal_x - pose.x)/internal + cos(pose.theta)* (goal_y - pose.y)/internal;
        // msg.angular.z = goal_theta/ internal;
        //case 3:
        //基于优化
        



        // 发布消息
        pub.publish(msg);

        // log
        cout << "pose_x:" << pose.x << " pose_y:" << pose.y << " pose_thera:" << pose.theta << endl;
        }

        // 根据前面制定的发送贫频率自动休眠 休眠时间 = 1/频率；
        r.sleep();

        // 暂无应用
        ros::spinOnce();
    }

    return 0;
}
