//
// Created by stephan on 25.04.19.
//

#include "EdgeDetector.h"

void EdgeDetector::detectEdges(cv::Mat img) {
    src = img;
    cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    blur( src_gray, src_gray, cv::Size(3,3) );
    CannyThreshold();
}

void EdgeDetector::CannyThreshold()
{
    cv::RNG rng(12345);
    cv::Mat canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    /// Draw contours
    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
    }

    /// Show in a window
    namedWindow( "Contours", cv::WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}

void EdgeDetector::Dilation()
{
    int dilation_type;
    if( dilation_elem == 0 ){ dilation_type = cv::MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = cv::MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

    cv::Mat element = getStructuringElement( dilation_type,
                                         cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                         cv::Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
   // dilate( detected_edges, dilation_dst, element );
}