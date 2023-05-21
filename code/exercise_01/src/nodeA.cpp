#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

/**
 * @brief  node A
 * @note   
 * @param  argc: 
 * @param  **argv: 
 * @retval 
 */

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Message from node B: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("AtoB", 10);
  ros::Subscriber sub = n.subscribe("BtoA", 10, chatterCallback);
  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    
    std_msgs::String msg;
    std::stringstream ss;
    ss << "I am a super man.";
    msg.data = ss.str();
    chatter_pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}