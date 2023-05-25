#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>

ros::Publisher pub;

void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;

  // to PCL data
  pcl_conversions::toPCL(*cloud_msg, *cloud);

  // creat a VoxelGrid filter, size = 0.1m
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloudPtr);
  sor.setLeafSize (0.1, 0.1, 0.1);
  sor.filter (cloud_filtered);

  // to ROS data
  sensor_msgs::PointCloud2 output;
  pcl_conversions::moveFromPCL(cloud_filtered, output);

  // publish filtered point cloud data
  pub.publish (output);
}

int
main (int argc, char** argv)
{
  // initialize ROS node
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  // creat a subscriber
  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("velodyne_points", 1, cloud_cb);

  // creat a publisher 
  pub = nh.advertise<sensor_msgs::PointCloud2> ("filtered_points", 1);

  // Spin
  ros::spin ();
}
