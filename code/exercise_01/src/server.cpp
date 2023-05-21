#include "ros/ros.h"
#include "exercise_01/ThreeVariables.h"

bool add(exercise_01::ThreeVariables::Request  &req,
         exercise_01::ThreeVariables::Response &res)
{
  res.Sum = req.A * req.B + req.C;
  ROS_INFO("request: A=%ld, B=%ld,C=%ld", (long int)req.A, (long int)req.B,(long int)req.C);
  ROS_INFO("sending back response,sum = [%ld]", (long int)res.Sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("caculate", add);
  ROS_INFO("Ready!");
  ros::spin();

  return 0;
}