#include"ros/ros.h"
#include"opencv2/opencv.hpp"
#include"cv_bridge/cv_bridge.h"
#include"sensor_msgs/Image.h"
#include"time.h"

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    
    ros::init(argc, argv, "convert_image");
    
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("cv_bridge_image", 1);
     
    cv_bridge::CvImage cv_image;
    
    //Read image
    cv::Mat image = cv::imread("/home/bonen/vison_ws/src/config/test.png");
    //Read height,width
    int height = image.rows;
    int width = image.cols;
    // center = (width/2, height/2)
    cv::Point2f center(width/2, height/2);
   // Generated rotation matrix
    cv::Mat M = cv::getRotationMatrix2D(center, 90, 1.0);
    //Rotation transformation
    cv::Mat dst;
    cv::warpAffine(image, dst, M, cv::Size(width, height));
    //Write image
    imwrite("/home/bonen/vison_ws/src/config/test1.png", dst);
    //To ROS message
    cv_image.image = dst;
    cv_image.encoding = "bgr8";
    //Frequency
    ros::Rate rate(10);
    while(not ros::isShuttingDown())
    {
        
        pub.publish(cv_image.toImageMsg());
        ros::spinOnce();
    }

    return 0;
}
