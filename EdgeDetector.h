//
// Created by stephan on 25.04.19.
//

#ifndef SHADOWDRAWGUI_EDGEDETECTOR_H
#define SHADOWDRAWGUI_EDGEDETECTOR_H


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>


class EdgeDetector{
public:
    cv::Mat detectEdges(cv::Mat img);
private:
    cv::Mat src; cv::Mat src_gray;
    int thresh = 300;
    cv::Mat CannyThreshold();
};

#endif //SHADOWDRAWGUI_EDGEDETECTOR_H
