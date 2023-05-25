#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//Plane ransac specific includes 
#include <pcl/sample_consensus/model_types.h>   
#include <pcl/sample_consensus/method_types.h>   
#include <pcl/segmentation/sac_segmentation.h>  
 
#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/extract_indices.h>
 
 
 
ros::Publisher pub;
 
void
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  // From sensor_msgs/PointCloud2 to pcl/PointCloud
 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new 
 pcl::PointCloud<pcl::PointXYZ>);
 pcl::fromROSMsg (*input,*cloud); 
 
 
  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients); //Model parameter
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
 
  // Create a ransac method
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // Select the factor of the optimization parameter
  seg.setOptimizeCoefficients (true);
 
  seg.setModelType (pcl::SACMODEL_PLANE);  
  seg.setMethodType (pcl::SAC_RANSAC);    
  seg.setDistanceThreshold (0.2);        
 
  seg.setInputCloud (cloud);   
  seg.segment (*inliers,*coefficients);  
 
  // Publish the ransaced points by ros
  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud (cloud);
  extract.setIndices (inliers);
  extract.setNegative (true);
  extract.filter (*cloud_filtered);
  // To PointCloud2
  sensor_msgs::PointCloud2 output;  
  pcl::toROSMsg(*cloud_filtered,output);
  pub.publish (output);
}
 
int main (int argc, char** argv)
{
 
  ros::init (argc, argv, "yyf");
  ros::NodeHandle nh;
 
  ros::Subscriber sub = nh.subscribe ("velodyne_points", 1, cloud_cb);
 
  pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_ransaced", 1);
 
  ros::spin ();
}
 
 
