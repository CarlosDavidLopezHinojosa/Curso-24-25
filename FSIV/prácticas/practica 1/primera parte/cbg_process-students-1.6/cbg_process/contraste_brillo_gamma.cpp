#include <iostream>
#include <exception>

// Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"
int main ()
{   
    double brillo = 60, constraste = 1, gamma = 2;
    cv::Mat B, C, G;
    cv::Mat I = cv::imread("../data/ciclista_original.jpg",cv::IMREAD_COLOR);
    I = fsiv_convert_image_byte_to_float(I);

    //Imagen con Brillo
    B = I + cv::Scalar(brillo);
    //Imagen con Contraste
    cv::multiply(I,cv::Scalar(constraste),C); 
    //Imagen con Gamma
    cv::pow(I,gamma,G);

    I = fsiv_convert_image_float_to_byte(I);
    B = fsiv_convert_image_float_to_byte(B);
    C = fsiv_convert_image_float_to_byte(C);
    G = fsiv_convert_image_float_to_byte(G);

    cv::imshow("ORIGINAL",I);
    cv::imshow("BRILLO",B);
    cv::imshow("CONTRASTE",C);
    cv::imshow("GAMMA",G);

    cv::waitKey(0); 
    
    return 0;
}