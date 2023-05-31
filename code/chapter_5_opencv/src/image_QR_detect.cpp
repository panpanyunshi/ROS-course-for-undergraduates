#include <ros/ros.h>
#include <opencv2/core.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/aruco.hpp>
#include <geometry_msgs/PoseStamped.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/core/eigen.hpp>

using namespace cv;
static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    ros::Publisher pose_pub_;

public:
    ImageConverter()
        : it_(nh_)
    {
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/usb_cam/image_raw", 1,
                                   &ImageConverter::imageCb, this);
        image_pub_ = it_.advertise("/image_converter/output_video", 1);

        pose_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/aruco/pose", 1);

        cv::namedWindow(OPENCV_WINDOW, WINDOW_AUTOSIZE);
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
        cv::Mat img;
        if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
        {
            // 0 source:https://blog.csdn.net/Mufafafa/article/details/124464644

            // 1 marker detection
            img = cv_ptr->image;
            cv::Ptr<aruco::Dictionary> aruco_dict = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
            std::vector<int> markerIds;
            std::vector<std::vector<Point2f>> markerCorners, rejectedCandidates;
            auto parameters = aruco::DetectorParameters::create();
            aruco::detectMarkers(img, aruco_dict, markerCorners, markerIds, parameters, rejectedCandidates);
            aruco::drawDetectedMarkers(img, markerCorners, markerIds, Scalar(0, 255, 0));
            // 2 pose estimation
            cv::Mat cameraMatrix;
            std::vector<double> camera = {774.7691, 0.0, 367.113,
                                          0.0, 773.93408, 284.18334,
                                          0.0, 0.0, 1.0};
            cameraMatrix = Mat(camera);
            cameraMatrix = cameraMatrix.reshape(1, 3);

            cv::Mat distCoeffs;
            std::vector<double> dist = {-0.093661, -0.089419, 0.022542, 0.051281, 0.000000};
            distCoeffs = Mat(dist);
            distCoeffs = distCoeffs.reshape(1, 1);

            std::vector<cv::Vec3d> rvecs;
            std::vector<cv::Vec3d> tvecs;
            aruco::estimatePoseSingleMarkers(markerCorners, 0.053, cameraMatrix, distCoeffs, rvecs, tvecs);
            for (int i = 0; i < rvecs.size(); i++)
            {
                // 绘制坐标轴，检查姿态估计结果
                cv::aruco::drawAxis(img, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.02);

                geometry_msgs::PoseStamped pose;
                pose.header.frame_id = std::to_string(i);
                pose.pose.position.x = tvecs[i][0];
                pose.pose.position.y = tvecs[i][1];
                pose.pose.position.z = tvecs[i][2];

                cv::Mat R;
                Rodrigues(rvecs[i], R);
                
                Eigen::Matrix3d matrix;
                cv2eigen(R,matrix);

                Eigen::Quaterniond q;
                q = Eigen::Quaterniond(matrix);

                pose.pose.orientation.w = q.w();
                pose.pose.orientation.x = q.x();
                pose.pose.orientation.y = q.y();
                pose.pose.orientation.z = q.z();

                pose_pub_.publish(pose);     
            }
        }

        // Update GUI Window
        cv::imshow(OPENCV_WINDOW, img);
        cv::waitKey(3);

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_QR_detect");
    ImageConverter ic;
    ros::spin();
    return 0;
}