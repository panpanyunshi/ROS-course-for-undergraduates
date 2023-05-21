#include "ros/ros.h"
#include "exercise_01/ThreeVariables.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client");
  if (argc != 4)
  {
    ROS_INFO("usage: please input A B C");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<exercise_01::ThreeVariables>("caculate");
  exercise_01::ThreeVariables srv;
  srv.request.A = atoll(argv[1]);
  srv.request.B = atoll(argv[2]);
  srv.request.C = atoll(argv[3]);
  if (client.call(srv))
  {
    ROS_INFO("Received!Sum = %ld", (long int)srv.response.Sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}