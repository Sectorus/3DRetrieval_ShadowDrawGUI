//
// Created by stephan on 03.04.19.
//

#ifndef SHADOWDRAWGUI_BLENDING_H
#define SHADOWDRAWGUI_BLENDING_H
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "ResourceManager.h"

#endif //SHADOWDRAWGUI_BLENDING_H

class Blending{
public:
    cv::Mat blend(std::vector<int> refs);
    cv::Mat alphaBlend(cv::Mat img1, double weight1, cv::Mat img2, double weight2);
private:
};