#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "common_code.hpp"

int main ()
{   
    cv::Mat I = cv::imread("../data/harrypgreen.jpeg",cv::IMREAD_COLOR);
    cv::Scalar lower(40,0,0);
    cv::Scalar upper(80,255,255);
    cv::Mat HSV_I = fsiv_convert_bgr_to_hsv(I);
    cv::Mat M = fsiv_create_mask_from_hsv_range(HSV_I,lower,upper);

    cv::imshow("Mascara",M);
    cv::imshow("Original",I);

    cv::waitKey(0);
    return 0;
}