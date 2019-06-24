//
// Created by stephan on 03.04.19.
//

#include "Blending.h"

cv::Mat Blending::alphaBlend(cv::Mat img1, double weight1, cv::Mat img2, double weight2) {
    cv::Mat img;
    cv::addWeighted(img1, weight1, img2, weight2, 0, img);
    return img.clone();
}

cv::Mat Blending::blend(std::vector<int> refs) {

    auto first = ResourceManager::instance()->getResourceImages().at(refs.at(0));
    cv::Mat img(first.rows, first.cols, first.type(), cv::Scalar(255, 255, 255));

    for (int i = 1; i < refs.size(); i++) {
        cv::Mat mat = ResourceManager::instance()->getResourceImages().at(refs.at(i));
        cv::bitwise_and(mat, img, img);

    }

    cv::Mat transparent(first.rows, first.cols, first.type(), cv::Scalar(255, 255, 255));
    return alphaBlend(transparent, 0.7, img, 0.3).clone();
}