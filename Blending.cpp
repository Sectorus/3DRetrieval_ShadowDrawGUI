//
// Created by stephan on 03.04.19.
//

#include "Blending.h"

cv::Mat Blending::blend() {
    /*
    src1 = cv::imread("img/test.jpg");
    src2 = cv::imread("img/test2.jpg");

    if( !src1.data ) { printf("Error loading src1 \n"); return src1; }
    if( !src2.data ) { printf("Error loading src2 \n"); return src1; }


    /// Create Windows
    //cv::namedWindow("Linear Blend", 1);

    int width, height;
    if(src1.cols > src2.cols) width = src1.cols;
    else width = src2.cols;

    if(src1.rows > src2.rows) height = src1.rows;
    else height = src2.rows;

    cv::Mat img1(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    src1.copyTo(img1(cv::Rect(0,0,src1.cols, src1.rows)));

    int min_x = ( img1.cols - src2.cols)/2;
    int min_y = ( img1.rows - src2.rows)/2;

    cv::Rect roi = cv::Rect(min_x, min_y, src2.cols, src2.rows);
    cv::Mat out_image = img1.clone();
    cv::Mat A_roi= img1(roi);
    cv::Mat out_image_roi = out_image(roi);
    beta = ( 1.0 - alpha);

    cv::addWeighted(A_roi,alpha,src2, beta,0.0,out_image_roi);
    //imshow( "Linear Blend", out_image_roi );
    return out_image_roi;*/

    /*
     * Alpha blending - not suitable
     *
    auto first = ResourceManager::instance()->getResourceImages().at(0);
    cv::Mat img(first.rows, first.cols, first.type(), cv::Scalar(0, 0, 0));

    for(cv::Mat mat : ResourceManager::instance()->getResourceImages())
    {
        cv::addWeighted(img, 0.5, mat, 1.0f/ResourceManager::instance()->getResourceImages().size(), 0, img);
    }*/

    auto first = ResourceManager::instance()->getResourceImages().at(0);
    cv::Mat img(first.rows, first.cols, first.type(), cv::Scalar(255, 255, 255));

    for(cv::Mat mat : ResourceManager::instance()->getResourceImages())
    {
        cv::bitwise_and(mat, img, img);
    }

    //Make merged sketches lighter
    cv::Mat transparent(first.rows, first.cols, first.type(), cv::Scalar(255, 255, 255));
    cv::addWeighted(transparent, 0.7, img, 0.3, 0, img);

    return img;
}