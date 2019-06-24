//
// Created by stephan on 25.04.19.
//

#include "EdgeDetector.h"

cv::Mat EdgeDetector::detectEdges(cv::Mat img) {
    src = img;
    cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    blur(src_gray, src_gray, cv::Size(3, 3));
    return CannyThreshold();
}

cv::Mat EdgeDetector::CannyThreshold() {
    cv::RNG rng(12345);
    cv::Mat canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    cv::Mat drawing = cv::Mat::zeros(canny_output.size(), CV_8UC3);
    drawing = cv::Scalar(255, 255, 255);

    for (int i = 0; i < contours.size(); i++) {
        cv::Scalar color = cv::Scalar(0, 0, 0);
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }

    return drawing;
}