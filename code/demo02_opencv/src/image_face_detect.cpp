#include <iostream>
#include <fstream>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace cv;
using namespace std;
static const std::string OPENCV_WINDOW = "Image window";
std::string face_cascade_name = "/home/xzm/test_ws/src/demo02_opencv/config/haarcascade_frontalface_alt.xml"; /*must be absulute path*/
cv::CascadeClassifier faceCascade;


void faceRecongize(cv::CascadeClassifier faceCascade,cv::Mat frame){
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(frame, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	for (int i = 0; i < faces.size(); i++) {
        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        /*circle or ellipse. of course ,ellipse is better*/

        cv::ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
        // cv::circle(frame, center, (faces[i].width / 2+faces[i].height)/2, CV_RGB(255, 0, 0),5);
    }

}

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

        // write what you want to do!
        cv::Mat frame;
        cv::cvtColor(cv_ptr->image,frame,COLOR_BGRA2GRAY);
        faceRecongize(faceCascade,frame);

        // Update GUI Window
        cv::imshow(OPENCV_WINDOW,frame);
        cv::waitKey(3);

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char **argv)
{
    if (!faceCascade.load(face_cascade_name)) {
        std::cout << "load face_cascade_name failed. " << std::endl;
    }

    ros::init(argc, argv, "image_converter");
    ImageConverter ic;
    ros::spin();
    return 0;
}