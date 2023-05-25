#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//plane segmentation 
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
  // 将点云格式为sensor_msgs/PointCloud2 格式转为 pcl/PointCloud
 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new 
 pcl::PointCloud<pcl::PointXYZ>);
 pcl::fromROSMsg (*input,*cloud); 
 
 
  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
 // pcl::ModelCoefficients coefficients;   //申明模型的参数
 // pcl::PointIndices inliers;             //申明存储模型的内点的索引
  // 创建一个分割方法
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // 这一句可以选择最优化参数的因子
  seg.setOptimizeCoefficients (true);
 
  seg.setModelType (pcl::SACMODEL_PLANE);   //平面模型
  seg.setMethodType (pcl::SAC_RANSAC);    //分割平面模型所使用的分割方法
  seg.setDistanceThreshold (0.2);        //设置最小的阀值距离
 
  seg.setInputCloud (cloud);   //设置输入的点云
  seg.segment (*inliers,*coefficients);  
 
  // 把提取出来的外点 -> ros发布出去
  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud (cloud);
  extract.setIndices (inliers);
  extract.setNegative (true);
  extract.filter (*cloud_filtered);
  //再rviz上显示所以要转换回PointCloud2
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
 
 
