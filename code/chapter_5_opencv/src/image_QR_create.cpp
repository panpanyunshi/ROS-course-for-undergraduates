#include <opencv2/core.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/aruco.hpp>

using namespace cv;

int main(int argc, char **argv)
{
    // 1 create QR
    cv::Ptr<aruco::Dictionary> aruco_dict = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    int marker_id = 31;
    cv::Mat marker_img;
    aruco::drawMarker(aruco_dict, marker_id, 500, marker_img);
    // 2 在当前工作空间下生成jpg
    cv::String pic_name = "marker_6X6_250_" + std::to_string(marker_id) + ".jpg";
    cv::imwrite(pic_name, marker_img);
    return 0;
}