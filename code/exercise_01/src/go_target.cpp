#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

/*turtle's pose*/
turtlesim::Pose pose;
bool flag_pose = false;
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

    if (!flag_pose)
    {
        init_x = pose.x;
        init_y = pose.y;
    }
    flag_pose = true;
}

/**
 * @brief  main
 * @note   
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
int main(int argc, char *argv[])
{

    ros::init(argc, argv, "go_target");
    ros::NodeHandle nh; 

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 10, poseCallback);

    if (argc != 3)
    {
        ROS_INFO("usage:Please enter a destination location!");
        return 1;
    }
    double des_x = atof(argv[1]);
    double des_y = atof(argv[2]);
    cout << "destination:" << des_x << " " << des_y << endl;

    // 逻辑(一秒10次)
    double frequency = 20;
    ros::Rate r(frequency);

    // cycle
    while (ros::ok())
    {
        geometry_msgs::Twist msg;
        double vel_x;
        double vel_y;
        if (flag_pose)
        {
            // caculate speed
            if (sqrt(pow(pose.x - des_x, 2) + pow(pose.y - des_y, 2)) > 0.05)
            {
                vel_x =  (des_x - pose.x)/5; //5s 走完
                vel_y =  (des_y - pose.y)/5;
            }
            else
            {
                vel_x = 0;
                vel_y = 0;
            }
            msg.linear.x = vel_x;
            msg.linear.y = vel_y;
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
