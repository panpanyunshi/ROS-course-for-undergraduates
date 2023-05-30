#include <ros/ros.h>
#include <opencv2/core.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

public:
    ImageConverter()
        : it_(nh_)
    {
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/usb_cam/image_raw", 1,
                                   &ImageConverter::imageCb, this);
        image_pub_ = it_.advertise("/image_converter/output_video", 1);

        cv::namedWindow(OPENCV_WINDOW,WINDOW_AUTOSIZE);
    }

    ~ImageConverter()
    {
        cv::destroyWindow(OPENCV_WINDOW);
    }

    void imageCb(const sensor_msgs::ImageConstPtr &msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        
        //write what you want to do!
        Mat rot_mat,rot_picture;
        if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
        {
        //write what you want to do!
        cv::Point2f center(cv_ptr->image.rows/2,cv_ptr->image.cols/2);
        //旋转矩阵
        rot_mat = cv::getRotationMatrix2D(center,90.0,1.0); 
        //仿射变换
        cv::warpAffine(cv_ptr->image,rot_picture,rot_mat,cv::Size(cv_ptr->image.rows,cv_ptr->image.cols));

        }

        // Update GUI Window
        cv::imshow(OPENCV_WINDOW,rot_picture);
        cv::waitKey(3);

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_rotation");
    ImageConverter ic;
    ros::spin();
    return 0;
}