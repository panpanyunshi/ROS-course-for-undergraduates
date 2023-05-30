#include "ros/ros.h"
#include "std_msgs/String.h"

/**
 * @brief  node B
 * @note   
 * @param  msg: 
 * @retval None
 */

ros::Publisher pub;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  /* receive
  */
  ROS_INFO("Message from node A: [%s]", msg->data.c_str()); 
  /* publish
  */
  std_msgs::String pub_msg;
  std::stringstream ss;
  ss << "OK,I see.";
  pub_msg.data = ss.str();
  pub.publish(pub_msg);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("AtoB", 10, chatterCallback);
  pub = n.advertise<std_msgs::String>("BtoA",10);

  ros::spin();

  return 0;
}